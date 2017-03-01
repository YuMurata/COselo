#include"OseloImpl.h"
#include"OseloSystem.h"

using namespace std;

pair<PutState,PutState>OseloClass::Init()
{
	return OseloSystem::Init(&this->pimpl->board);
}

PutState OseloClass::Put(const CellCoord &coord)
{
	return OseloSystem::Put(&this->pimpl->board, coord, this->pimpl->current_turn);
}

pair<PutState,PutState> OseloSystem::Init(BoardClass *board)
{
	auto ret = board->Init();
	return ret;
}

PutState OseloSystem::Put(BoardClass *board,const CellCoord &coord,const int &color)
{
	Flip flip;
	OseloSystem::CheckPut(*board, coord, color, &flip);

	PutState ret;
	ret.color = color;
	ret.flip = flip;
	ret.put = coord;

	board->PutPiecesAt(ret);

	return ret;
}