#include"BoardImpl.h"

using namespace std;

BoardClass::BoardClass()
	:BoardClass(8) {}

//cell_num‚Écell_num‚ğİ’è
BoardClass::BoardClass(const CellNum &board_size)
	:pimpl(new Impl(board_size)){}

BoardClass::BoardClass(const BoardClass &board)
	: pimpl(new Impl(*board.pimpl)) {}

BoardClass::~BoardClass() = default;

//”Õ–Ê‚Ì‰Šú‰»
std::pair<PutState, PutState> BoardClass::Init()
{
	this->pimpl->board = vector<vector<int>>(this->pimpl->board_size.y, vector<int>(this->pimpl->board_size.x, Cell_Empty));
	auto mid = this->pimpl->board_size / (CellCoord)2;

	auto left_top = CellCoord(mid.x - 1, mid.y - 1);
	auto right_top = CellCoord(mid.x, mid.y - 1);
	auto left_down = CellCoord(mid.x - 1, mid.y);
	auto right_down = CellCoord(mid.x, mid.y);

	auto black = BoardClass::Cell_BLACK;
	auto white = BoardClass::Cell_WHITE;

	pair<PutState, PutState> ret;

	ret.first.color = black;
	ret.first.flip = { left_top,right_down };

	ret.second.color = white;
	ret.second.flip = { right_top,left_down };

	PutState init[] = { ret.first,ret.second };

	for (auto &i : init)
	{
		for (auto &j : i.flip)
		{
			this->pimpl->PutPieceAt(j, i.color);
		}
	}

	return ret;
}
