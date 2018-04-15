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
	for (int row = 0; row < numTilesPerSide; row++) {
		for (int col = 0; col < numTilesPerSide; col++) {

			auto x = tileVec[numTilesPerSide * row + col];
			if (x->getType() == Tile::Type::EMPTY)
				return std::pair<int, int>(row, col);

		}
	}
}

bool Board::swap(int norm_row, int norm_col, int blank_row, int blank_col) {
	if (norm_row < 0 || norm_row >= numTilesPerSide) return false;
	if (norm_col < 0 || norm_col >= numTilesPerSide) return false;
	if (blank_row < 0 || blank_row >= numTilesPerSide) return false;
	if (blank_col < 0 || blank_col >= numTilesPerSide) return false;

	//asserts that at least one of the tiles is empty
	assert(get(blank_row, blank_col)->getType() == Tile::Type::EMPTY);

	//Swap physical positions -- Note originalPos is based off array pos which is swapped next
	get(norm_row, norm_col)->setPos(blank->pos());
	blank->shift(sfu::getDirAtoB(blank->pos(), getOriginalPos(norm_row, norm_col)));

	//Swap array positions
	Tile * temp = get(norm_row, norm_col);
	set(norm_row, norm_col, get(blank_row, blank_col));
	set(blank_row, blank_col, temp);

	//--Debug-- Prints the board sorta
	for (int row = 0; row < numTilesPerSide; row++) {
		for (int col = 0; col < numTilesPerSide; col++) {
			std::cout << (get(row, col)->getType() == Tile::Type::NORMAL);
		}
		std::cout << std::endl;
	}

	//update bounds
	updateBounds();

	return true;
}

void Board::updateBounds() {

	for (auto v : tileVec) v->resetBound();

	auto bCoords = blankCoords();

	auto t_up = get(bCoords.first - 1, bCoords.second);
	auto t_down = get(bCoords.first + 1, bCoords.second);
	auto t_left = get(bCoords.first, bCoords.second - 1);
	auto t_right = get(bCoords.first, bCoords.second + 1);
	
	if (t_up) t_up->setBound(sfu::concatRects(t_up->getRect(), blank->getRect()));
	if (t_left) t_left->setBound(sfu::concatRects(t_left->getRect(), blank->getRect()));
	if (t_right) t_right->setBound(sfu::concatRects(blank->getRect(), t_right->getRect()));
	if (t_down) t_down->setBound(sfu::concatRects(blank->getRect(), t_down->getRect()));

}

void Board::centerAllTiles() {
	for (int r = 0; r < numTilesPerSide; ++r) {
		for (int c = 0; c < numTilesPerSide; ++c) {
			get(r, c)->setPos(getOriginalPos(r, c));
		}
	}
}

//Board::Board(sf::RenderWindow * win) { Board(win, 3, "CHANGE_LATER"); }

Board::Board(sf::RenderWindow * win, int n, float sideSize, std::string pName) :
	boardSideSize(sideSize), window(win), numTilesPerSide(n)
{
	tileVec = std::vector<Tile*>(n*n, nullptr);

	for (int i = 0; i < n * n - 1; i++) {
		//Get the portion of image to put on tile
		//...
		auto col = i % numTilesPerSide;
		auto row = i / numTilesPerSide;
		tileVec[i] = new Tile(row, col, numTilesPerSide, win->getSize().x, win, false, pallete(i));
	}

	tileVec[n*n - 1] = new Tile(n-1, n-1, numTilesPerSide, win->getSize().x, win, true);

	//bounds
	tileVec[n*n - 2]->setBound(sfu::concatRects(tileVec[n*n - 2]->getRect(), tileVec[n*n - 1]->getRect()));
	tileVec[n*n - n - 1]->setBound(sfu::concatRects(tileVec[n*n - n - 1]->getRect(), tileVec[n*n - 1]->getRect()));

	//blank
	blank = tileVec[n*n - 1];

	//DEBUG
	//move(sfu::Dir::RIGHT);

}

bool Board::move(sfu::Dir direction) {
    
	centerAllTiles();
	lastMoved = nullptr;

    for (int r = 0; r < numTilesPerSide; ++r) {
        for (int c = 0; c < numTilesPerSide; ++c) {
            if (get(r, c)->getType() == Tile::Type::EMPTY) {
                
				switch (direction) {
				case sfu::Dir::DOWN:
					return swap(r - 1, c, r , c);
				case sfu::Dir::LEFT:
					return swap(r, c + 1, r, c);
				case sfu::Dir::UP:
					return swap(r + 1, c, r , c);
				case sfu::Dir::RIGHT:
					return swap(r, c - 1, r, c);
				default:
					assert(false);
				}

            }
        }
    }

	assert(false);
	return false;

}

void Board::shuffle(int n) {
    for (int i = 0; i < n; ++i) {
        int d = rand() % 4;
        move(sfu::Dir(d));
    }
}

bool Board::isSolved() {
	return false;
}

void Board::update() {
	for (int row = 0; row < numTilesPerSide; row++) {
		for (int col = 0; col < numTilesPerSide; col++) {

			auto x = tileVec[numTilesPerSide * row + col];

			if (lastMoved && lastMoved != x) continue;
			if (x->getType() == Tile::Type::EMPTY) continue;

			sfu::DragNDrop::State state = x->update();

			bool L = state == sfu::DragNDrop::State::LOWERED;
			bool R = state == sfu::DragNDrop::State::RAISED;

			if (L && sfu::pointsClose(x->pos(), blank->pos(), .01)) {
				auto bCoords = blankCoords();
				swap(row, col, bCoords.first, bCoords.second);
				lastMoved = nullptr;
			} else if (L && sfu::pointsClose(x->pos(), getOriginalPos(row, col), .01)) {
				lastMoved = nullptr;
			}

			if (R) lastMoved = x;
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
	
	if (row < 0 || row >= numTilesPerSide || col < 0 || col >= numTilesPerSide)
		return nullptr;

    Tile *ptr = tileVec[numTilesPerSide * row + col];
    return ptr;
}

void Board::set(int row, int col, Tile * ptr){
    tileVec[numTilesPerSide * row + col] = ptr;
}

sf::Vector2f Board::getOriginalPos(int row, int col) {
	auto tileSideLen = boardSideSize / numTilesPerSide;
	return sf::Vector2f(tileSideLen * col, tileSideLen * row);
}
