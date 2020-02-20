#pragma once
#include <iostream>
#include <vector>
#include "hero.h"

using namespace std;

class Party {
	private:
		int location_x, location_y, wallet;
		vector<Hero> hero;
	public:
		// Constructors:
		Party();

		// Accessors:
		int get_location_x();
		int get_location_y();
		int get_wallet();

		// Mutators:
		void set_location(int x, int y);
		void grab_treasure();
};

// Implementations:
Party::Party() {
	location_x = 50;
	location_y = 50;
	wallet = 0;
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

void Party::set_location(int x, int y) {
	location_x = x;
	location_y = y;
}

void Party::grab_treasure() {
	wallet++;
}
