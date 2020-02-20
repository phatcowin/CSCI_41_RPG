#include "map.h"
#include <unistd.h>

const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

int main() {
	turn_on_ncurses();
	Map map;
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == RIGHT) {
			if (map.obstacle_check(x+1, y) == false) {
				x++;
				map.move_hero(x, y);
			}
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		}
		else if (ch == LEFT) {
			if (map.obstacle_check(x-1, y) == false) x--;
			if (y < 0) y = 0;
		}
		else if (ch == UP) {
			if (map.obstacle_check(x, y-1) == false) y--;
			if (x < 0) x = 0;
		}
		else if (ch == DOWN) {
			if (map.obstacle_check(x, y+1) == false) y++;
			if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}

		

		clear();
		map.draw(x,y);
		mvprintw(11,11,"X: %i Y: %i\n",x,y);
		refresh();
		usleep(5000);
	}
	clear();
	endwin(); // End curses mode
	system("clear");
}
