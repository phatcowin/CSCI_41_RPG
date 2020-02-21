#pragma once
#include <iostream>
#include <vector>
#include "hero.h"

using namespace std;

class Party {
	private:
		int location_x, location_y, wallet, kills;
		vector<Hero> heroes;
	public:
		// Constructors:
		Party();

		// Accessors:
		int get_location_x();
		int get_location_y();
		int get_wallet();
		int get_kills();
		int get_health(int x);
		int get_mhealth(int x);
		int get_speed(int x);
		bool is_dead(int x);
		bool party_alive();
		string get_name(int x);

		// Mutators:
		void set_location(int x, int y);
		void grab_treasure();
		void monster_slain();
		void adjust_health(int x, int y);
};

// Implementations:
Party::Party() {
	location_x = 50;
	location_y = 50;
	wallet = 0;
	kills = 0;
	Hero temp(4 ,150, "Dan");
	heroes.push_back(temp);
	Hero temp2(6, 100, "Jerry");
	heroes.push_back(temp2);
}

int Party::get_location_x() {
	return location_x;
}

int Party::get_location_y() {
	return location_y;
}

int Party::get_wallet() {
	return wallet;
}

int Party::get_kills() {
	return kills;
}

int Party::get_health(int x) {
	return heroes.at(x).get_health();
}

int Party::get_mhealth(int x) {
	return heroes.at(x).get_mhealth();
}

int Party::get_speed(int x) {
	return heroes.at(x).get_speed();
}

bool Party::is_dead(int x) {
	return heroes.at(x).is_dead();
}

bool Party::party_alive() {
	if (heroes.at(0).is_dead() == true && heroes.at(1).is_dead() == true) return false;
	else return true;
}

string Party::get_name(int x) {
	return heroes.at(x).get_name(); 
}

void Party::set_location(int x, int y) {
	location_x = x;
	location_y = y;
}

void Party::grab_treasure() {
	wallet++;
}

void Party::monster_slain() {
	kills++;
}

void Party::adjust_health(int x, int y) {
	heroes.at(x).adjust_health(y);
}
