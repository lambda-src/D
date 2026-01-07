#include "editor.h"
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

int32_t main(int32_t argc, uint8_t *argv[]){
	Editor editor = INIT_EDITOR;
	editor_start();
	editor_loop(&editor);
	// Exit once loop ends 
	endwin();
  	return 0;
}
