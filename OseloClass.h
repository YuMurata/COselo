#pragma once

#include"BoardClass.h"

class OseloClass
{
private:
	class Impl;
	std::unique_ptr<Impl> pimpl;
	
public:
	OseloClass(const BoardClass::CellNum &cell_num, const int &current_color);
	virtual ~OseloClass();

	std::pair<PutState,PutState> Init();

	void DrawBoard()const;
	
	bool CheckFinish()const;

	int GetCurrent()const;

	void ChangeTurn();

	bool CheckPutable()const;

	PutState Put(const CellCoord &coord);

	BoardClass GetBoard()const;

	PutState Undo();

	bool Redo();

	int GetWin()const;
};