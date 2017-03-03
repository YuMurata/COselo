#pragma once

#include"BoardClass.h"

//�I�Z���N���X
//
//OseloClass(const BoardClass::CellNum &cell_num, const int &current_color);�@cell_num=�{�[�h�̑傫���Acurrent_color=�ŏ��̃^�[���̐F
//virtual ~OseloClass();
//std::pair<PutState,PutState> Init();�@�Ֆʂ̏�����
//void DrawBoard()const;�@�Ֆʂ̕`��i�R���\�[��
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