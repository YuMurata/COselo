#include"BoardImpl.h"

using namespace std;

//”Õ–Ê‚Ì‘å‚«‚³‚ğæ“¾
BoardClass::CellNum BoardClass::GetBoardSize()const
{
	return this->pimpl->board_size;
}

//À•Wcoord‚Ìó‘Ô‚ğæ“¾
int BoardClass::GetCellState(const CellCoord &coord)const
{
	return this->pimpl->board[coord.y][coord.x];
}

//Fcolor‚ÌÎ”‚ğæ“¾
int BoardClass::GetCellNum(const int &color)const
{
	return this->pimpl->cell_num[color];
}

//‘½‚¢‚Ù‚¤‚ÌF‚ğæ“¾
int BoardClass::GetOften()const
{
	auto black = this->GetCellNum(Cell_BLACK);
	auto white = this->GetCellNum(Cell_WHITE);

	auto ret = Cell_Empty;

	if (black != white)
	{
		ret = black > white ? Cell_BLACK : Cell_WHITE;
	}

	return ret;
}

BoardClass::Board BoardClass::GetBoard()const
{
	return this->pimpl->board;
}