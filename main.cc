#include "map.h"
#include "party.h"
#include "monster.h"
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

void start_battle(Party *party) {
	clear();
	party->monster_slain();
	
}

int main() {
	turn_on_ncurses();
	Map map;
	Party party;
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == RIGHT) {
			if (map.obstacle_check(x+1, y) == false) {
				x++;
			}
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		}
		else if (ch == LEFT) {
			if (map.obstacle_check(x-1, y) == false) {
				x--;
			}
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

		if (map.check_tile(x, y) == '$') {
			party.grab_treasure();

		}
		else if (map.check_tile(x, y) == 'M') start_battle(&party);
		
		map.move_party(x, y, &party);		

		clear();
		map.draw(x,y);
		//mvprintw(11,11,"X: %i Y: %i\n",x,y);
		mvprintw(0,12,"TREASURE: %i/%i",party.get_wallet(),map.treasure_count());
		mvprintw(1,12,"KILLS: %i",party.get_kills());
		mvprintw(2,12,"DAN'S HEALTH: %i/%i",party.get_health(0),party.get_mhealth(0));
		mvprintw(3,12,"JERRY'S HEALTH: %i/%i",party.get_health(1),party.get_mhealth(0));
		refresh();
		usleep(5000);
	}
	clear();
	endwin(); // End curses mode
	system("clear");
}
