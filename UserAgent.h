#pragma once

#include"BaseAgent.h"

class UserAgent :public BaseAgent
{
public:
	//oseloにobj,my_colorにcolorを設定
	UserAgent(const std::shared_ptr<OseloClass> &obj, const int &color);

	//ユーザが石を置く
	void Put();
};