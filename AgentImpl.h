#pragma once

#include"BaseAgent.h"
#include"QAgent.h"
#include"QLTLAgent.h"

#include"OseloClass.h"

#include"Hash.h"

#include"../../MachineLearning/ReinforcementLearning/QLearning/QLearning/QLClass.h"
#include"../../MachineLearning/ReinforcementLearning/QLearning/QLTL/QLTLClass.h"
#include<memory>

class BaseAgent::Impl
{
public:
	std::shared_ptr<OseloClass> oselo;
	int my_color;

	void DispTurn()const;

	Impl(const shared_ptr<OseloClass> &obj, const int &color);
};

class QAgent::Impl
{
public:
	using S = BoardClass;
	using A = CellCoord;

	QLClass<S,A> ql_obj;
};

class QLTLAgent::Impl
{
public:
	using S = BoardClass;
	using A = CellCoord;
	using DataType = int;

	QLTLClass<S, A, DataType> qltl_obj;
	bool learn_flag;

	Impl(const int &all_cell_num,const bool &learn_flag=true);
};