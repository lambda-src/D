#pragma once 

#include <stdint.h>
#include <ncurses.h>

#define INIT_EDITOR ((Editor){ \
    .kb_buffer = EOF, \ 
    .cur = (Cursor){.x = 0, .y = 0}, \
    .win = initscr(), \
    .ed_buffer = init_editor_buffer() \
})

// The intial capacity for the editing buffer
#define INITIAL_CAP 1024

// This will most def need to be re worked at some point but for now its gonna be a simple 
// dynamic array implementation
typedef struct {
    size_t cap; 
    size_t len;
    // Even though this is an array of bytes there's no need for a \0 at the end because we already know the length
    // Also this mayyyy need to be changed for the future if you had unicode characters that were more then 1 byte
    // since if you had this string: "hi 🐼!" the actual byte length is 9 so deleting the 3th byte wont delete the 
    // emoji and will instead delete the first byte of the emoji sequence
    uint8_t *ptr;
} EditorBuffer;

typedef struct {
    int8_t x;
    int8_t y;
} Cursor;

typedef struct {
    Cursor cur;
    int16_t kb_buffer; 
    WINDOW *win;
    EditorBuffer *ed_buffer;
} Editor;

// During this all of the setup stuff should happen
// initscr is called by INIT_EDITOR
void editor_start();

// This is the infinite loop of waiting for user input and doing stuff with it 
void editor_loop(Editor *editor);

// Allocate a editor buffer
// This probably doesn't need to be freed since when the program exits the editor will be freed
EditorBuffer *init_editor_buffer();

// Push a byte into the buffer and grow if need be 
void editor_buffer_push(EditorBuffer *buff, uint8_t byte);

// Double the size of the buffers capacity and realloc the current buffer over
void editor_buffer_grow(EditorBuffer *buff);

// Insert a character at a specific index and shift stuff accordingly
void editor_buffer_insert(EditorBuffer *buff, size_t index, uint8_t byte);

// Deletes a character then shifts everything accordingly
void editor_buffer_remove(EditorBuffer *buff, size_t index);
