#pragma once

#include"BaseAgent.h"

class UserAgent :public BaseAgent
{
public:
	//oselo‚Éobj,my_color‚Écolor‚ğİ’è
	UserAgent(const std::shared_ptr<OseloClass> &obj, const int &color);

	//ƒ†[ƒU‚ªÎ‚ğ’u‚­
	void Put();
};