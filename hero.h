#pragma once
#include <iostream>

using namespace std;

class Hero {
	private:
		int default_speed, speed, max_health, health;
		bool dead;
	public:
		// Constructors:
		Hero(int set_speed, int set_health);	
		// Accessors:
		int get_speed();
		int get_dspeed();
		int get_health();
		int get_mhealth();
		bool is_dead();
		// Mutators:
		void adjust_health(int x);
		void adjust_speed(int x);
};

// Implementations:
Hero::Hero(int set_speed, int set_health) {
	speed = set_speed;
	default_speed = set_speed;
	health = set_health;
	max_health = set_health;
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
