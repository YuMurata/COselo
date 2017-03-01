#include"AgentImpl.h"

void QLTLAgent::Put()
{
	this->base_pimpl->DispTurn();

	auto s = this->base_pimpl->oselo->GetBoard();

	auto a = this->qltl_pimpl->qltl_obj.Learn(s);
	if (!this->qltl_pimpl->learn_flag)
	{
		a = this->qltl_pimpl->qltl_obj.BestAction(s);
	}
	this->base_pimpl->oselo->Put(a);
}

void QLTLAgent::Review(const CellCoord &coord)
{
	this->qltl_pimpl->qltl_obj.QUpDate(this->base_pimpl->oselo->GetBoard(), coord);
}