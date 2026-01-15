#include "editor.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

void editor_start() {
	raw();
	cbreak;
	noecho();
	keypad(stdscr, TRUE);
	start_color();
    printw("Press F4 to quit\n");
}

void editor_loop(Editor *editor) {
    while (editor->kb_buffer != KEY_F(4)) {
        getyx(editor->win, editor->cur.y, editor->cur.x);
		editor->kb_buffer = getch();
        switch (editor->kb_buffer) {
            case KEY_UP: 
			    move(editor->cur.y-1, editor->cur.x);
				break;

			case KEY_DOWN: 
				move(editor->cur.y+1, editor->cur.x);
				break;

			case KEY_LEFT: 
				move(editor->cur.y, editor->cur.x-1);
				break;

			case KEY_RIGHT:
				move(editor->cur.y, editor->cur.x+1);
				break;

			case KEY_BACKSPACE: 
				if(move(editor->cur.y, editor->cur.x-1) == OK)
                    // TODO characters need to be deleted based upon cursor position
					delch();
				break;
			//Attribs
			case KEY_F(1):
				attrset(A_NORMAL);
				break;
			case KEY_F(2):
				attrset(A_REVERSE);
				break;
			//Typing
			case EOF:
				break;
			default: 
				printw("%c", editor->kb_buffer);
                // TODO charcters need to be inserted into the ed_buffer based upon cursor pos
				break;
        }
        refresh();
    }
}

EditorBuffer *init_editor_buffer() {
    EditorBuffer *buff = malloc(sizeof(EditorBuffer));
    if (buff == NULL)
        panic("Allocation error");
    buff->ptr = malloc(INITIAL_CAP);
    if (buff->ptr == NULL)
        panic("Allocation error");
    buff->cap = INITIAL_CAP;
    buff->len = 0;
    return buff;
}

void editor_buffer_grow(EditorBuffer *buff) {
    // Blazingly fast way to multiply by 2
    buff->cap <<= 1; 
    uint8_t *new_buff = realloc(buff->ptr, buff->cap);
    if (new_buff == NULL) 
        // If the allocation fails cause the buffer got too big then ideally we would 
        // save the contents to a file or something or rework the editor buffer to not
        // suck as much :c 
        panic("Allocation error");
    buff->ptr = new_buff;
}

void editor_buffer_push(EditorBuffer *buff, uint8_t byte) {
    if (buff->len == buff->cap)
        editor_buffer_grow(buff);
    buff->ptr[buff->len++] = byte;
}

void editor_buffer_insert(EditorBuffer *buff, size_t index, uint8_t byte) {
    if (buff->len == buff->cap)
        editor_buffer_grow(buff);
    // Shift the elements to make room for the new element 
    memmove(
        &buff->ptr[index], 
        &buff->ptr[index+1], 
        &buff->ptr[buff->len] - &buff->ptr[index]
    );
    buff->ptr[index] = byte;
    buff->len++;
}

void editor_buffer_remove(EditorBuffer *buff, size_t index) {
    // If any of these early return
    if (buff->len == 0 || index < 0 || index >= buff->len)
        return;
    memmove(
        &buff->ptr + index, 
        &buff->ptr + index + 1, 
        (buff->len - index - 1)
    );
    buff->len--;
}