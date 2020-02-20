#pragma once
#include <iostream>

using namespace std;

class Hero {
	private:
		int location_x, location_y;
	public:
		// Constructors:
		Hero(int x, int y);

		// Accessors:
		int get_location_x();
		int get_location_y();

		// Mutators:
		void set_location(int x, int y);
};

Hero::Hero(int x, int y) {
	location_x = x;
	location_y = y;
}

int Hero::get_location_x() {
	return location_x;
}

int Hero::get_location_y() {
	return location_y;
}
