#pragma once

class BaseQ
{
public:
	virtual void LoadFile(const std::string &file_name) = 0;

	virtual void WriteFile(const std::string &file_name)=0;
};