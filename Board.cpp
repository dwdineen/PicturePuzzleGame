#include "Board.h"



bool Board::swap(int row1, int col1, int row2, int col2) {
	if (row1 < 0 || row1 > sideLen) return false;
	if (col1 < 0 || col1 > sideLen) return false;
	if (row2 < 0 || row2 > sideLen) return false;
	if (col2 < 0 || col2 > sideLen) return false;

	//asserts that at least one of the tiles is empty
	assert(get(row1, col1)->getType() == Tile::EMPTY || get(row2, col2)->getType() == Tile::EMPTY);

	Tile * temp = get(row1, col1);
	set(row1, col1, get(row2, col2));
	set(row2, col2, temp);

	lastMoved = (get(row1, col1)->getType() == Tile::NORMAL) 
		? get(row1, col1) : get(row2, col2);

	return true;
}

Board::Board() { Board(3, "CHANGE_LATER"); }

Board::Board(int n, std::string pName) {
	sideLen = n;
	tileVec = std::vector<Tile*>(n*n);

	for (int i = 0; i < n * n - 1; i++) {
		//Get the portion of image to put on tile
		//...
		tileVec[i] = new Tile(/* ... */);
	}

	tileVec[n*n - 1] = new Tile(true);
}

bool Board::move(Dir direction) {
    
    for (int r = 0; r < sideLen; ++r) {
        for (int c = 0; c < sideLen; ++c) {
            if (get(r, c)->getType() == Tile::Type::EMPTY) {
                
				switch (direction) {
				case Dir::DOWN:
					return swap(r, c, r + 1, c);
				case Dir::LEFT:
					return swap(r, c, r, c - 1);
				case Dir::UP:
					return swap(r, c, r - 1 , c);
				case Dir::RIGHT:
					return swap(r, c, r, c + 1);
				}

            }
        }
    }

}

void Board::shuffle(int n) {


}

bool Board::isSolved() {
	return false;
}


Board::~Board() {
	for (auto t : tileVec) delete t;
}

Tile * Board::get(int row, int col) {
    Tile *ptr = tileVec[sideLen * row + col];
    return ptr;
}

void Board::set(int row, int col, Tile * ptr){
    tileVec[sideLen * row + col] = ptr;
}
