#pragma once
#include"BaseAgent.h"
#include<string>

class QLTLAgent :public BaseAgent 
{
private:
	class Impl;
	std::unique_ptr<Impl> qltl_pimpl;

public:
	QLTLAgent(const std::shared_ptr<OseloClass> &obj, const int &color, const int &cell_num, const bool &learn_flag = true);

	virtual ~QLTLAgent();

	virtual void Put();

	void Review(const CellCoord &coord);

	void LoadFile(const std::string &file_name);

	void WriteFile(const std:: string &file_name);
};
