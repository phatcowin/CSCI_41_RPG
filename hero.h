#pragma once
#include <iostream>

using namespace std;

class Hero {
	private:
		int default_speed, speed, max_health, health;
		bool dead;
		string h_name;
	public:
		// Constructors:
		Hero(int set_speed, int set_health, string set_name);	
		// Accessors:
		int get_speed();
		int get_dspeed();
		int get_health();
		int get_mhealth();
		bool is_dead();
		string get_name();
		// Mutators:
		void adjust_health(int x);
		void adjust_speed(int x);
};

// Implementations:
Hero::Hero(int set_speed, int set_health, string set_name) {
	speed = set_speed;
	default_speed = set_speed;
	health = set_health;
	max_health = set_health;
	h_name = set_name;
	dead = false;
}

int Hero::get_speed() {
	return speed;
}

int Hero::get_dspeed() {
	return default_speed;
}

int Hero::get_health() {
	return health;
}

int Hero::get_mhealth() {
	return max_health;
}

bool Hero::is_dead() {
	return dead;
}

string Hero::get_name() {
	return h_name;
}

void Hero::adjust_health(int x) {
	health += x;
	if (health <= 0) {
		health = 0;
		dead = true;
	}
}

void Hero::adjust_speed(int x) {
	speed += x;
	if (speed < 0) speed = 0;
}
