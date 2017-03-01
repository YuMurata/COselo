#pragma once

#include"BoardClass.h"

class BoardClass::Impl
{
public:
	Board board;//盤面
	CellNum board_size;//盤面のサイズ
	std::vector<int> cell_num;

	std::stack<PutState> undo;
	std::stack<PutState> redo;

	void PutPieceAt(const CellCoord &coord, const int &color);

	Impl(const CellNum &board_size);
	//~Impl() { std::cout << "free board" << std::endl; }
};
