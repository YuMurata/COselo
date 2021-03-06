#include"BoardImpl.h"

using namespace std;

//座標coordに色colorを設定
void BoardClass::PutPiecesAt(const PutState &state)
{
	const int &color = state.color;

	this->pimpl->PutPieceAt(state.put, color);
	
	for (auto &i : state.flip)
	{
		this->pimpl->PutPieceAt(i, color);
	}

	this->pimpl->undo.push(state);

	if (!this->pimpl->redo.empty())
	{
		this->pimpl->redo = stack<PutState>();
	}
}
