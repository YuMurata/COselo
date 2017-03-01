#pragma once

#include"BaseAgent.h"
#include<Randomer.h>

class RandomAgent :public BaseAgent,Randomer
{
public:
	RandomAgent(const std::shared_ptr<OseloClass> &obj, const int &color);

	void Put();
};