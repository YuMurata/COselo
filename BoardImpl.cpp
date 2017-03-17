#include"BoardImpl.h"
#include"PutState.h"
BoardClass::Impl::Impl(const BoardSize &board_size)
	:board_size(board_size), cell_num(BoardClass::Cell_NUM) {}

void BoardClass::Impl::PutPieceAt(const CellCoord &coord, const int &color)
{
	auto &cell = this->board[coord.y][coord.x];

	if (color != Cell_Empty)
	{
		if (cell != Cell_Empty)
		{
			--this->cell_num[(color + 1) % 2];
		}

		++this->cell_num[color];
	}

	cell = color;
}