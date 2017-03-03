#pragma once

#include"OseloClass.h"

class OseloClass::Impl
{
public:
	BoardClass board;
	int current_turn;
	const int init_turn;

	Impl(const BoardSize &cell_num, const int &current_turn);
};