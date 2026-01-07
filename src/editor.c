#include "editor.h"

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
				break;
        }
        refresh();
    }
}