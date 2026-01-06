#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

int32_t main(int32_t argc, uint8_t *argv[]){
  	int32_t ch;
  	initscr();
  	noecho();
  	cbreak();
  	printw("Press crtl+c to exit ...\n\n");
  	for (;;) {
    	ch = getch();
    	printw("Value of %c is: %d\n", ch, ch);
  	}
  	endwin();
  	return 0;
}
