#pragma once

#include"BoardClass.h"

//オセロクラス
//
//OseloClass(const BoardClass::CellNum &cell_num, const int &current_color);　cell_num=ボードの大きさ、current_color=最初のターンの色
//virtual ~OseloClass();
//std::pair<PutState,PutState> Init();　盤面の初期化
//void DrawBoard()const;　盤面の描画（コンソール
//bool CheckFinish()const;
//int GetCurrent()const;
//void ChangeTurn();
//bool CheckPutable()const;
//PutState Put(const CellCoord &coord);
//BoardClass GetBoard()const;
//PutState Undo();
//bool Redo();
//int GetWin()const;
class OseloClass
{
private:
	class Impl;
	std::unique_ptr<Impl> pimpl;
	
public:
	OseloClass(const BoardSize &board_size, const int &init_color=BoardClass::Cell_BLACK);
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