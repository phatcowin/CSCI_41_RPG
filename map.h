#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include "party.h"
using namespace std; //Boo hiss

class Map {
	vector<vector<char>> map;
	default_random_engine gen;
	int total_treasure;
	public:
	static const char HERO     = 'H';
	static const char MONSTER  = 'M';
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = '.';
	static const char TREASURE = '$';
	static const char GOAL     = 'G';
	static const size_t SIZE = 100; //World is a 100x100 map
	static const size_t DISPLAY = 10; //Show a 10x10 area at a time
	bool obstacle_check();
	void move_party();
	char check_tile();
	int treasure_count() { return total_treasure; }
	//Randomly generate map
	void init_map() {
		uniform_int_distribution<int> d100(1,100);
		map.clear();
		map.resize(SIZE); //100 rows tall
		total_treasure = 0;
		for (auto &v : map) v.resize(SIZE,'.'); //100 columns wide
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				//Line the map with walls
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1) 
					map.at(i).at(j) = WALL;
				else if (i == SIZE/2 and j == SIZE/2) { 
					map.at(i).at(j) = HERO;
				} else {
					//5% chance of monster
					if (d100(gen) <= 5) {
						map.at(i).at(j) = MONSTER;
					}
					else if (d100(gen) <= 3) {
						map.at(i).at(j) = TREASURE;
						total_treasure++;
					}
					else if (d100(gen) <= 10) { //10% each spot is wall
						map.at(i).at(j) = WALL;
					}
					else if (d100(gen) <= 3) { //3% each spot is water
						map.at(i).at(j) = WATER;
					}
					else if (d100(gen) <= 20) { //20% chance of water near other water
						if (map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER)
							map.at(i).at(j) = WATER;
					}
				}
			}
		}
	}
	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			start_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				//if (i == cursor_x && j == cursor_y)
				//	attron(A_UNDERLINE | A_BOLD);
				int color = 1;
				if (map.at(i).at(j) == WALL)
					color = 5;
				else if (map.at(i).at(j) == WATER)
					color = 2;
				else if (map.at(i).at(j) == HERO)
					color = 3;
				else if (map.at(i).at(j) == TREASURE)
					color = 4;
				else if (map.at(i).at(j) == MONSTER)
					color = 6;

				attron(COLOR_PAIR(color));
				mvaddch(i-start_y,j-start_x,map.at(i).at(j));
				attroff(COLOR_PAIR(color));
				//attroff(A_UNDERLINE | A_BOLD);
			}
		}
	}
	bool obstacle_check(int x, int y) {
		if (map.at(y).at(x) == WATER || map.at(y).at(x) == WALL) return true;
		else return false;
	}
	void move_party(int x, int y, Party *party) {
		map.at(party->get_location_y()).at(party->get_location_x()) = OPEN;
		party->set_location(x, y);
		map.at(party->get_location_y()).at(party->get_location_x()) = HERO;
	}
	string save_map(){
        string map_save;
        for(int y = 0; y < 100 ; y++) {
            for (int x = 0; x < 100 ; x++) {
                map_save += map.at(y).at(x);

            }
        }
        return map_save;
    }
	char check_tile(int x, int y) {
		return map.at(y).at(x);
	}
	Map() {
		init_map();
	}
};
