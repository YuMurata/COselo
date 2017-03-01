#include"OseloImpl.h"

OseloClass::Impl::Impl(const BoardClass::CellNum &cell_num, const int &current_turn)
	:board(cell_num), current_turn(current_turn), init_turn(current_turn) {}
