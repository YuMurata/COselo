#include"AgentImpl.h"

#include"Define.h"

//Žè”Ô•\Ž¦
void BaseAgent::Impl::DispTurn()const
{
#ifndef NO_DISP
	const char *turn[] =
	{
		"BLACK",
		"WHITE",
	};

	cout << typeid(*this).name() << ":" << turn[this->my_color] << endl;
#endif
}

BaseAgent::Impl::Impl(const std::shared_ptr<OseloClass> &obj, const int &color)
	:oselo(obj), my_color(color) {}

QLTLAgent::Impl::Impl(const int &all_cell_num,const bool &learn_flag)
	:qltl_obj(all_cell_num),learn_flag(learn_flag) {}
