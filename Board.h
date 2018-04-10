#pragma once

#include <string>
#include <vector>
#include "Tile.h"

// 0 1 2
// 3 4 5
// 6 7 8


class Board {

	int sideLen = 3;
	std::string imageStr;
	std::vector<Tile*> tileVec;

	// Holds a pointer to the last tile that was moved
	Tile * lastMoved;


	bool swap(int row1, int col1, int row2, int col2);

	Tile * get(int row, int col);
	void set(int row, int col, Tile * ptr);

public:

	enum Dir {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Board(); //Default Constructor
	Board(int n, std::string pName); //with board size and picture

	bool move(Dir direction);
	void shuffle(int n = 200); //Make n random moves
	bool isSolved();

	~Board();


};

