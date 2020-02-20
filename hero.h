#pragma once
#include <iostream>

using namespace std;

class Hero {
	private:
		int location_x, location_y;
	public:
		// Constructors:
		Hero();

		// Accessors:
		int get_location_x();
		int get_location_y();

		// Mutators:
		void set_location(int x, int y);
};

Hero::Hero() {
	location_x = 50;
	location_y = 50;
}

int Hero::get_location_x() {
	return location_x;
}

int Hero::get_location_y() {
	return location_y;
}

void Hero::set_location(int x, int y) {
	location_x = x;
	location_y = y;
}
