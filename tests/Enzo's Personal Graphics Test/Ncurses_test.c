/*
 * ******************* D ********************
 * Enzo's Personal Graphics Test/Ncurses_test.c
 * Created 1/5/26
 * 
 * Messing around with Ncurses. Might be useful.
 * -----------Build Instructions------------
 * Just good old GCC with -lncurses
 * Something like:
 * gcc Ncurses_test.c -lncurses -o cool_test
 * ---------------Extra Notes -------------
 * The Man Page on Ncurses' getch() is very
 * helpful. Heres a link to it on the ArchWiki:
 * https://man.archlinux.org/man/curs_getch.3x.en
 * ---------------------------------------
 * ******************************************
 */
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

int main(){
	WINDOW *scrn = initscr();
	raw();
	cbreak;
	noecho();
	keypad(stdscr, TRUE);
	start_color();

	int32_t cursor_y, cursor_x;
	uint16_t kb_buffer = EOF; //This needs to be a 16-bit value, or else very bad things start happening.
	printw("Press F4 to quit\n");
	while(kb_buffer != KEY_F(4) ){ 
		getyx(scrn, cursor_y, cursor_x);
		kb_buffer = getch();
		switch(kb_buffer){ 
			//Movement
			case KEY_UP: 
			       	move(cursor_y-1, cursor_x);
				break;

			case KEY_DOWN: 
				move(cursor_y+1, cursor_x);
				break;

			case KEY_LEFT: 
				move(cursor_y, cursor_x-1);
				break;

			case KEY_RIGHT:
				move(cursor_y, cursor_x+1);
				break;

			case KEY_BACKSPACE: 
				if(move(cursor_y, cursor_x-1) == OK){
					delch();
				}
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
				printw("%c", kb_buffer);
				break;
		}
		refresh();
	
	}
	endwin();
	return 0;
}

