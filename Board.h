#pragma once

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Tile.h"

// 0 1 2
// 3 4 5
// 6 7 8


class Board {

	//BoardSize
	float boardSideSize;

	int numTilesPerSide = 3;
	std::string imageStr;
	std::vector<Tile*> tileVec;

	// Holds a pointer to the last tile that was moved
	Tile * lastMoved;

	Tile * blank;
	std::pair<int, int> blankCoords();

	sf::RenderWindow * window;

	bool swap(int norm_row, int norm_col, int blank_row, int blank_col);
	void updateBounds();

	Tile * get(int row, int col);
	void set(int row, int col, Tile * ptr);

	sf::Vector2f getOriginalPos(int row, int col);

public:

	//Board(sf::RenderWindow * win); //Default Constructor
	Board(sf::RenderWindow * win, int n, float board_size, std::string pName); //with board size and picture

	bool move(sfu::Dir direction);
	void shuffle(int n = 200); //Make n random moves
	bool isSolved();

	void update();
	void draw();

	~Board();


};

