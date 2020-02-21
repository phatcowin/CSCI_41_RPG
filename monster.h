#pragma once
#include <iostream>
#include <time.h>

using namespace std;

class Monster {
	private:
		int speed, health;
		bool dead;
		string m_name;
	public:
		// Constructors:
		Monster();

		// Accessors:
		int get_speed();
		int get_health();
		bool is_dead();
		string get_name();

		// Mutators: 
		void adjust_health(int x);
};

// Implementations:
Monster::Monster() {
	srand(time(0));
	health = (rand() % 15) + 10;
	speed = rand() % 10;
	dead = false;
	int shuffle = rand() % 10;
	if (shuffle == 0) m_name = "Cthulu";
	else if (shuffle == 1) m_name = "Dragon";
	else if (shuffle == 2) m_name = "Jigglypuff";
	else if (shuffle == 3) m_name = "Basilisk";
	else if (shuffle == 4) m_name = "Nightmare";
	else if (shuffle == 5) m_name = "Oso";
	else if (shuffle == 6) m_name = "Warren Buffet";
	else if (shuffle == 7) m_name = "Sekiro";
	else if (shuffle == 8) m_name = "Ghost";
	else if (shuffle == 9) m_name = "Chimera";
}

int Monster::get_speed() {
	return speed;
}

int Monster::get_health() {
	return health;
}

bool Monster::is_dead() {
	return dead;
}

string Monster::get_name() {
	return m_name;
}

void Monster::adjust_health(int x) {
	health += x;
	if (health <= 0) {
		health = 0;
		dead = true;
	}
}
