#include"BoardImpl.h"

PutState BoardClass::Undo()
{
	if (this->pimpl->undo.empty())
	{
		return PutState();
	}

	PutState state = this->pimpl->undo.top();

	this->pimpl->PutPieceAt(state.put, Cell_Empty);

	const int &enemy_color = (state.color + 1) % 2;

	for (auto &i : state.flip)
	{
		this->pimpl->PutPieceAt(i, enemy_color);
	}

	this->pimpl->redo.push(state);
	this->pimpl->undo.pop();

	return state;
}

bool BoardClass::Redo()
{
	if (this->pimpl->redo.empty())
	{
		return false;
	}

	PutState state = this->pimpl->redo.top();

	const int &color = state.color;

	this->pimpl->PutPieceAt(state.put, color);


	for (auto &i : state.flip)
	{
		this->pimpl->PutPieceAt(i, color);
	}

	this->pimpl->undo.push(state);
	this->pimpl->redo.pop();

	return true;
}