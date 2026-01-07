#pragma once 

#include <stdint.h>
#include <ncurses.h>

#define INIT_EDITOR ((Editor){ \
    .kb_buffer = EOF, \ 
    .cur = (Cursor){.x = 0, .y = 0}, \
    .win = initscr() \
})

typedef struct {
    int8_t x;
    int8_t y;
} Cursor;

typedef struct {
    Cursor cur;
    int16_t kb_buffer; 
    WINDOW *win;
} Editor;

// During this all of the setup stuff should happen
// initscr is called by INIT_EDITOR
void editor_start();

// This is the infinite loop of waiting for user input and doing stuff with it 
void editor_loop(Editor *editor);


