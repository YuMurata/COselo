#pragma once

#include"PutState.h"

using BoardSize = TCoordinate<int>;
using Board = std::vector<std::vector<int>>;

class BoardClass
{
private:
	class Impl;
	std::unique_ptr<Impl> pimpl;

public:
	//�}�X�ڂ̏��
	enum CellState
	{
		Cell_Empty=-1,
		Cell_BLACK,
		Cell_WHITE,
		Cell_NUM,
	};

//Init

	BoardClass();

	//cell_num��cell_num��ݒ�
	BoardClass(const BoardSize &board_size);

	BoardClass(const BoardClass &board);

	~BoardClass();

	//�Ֆʂ̏�����
	std::pair<PutState,PutState> Init();

//Put

	//���Wcoord�ɐFcolor��ݒ�
	void PutPiecesAt(const PutState &state);

//Get

	//�Ֆʂ̑傫�����擾
	BoardSize GetBoardSize()const;

	//���Wcoord�̏�Ԃ��擾
	int GetCellState(const CellCoord &coord)const;

	//�Fcolor�̐ΐ����擾
	int GetCellNum(const int &color)const;

	//�����ق��̐F���擾
	int GetOften()const;

	Board GetBoard()const;

	BoardClass GetReverse()const;

	bool operator==(const BoardClass &obj)const;

	bool operator<(const BoardClass &obj)const;

	friend std::ostream& operator<<(std::ostream&, const BoardClass&);

	friend std::wostream& operator<<(std::wostream&, const BoardClass&);

	BoardClass& operator=(const std::vector<std::vector<int>> &input);

	BoardClass& operator=(const BoardClass &board);

	PutState Undo();

	bool Redo();
};