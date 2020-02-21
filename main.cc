#include "map.h"
#include "party.h"
#include "monster.h"
#include <unistd.h>
#include <time.h>
#include <fstream>

const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

struct LL {
	string char_name;
	LL *next;
	LL(string new_cname, LL *new_next) { char_name = new_cname, next = new_next; }
};

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

void SaveGame(Party *party, Map *map){
    ofstream save1("Save1.txt");
    save1 << party -> get_location_x() << endl;
    save1 <<  party -> get_location_y() << endl;
    save1 <<  party -> get_wallet() << endl;
    save1 <<  party -> get_health(0) << endl;
    save1 <<  party -> get_health(1) << endl;
    save1 <<  party -> get_speed(0) << endl;
    save1 <<  party -> get_speed(1) << endl;
    save1 <<  party -> get_kills() << endl;
    save1 <<  map -> save_map() << endl;
    save1.close();
    cout << "Game saved to Save1.txt" << endl;
}

void start_battle(Party *party) {
	Monster monster;
	int attack_value, target, turn_count(0);
	LL *head = nullptr;
	if (monster.get_speed() <= 4) { // make it linked
		LL *temp1 = new LL(monster.get_name(), head);
		head = temp1;
		LL *temp2 = new LL("Dan", head);
		head = temp2;
		LL *temp3 = new LL("Jerry", head);
		head = temp3;
	} else if (monster.get_speed() >= 6) {
		LL *temp1 = new LL("Dan", head);
		head = temp1;
		LL *temp2 = new LL("Jerry", head);
		head = temp2;
		LL *temp3 = new LL(monster.get_name(), head);
		head = temp3;
	} else {
		LL *temp1 = new LL("Dan", head);
		head = temp1;
		LL *temp2 = new LL(monster.get_name(), head);
		head = temp2;
		LL *temp3 = new LL("Jerry", head);
		head = temp3;
	}
	head->next->next->next = head; // make it circular
	LL *temp = head;
	while (monster.is_dead() == false && party->party_alive() == true) {
		if (temp->char_name == "Dan" && party->is_dead(0) == false) {
			attack_value = 1 + rand() % 5;
			monster.adjust_health(attack_value);
			//mvprintw(turn_count,0,"Dan attacked %i, for %i damage.",monster.get_name(),attack_value);
		} else if (temp->char_name == "Jerry" && party->is_dead(1) == false) {
			attack_value = 1 + rand() % 3;
			monster.adjust_health(attack_value);
			//mvprintw(turn_count,0,"Jerry attacked %i for %i damage.",monster.get_name(),attack_value);
		} else {
			attack_value = 1 + rand() % 4;
			if (party->is_dead(0) == false) target = 0;
			else target = 1;
			party->adjust_health(target, attack_value);
			//mvprintw(turn_count,0,"%i attacked %i for %i damage.",monster.get_name(),party->get_name(target),attack_value);
		}
		turn_count++;
		temp = temp->next;
	}
	if (monster.is_dead() == true && party->party_alive() == true) party->monster_slain();
}

int main() {
	cout << "Would you like to load your Saved Data?" << endl;
    cout << "1) YES" << endl;
    cout << "2) NO" << endl;
    string selection = "";
do{
        cin >> selection;
        if (!cin){
            selection = "0";
            continue;
        }
        if (selection == "1") {
            cout << "Yas";
            string line;
            ifstream save1 ("Save1.txt");
            if (save1.is_open()){
//           for (int y(0); y < 100; y++) {
//                for (int x(0); x < 100; x++) {
//                    map.at(y).at(x) = string[y * 100 + x +];
    save1.close();
  }

        }
            else if (selection == "2"){
                cout << "No";
                break;
            }
        else{
            cin >> selection;
    }
}while (selection != "1" and selection != "2");

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
		if (party.party_alive() == false) {
			cout << "GAME OVER";
			break;
		}
		
		map.move_party(x, y, &party);		

		clear();
		map.draw(x,y);
		//mvprintw(11,11,"X: %i Y: %i\n",x,y);
		mvprintw(0,12,"TREASURE: %i/%i",party.get_wallet(),map.treasure_count());
		mvprintw(1,12,"KILLS: %i",party.get_kills());
		mvprintw(2,12,"DAN'S HEALTH: %i/%i",party.get_health(0),party.get_mhealth(0));
		mvprintw(3,12,"JERRY'S HEALTH: %i/%i",party.get_health(1),party.get_mhealth(1));
		refresh();
		usleep(5000);
	}
	clear();
	endwin(); // End curses mode
	system("clear");
}
