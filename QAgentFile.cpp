#include"QAgent.h"
#include"AgentImpl.h"

void QAgent::LoadFile(const string &file_name)
{
	this->q_pimpl->ql_obj.LoadFile(file_name);
}

void QAgent::WriteFile(const string &file_name)
{
	this->q_pimpl->ql_obj.WriteFile(file_name);
}