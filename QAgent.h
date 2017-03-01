#pragma once

#include"BaseAgent.h"
#include<string>

class QAgent :public BaseAgent
{
private:
	class Impl;
	std::unique_ptr<Impl> q_pimpl;
	
public:
	void Put();

	QAgent(const std::shared_ptr<OseloClass> &obj, const int &color);
	virtual ~QAgent();

	void Review(const CellCoord &coord);

	void LoadFile(const std::string &file_name);

	void WriteFile(const std::string &file_name);
};