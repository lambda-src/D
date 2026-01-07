#include "editor.h"
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

int32_t main(int32_t argc, uint8_t *argv[]){
	Editor editor = INIT_EDITOR;
	editor_start();
	editor_loop(&editor);
	// Disable raw mode and clear screen 
	// TODO The terminal is still fucked after window ends 
	endwin();
	printf("\033c");
  	return 0;
}
