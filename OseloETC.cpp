#include"OseloImpl.h"
#include"OseloSystem.h"

OseloClass::OseloClass(const BoardSize &board_size, const int &current_turn)
	:pimpl(new Impl(board_size, current_turn)) {}

OseloClass::~OseloClass() = default;

//turn_color‚Ì”½“]
void OseloClass::ChangeTurn()
{
	OseloSystem::ChangeTurn(&this->pimpl->current_turn);
}

//turn_color‚Ì”½“]
void OseloSystem::ChangeTurn(int *turn_color)
{
	*turn_color = ((*turn_color)+1) % 2;
}