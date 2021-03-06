#pragma once

#include"BoardClass.h"
#include<Coordinate.h>
class BoardClass::Impl
{
public:
	Board board;//盤面
	BoardSize board_size;//盤面のサイズ
	std::vector<int> cell_num;

	std::stack<PutState> undo;
	std::stack<PutState> redo;

	void PutPieceAt(const CellCoord &coord, const int &color);

	Impl(const BoardSize &board_size);
};
