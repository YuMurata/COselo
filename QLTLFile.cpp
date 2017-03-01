#include"AgentImpl.h"
#include"QLTLAgent.h"
#include<string>

using namespace std;

void QLTLAgent::LoadFile(const string &file_name)
{
	this->qltl_pimpl->qltl_obj.LoadFile(file_name);
}

void QLTLAgent::WriteFile(const string &file_name)
{
	this->qltl_pimpl->qltl_obj.WriteFile(file_name);
}