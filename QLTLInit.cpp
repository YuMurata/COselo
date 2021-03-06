#include"AgentImpl.h"
#include"OseloSystem.h"

#include<StringPlus.h>
#include<sstream>
QLTLAgent::QLTLAgent(const shared_ptr<OseloClass> &obj, const int &color, const int &cell_num, const bool &learn_flag )
	: BaseAgent(obj, color),qltl_pimpl(new Impl( cell_num,learn_flag))
{
	using S = Impl::S;
	using A = Impl::A;
	using DataType = Impl::DataType;

	using QLTL = QLTLClass<S,A,DataType >;

	using DataList = QLTL::DataList;

	using SA = QLTL::SA;
	using Q = QLTL::Q;
	using SAQ = QLTL::SAQ;

	using QTable = QLTL::QTable;

	using R = QLTL::FuncR;
	using T = QLTL::FuncT;
	using As = QLTL::FuncAs;
	using Load = QLTL::FuncLoad;
	using Write = QLTL::FuncWrite;
	using S_LSH = QLTL::SToLSH;
	using LSH_S = QLTL::LSHToS;

	auto func_r = [&](const BoardClass &s)
	{
		int ampl = -1;
		int reward = s.GetCellNum(this->base_pimpl->my_color);


		if (this->win == this->base_pimpl->my_color)
		{
			ampl = 10;
		}
		else if (this->win == BoardClass::Cell_Empty)
		{
			ampl = -1;
		}
		else
		{
			ampl = -10;
		}

		//auto ret=reward*ampl;
		auto ret = ampl;
		return ret;
	};

	T func_t = [&](const S &s, const A &a)
	{
		auto board = OseloSystem::GetEstimate(s, a, this->base_pimpl->my_color).GetReverse();

		auto best_a = this->qltl_pimpl->qltl_obj.BestAction(board);

		auto ret = OseloSystem::GetEstimate(board, best_a, this->base_pimpl->my_color).GetReverse();

		return ret;
	};

	As func_as = [&](const BoardClass &s)
	{
		return OseloSystem::GetPutable(s, this->base_pimpl->my_color);
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
			std::stringstream is;
			is << saq.first.first << saq.first.second << saq.second;

			auto input = is.str();
			auto ret = SplitA(input);

			return ret;
		};

		transform(begin(q_table), end(q_table), begin(*ret), func);

		//return ret;
	};

	S_LSH s_lsh = [&](const S &s)
	{
		auto board_size = this->base_pimpl->oselo->GetBoard().GetBoardSize();
		auto cell_num = board_size.x*board_size.y;
		QLTL::DataList ret;
		ret.reserve(cell_num);

		auto board = s.GetBoard();

		auto func = [&ret](const vector<int> &line)
		{
			ret.insert(end(ret), begin(line), end(line));
		};

		for_each(begin(board), end(board), func);

		return ret;
	};

	LSH_S lsh_s = [&](const DataList &data)
	{
		auto board_size = this->base_pimpl->oselo->GetBoard().GetBoardSize();
		vector<vector<int>> board_mat(board_size.y, vector<int>(board_size.x));

		auto itr = begin(data);
		for (auto &i : board_mat)
		{
			for (auto &j : i)
			{
				j = *(++itr);
			}
		}

		BoardClass ret;
		ret = board_mat;

		return ret;
	};

	this->qltl_pimpl->qltl_obj.SetFunc(func_r, func_t, func_as, func_load, func_write, s_lsh, lsh_s);
}

QLTLAgent::~QLTLAgent() = default;
