#pragma once

#include <string>
#include <vector>
#include "Tile.h"

class Board {

	int size = 3;
	std::vector<std::vector<Tile>> tileVec;


public:

	static enum Dir {
		UP,
		DOWN,
		LEFT,
		Right
	};

	Board(); //Default Constructor
	Board(int n, std::string pName); //with board size and picture

	void move(Dir direction);
	void shuffle();
	bool isSolved();


	~Board();
};

