#pragma once
#include"PutState.h"
#include"OseloClass.h"
#include<memory>

class BaseAgent
{
protected:
	class Impl;
	std::unique_ptr<Impl> base_pimpl;

public:
	static int win;

	//oseloにobj,my_colorにcolorを設定
	BaseAgent(const std::shared_ptr<OseloClass> &obj, const int &color);
	virtual ~BaseAgent();
	virtual void Put() = 0;

	virtual void Review(const CellCoord &a)
	{

	}

	int GetColor()const;
};