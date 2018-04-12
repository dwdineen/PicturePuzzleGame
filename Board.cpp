#include <iostream>
#include <SFML\Graphics.hpp>
#include "Board.h"

//ONLY FOR DEVELOPMENT USE (LATER WE WILL HAVE PICTURES)
sf::Color pallete(int n) {
	n = n % 5;
	switch (n) {
	case 0: return sf::Color::Red;
	case 1: return sf::Color::Blue;
	case 2: return sf::Color::Yellow;
	case 3: return sf::Color::Cyan;
	case 4: return sf::Color::Magenta;
	}

	return sf::Color::Black;
}


std::pair<int, int> Board::blankCoords() {
	for (int row = 0; row < sideLen; row++) {
		for (int col = 0; col < sideLen; col++) {

			auto x = tileVec[sideLen * row + col];
			if (x->getType() == Tile::Type::EMPTY)
				return std::pair<int, int>(row, col);

		}
	}
}

bool Board::swap(int row1, int col1, int row2, int col2) {
	if (row1 < 0 || row1 > sideLen) return false;
	if (col1 < 0 || col1 > sideLen) return false;
	if (row2 < 0 || row2 > sideLen) return false;
	if (col2 < 0 || col2 > sideLen) return false;

	//asserts that at least one of the tiles is empty
	assert(get(row1, col1)->getType() == Tile::Type::EMPTY || get(row2, col2)->getType() == Tile::Type::EMPTY);

	Tile * temp = get(row1, col1);
	set(row1, col1, get(row2, col2));
	set(row2, col2, temp);

	for (int row = 0; row < sideLen; row++) {
		for (int col = 0; col < sideLen; col++) {
			std::cout << (get(row, col)->getType() == Tile::Type::NORMAL);
		}
		std::cout << std::endl;
	}

	return true;
}

Board::Board(sf::RenderWindow * win) { Board(win, 3, "CHANGE_LATER"); }

Board::Board(sf::RenderWindow * win, int n, std::string pName) {

	window = win;
	sideLen = n;
	tileVec = std::vector<Tile*>(n*n, nullptr);

	for (int i = 0; i < n * n - 1; i++) {
		//Get the portion of image to put on tile
		//...
		auto col = i % sideLen;
		auto row = i / sideLen;
		tileVec[i] = new Tile(row, col, sideLen, win->getSize().x, win, false, pallete(i));
	}

	tileVec[n*n - 1] = new Tile(n-1, n-1, sideLen, win->getSize().x, win, true);

	//bounds
	tileVec[n*n - 2]->setBound(sfu::concatRects(tileVec[n*n - 2]->getRect(), tileVec[n*n - 1]->getRect()));
	tileVec[n*n - n - 1]->setBound(sfu::concatRects(tileVec[n*n - n - 1]->getRect(), tileVec[n*n - 1]->getRect()));

	//blank
	blank = tileVec[n*n - 1];
}

bool Board::move(sfu::Dir direction) {
    
    for (int r = 0; r < sideLen; ++r) {
        for (int c = 0; c < sideLen; ++c) {
            if (get(r, c)->getType() == Tile::Type::EMPTY) {
                
				switch (direction) {
				case sfu::Dir::DOWN:
					return swap(r, c, r + 1, c);
				case sfu::Dir::LEFT:
					return swap(r, c, r, c - 1);
				case sfu::Dir::UP:
					return swap(r, c, r - 1 , c);
				case sfu::Dir::RIGHT:
					return swap(r, c, r, c + 1);
				default:
					assert(false);
				}

            }
        }
    }

	return false;

}

void Board::shuffle(int n) {


}

bool Board::isSolved() {
	return false;
}


void Board::update() {
	for (int row = 0; row < sideLen; row++) {
		for (int col = 0; col < sideLen; col++) {

			auto x = tileVec[sideLen * row + col];
			if (x->getType() == Tile::Type::EMPTY) continue;
			sfu::DragNDrop::State state = x->update();

			bool b = state == sfu::DragNDrop::State::LOWERED;
			if (b && sfu::pointsClose(x->pos(), blank->pos(), .01)) {
				auto oPos = x->getOriginalPos();
				x->setOriginalPos(blank->pos());
				blank->shift(sfu::getDirAtoB(blank->pos(), oPos));
				auto bCoords = blankCoords();
				swap(row, col, bCoords.first, bCoords.second);
			}

		}
	}
}

void Board::draw() {
	for (auto & x : tileVec) x->draw();
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
