#pragma once

#include"PutState.h"

class BoardClass
{
public:
using CellNum = TCoordinate<int>;

using Board = std::vector<std::vector<int>>;
using State = std::vector<std::pair<CellCoord, int>>;

private:
	class Impl;
	std::unique_ptr<Impl> pimpl;

public:
	//マス目の状態
	enum CellState
	{
		Cell_Empty=-1,
		Cell_BLACK,
		Cell_WHITE,
		Cell_NUM,
	};

//Init

	BoardClass();

	//cell_numにcell_numを設定
	BoardClass(const CellNum &board_size);

	BoardClass(const BoardClass &board);

	~BoardClass();

	//盤面の初期化
	std::pair<PutState,PutState> Init();

//Put

	//座標coordに色colorを設定
	void PutPiecesAt(const PutState &state);

//Get

	//盤面の大きさを取得
	CellNum GetBoardSize()const;

	//座標coordの状態を取得
	int GetCellState(const CellCoord &coord)const;

	//色colorの石数を取得
	int GetCellNum(const int &color)const;

	//多いほうの色を取得
	int GetOften()const;

	Board GetBoard()const;

	bool operator==(const BoardClass &obj)const;

	bool operator<(const BoardClass &obj)const;

	friend std::ostream& operator<<(std::ostream&, const BoardClass&);

	BoardClass& operator=(const std::vector<std::vector<int>> &input);

	BoardClass& operator=(const BoardClass &board);

	PutState Undo();

	bool Redo();
};