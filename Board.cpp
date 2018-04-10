#include "Board.h"



Board::Board() {}

Board::Board(int n, std::string pName) {}

void Board::move(Dir direction) {
    if (direction == Board::Dir::UP) return;
    Tile * empty;
    for (int r = 0; r < sideLen; ++r) {
        for (int c = 0; c < sideLen; ++c) {
            if (!get(r, c)) {
                set(r, c, empty);
            }
        }
    }

}

void Board::shuffle() {}

bool Board::isSolved() {
	return false;
}


Board::~Board() {}

Tile * Board::get(int row, int col) {
    Tile *ptr = tileVec[sideLen * row + col];
    return ptr;
}

void Board::set(int row, int col, Tile * ptr){
    tileVec[sideLen * row + col] = ptr;
}
