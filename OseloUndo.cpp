#include"OseloImpl.h"
#include"OseloSystem.h"

PutState OseloClass::Undo()
{
	auto state=OseloSystem::Undo(&this->pimpl->board);
	this->ChangeTurn();
	if (!this->CheckPutable())
	{
		this->ChangeTurn();
	}

	return state;
}

bool OseloClass::Redo()
{
	return OseloSystem::Redo(&this->pimpl->board);
}

PutState OseloSystem::Undo(BoardClass *board)
{
	return board->Undo();
}

bool OseloSystem::Redo(BoardClass *board)
{
	return board->Redo();
}