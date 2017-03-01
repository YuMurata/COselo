#include"AgentImpl.h"
#include"OseloSystem.h"

#include<algorithm>
#include<StringPlus.h>

QAgent::QAgent(const shared_ptr<OseloClass> &obj, const int &color)
	: BaseAgent(obj, color),q_pimpl(new Impl)
{
	using S = BoardClass;
	using A = CellCoord;
	using QL = QLClass<S, A>;
	using SA = QL::SA;
	using Q = QL::Q;
	using SAQ = QL::SAQ;

	using QTable = QL::QTable;

	using R = QL::FuncR;
	using T = QL::FuncT;
	using As = QL::FuncAs;
	using Load = QL::FuncLoad;
	using Write = QL::FuncWrite;
	

	auto func_r = [&](const S &s)
	{
		int ampl = 1;
		int reward = s.GetCellNum(this->base_pimpl->my_color);


		if (this->win == this->base_pimpl->my_color)
		{
			ampl = 10;
		}
		else if (this->win == BoardClass::Cell_Empty)
		{
			ampl = 1;
		}
		else
		{
			ampl = -10;
		}


		return reward*ampl;
	};

	T func_t = [&](const S &s, const A &a)
	{
		auto ret = OseloSystem::GetEstimate(s, a, this->base_pimpl->my_color);
		return ret;
	};

	As func_as = [&](const S &s)
	{
		auto ret = OseloSystem::GetPutable(s, this->base_pimpl->my_color);
		return ret;
	};

	Load func_load = [&](const vector<vector<string>> &data_list)
	{
		vector<SAQ> ret(size(data_list));

		auto board_size = this->base_pimpl->oselo->GetBoard().GetBoardSize();

		auto s_size = board_size.x*board_size.y;
		auto a_size = 2;

		auto func = [&board_size, a_size](const vector<string> &input)
		{
			SAQ ret;
			auto &s = ret.first.first;
			auto &a = ret.first.second;
			auto &q = ret.second;

			auto itr = begin(input);

			vector<vector<int>> board(board_size.y);

			auto ret_board = [](const vector<string> &str)
			{
				vector<int> ret(size(str));

				transform(begin(str), end(str), begin(ret), [](const string &str) {return stoi(str); });
				return ret;
			};

			for (int y = 0; y < board_size.y; ++y)
			{
				auto last = itr + board_size.x;
				board[y] = ret_board(vector<string>(itr, last));

				itr = last;
			}

			s = board;
			a = CellCoord(stoi(*itr), stoi(*(itr + 1)));

			itr += a_size;

			q = stod(*itr);

			return ret;
		};

		transform(begin(data_list), end(data_list), begin(ret), func);

		return ret;
	};

	Write func_write = [](const QTable &q_table, vector<vector<string>> *ret)
	{
		string s;
		string a;
		string q;

		ret->resize(size(q_table));

		auto func = [](const pair<SA, double> &saq)
		{
			stringstream is;
			is << saq.first.first << saq.first.second << saq.second;

			auto input = is.str();
			vector<string> ret = SplitA(input);

			return ret;
		};

		transform(begin(q_table), end(q_table), begin(*ret), func);

		//return ret;
	};

	this->q_pimpl->ql_obj.SetFunc(func_r, func_t, func_as, func_load, func_write);
}

QAgent::~QAgent() = default;