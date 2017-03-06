// OseloSystem.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include"OseloClass.h"

#include"UserAgent.h"
#include"RandomAgent.h"
#include"QAgent.h"
#include"QLTLAgent.h"

using namespace std;

enum VS_TYPE
{
	QL,
	QLTL,
	QLTL_QL,
	NUM,
};

struct WinRate
{
	int game_count;
	vector<double> win_rate;

	WinRate(const int &game_count, const vector<double> rate)
		:game_count(game_count), win_rate(rate) {}
};

struct BaseVS
{
	vector<WinRate> data;
	int win_count[BoardClass::Cell_NUM];
	
	void Add(const int &game_count)
	{
		vector<double> rate({ 1.*win_count[BoardClass::Cell_BLACK] / game_count,1.*win_count[BoardClass::Cell_WHITE] / game_count });
		this->data.push_back(WinRate(game_count, rate));
	}

	virtual void Write(const string &file_name) = 0;
};

struct VSRandom:public BaseVS
{
	void Write(const string &file_name)
	{
		ofstream ofs(file_name);

		auto func = [&ofs](const WinRate &x)
		{
			ofs << x.game_count << "\t" << x.win_rate[BoardClass::Cell_BLACK] << endl;
		};

		for_each(begin(data), end(data), func);
	}
};

struct VSRL:public BaseVS
{
	void Write(const string &file_name)
	{
		ofstream ofs(file_name);

		auto func = [&ofs](const WinRate &x)
		{
			ofs << x.game_count << "\t" << x.win_rate[BoardClass::Cell_BLACK] << "\t" << x.win_rate[BoardClass::Cell_WHITE] << endl;
		};

		for_each(begin(data), end(data), func);
	}
};

void QLVSRandom(const shared_ptr<OseloClass> &obj,unique_ptr<BaseAgent> agents[])
{
	agents[BoardClass::Cell_BLACK].reset(new QAgent(obj, BoardClass::Cell_BLACK));
	agents[BoardClass::Cell_WHITE].reset(new RandomAgent(obj, BoardClass::Cell_WHITE));
}

void QLTLVSRandom(const shared_ptr<OseloClass> &obj, unique_ptr<BaseAgent> agents[])
{
	agents[BoardClass::Cell_BLACK].reset(new QLTLAgent(obj, BoardClass::Cell_BLACK,64));
	agents[BoardClass::Cell_WHITE].reset(new RandomAgent(obj, BoardClass::Cell_WHITE));
}

void QLTLVSQL(const shared_ptr<OseloClass> &obj, unique_ptr<BaseAgent> agents[])
{
	agents[BoardClass::Cell_BLACK].reset(new QLTLAgent(obj, BoardClass::Cell_BLACK, 64));
	agents[BoardClass::Cell_WHITE].reset(new QAgent(obj, BoardClass::Cell_WHITE));
}

void GetAgents(const shared_ptr<OseloClass> &obj, unique_ptr<BaseAgent> agents[], const int &vs_type)
{
	switch (vs_type)
	{
	case QL:
		QLVSRandom(obj, agents);
		break;
	case QLTL:
		QLTLVSRandom(obj, agents);
		break;
	case QLTL_QL:
		QLTLVSQL(obj, agents);
		break;
	}
}

void Load(const unique_ptr<BaseAgent> agents[],const int &vs_type)
{
	BaseQ *black_agent = nullptr; 
	BaseQ *white_agent = nullptr; 

	switch (vs_type)
	{
	case QL:
		black_agent= dynamic_cast<QAgent*>(agents[0].get());
		break;
	case QLTL:
		black_agent = dynamic_cast<QLTLAgent*>(agents[0].get());
		break;
	case QLTL_QL:
		black_agent = dynamic_cast<QLTLAgent*>(agents[0].get());
		white_agent = dynamic_cast<QAgent*>(agents[1].get());
		break;
	}

	if (black_agent != nullptr)
	{
		cout << "loading black.ql ..." << endl;
		//	black_agent->LoadFile("black.ql");
		cout << "complete\n" << endl;
	}

	if (white_agent != nullptr)
	{
		cout << "loading white.ql ..." << endl;
		//	white_agent->LoadFile("white.ql");
		cout << "complete\n" << endl;
	}
}

unique_ptr<BaseVS> GetWriter(const int &vs_type)
{
	switch (vs_type)
	{
	case QL:
		return unique_ptr<BaseVS>(new VSRandom);
	case QLTL:
		return unique_ptr<BaseVS>(new VSRandom);
	case QLTL_QL:
		return unique_ptr<BaseVS>(new VSRL);
	}
}

void MainLoop(const shared_ptr<OseloClass> &obj,const unique_ptr<BaseAgent> agents[],const unique_ptr<BaseVS> &writer)
{
	int learn_num = 100;

	cout << "num of learning >>" << flush;
	cin >> learn_num;

	for (int i = 1; i <= learn_num; ++i)
	{
		obj->Init();
		obj->DrawBoard();

		while (!obj->CheckFinish())
		{

			agents[obj->GetCurrent()]->Put();

			obj->ChangeTurn();
			if (!obj->CheckPutable())
			{
				obj->ChangeTurn();
			}

			obj->DrawBoard();
		}

		BaseAgent::win = obj->GetWin();
		if (BaseAgent::win != BoardClass::Cell_Empty)
		{
			++writer->win_count[BaseAgent::win];
		}

		writer->Add(i);

		cout << i << endl;

		PutState state;

		while ((state = obj->Undo()).IsPut())
		{
			agents[obj->GetCurrent()]->Review(state.put);
			obj->DrawBoard();
		}
		BaseAgent::win = BoardClass::Cell_Empty;
	}
}

void Save(const unique_ptr<BaseAgent> agents[],const int &vs_type)
{
	BaseQ *black_agent = nullptr;
	BaseQ *white_agent = nullptr;

	switch (vs_type)
	{
	case QL:
		black_agent = dynamic_cast<QAgent*>(agents[0].get());
		break;
	case QLTL:
		black_agent = dynamic_cast<QLTLAgent*>(agents[0].get());
		break;
	case QLTL_QL:
		black_agent = dynamic_cast<QLTLAgent*>(agents[0].get());
		white_agent = dynamic_cast<QAgent*>(agents[1].get());
		break;
	}
	if (black_agent != nullptr)
	{
		cout << "saving black.ql ..." << endl;
		black_agent->WriteFile("black.ql");
		cout << "complete\n" << endl;
	}

	if (white_agent != nullptr)
	{
		cout << "saving white.ql ..." << endl;
		white_agent->WriteFile("white.ql");
		cout << "complete\n" << endl;
	}
}

void GraphSave(const unique_ptr<BaseVS> &writer, const int &vs_type)
{
	string file_name;

	switch (vs_type)
	{
	case QL:
		file_name = "QL_win";
		break;
	case QLTL:
		file_name = "QLTL_win";
		break;
	case QLTL_QL:
		file_name = "QLTL_vs_QL";
		break;
	}

	file_name += ".xls";

	writer->Write(file_name);
}


int main()
{
	shared_ptr<OseloClass> obj(new OseloClass(8, BoardClass::Cell_BLACK));
	unique_ptr<BaseAgent> agents[BoardClass::Cell_NUM];

	int vs_type = QLTL;

	GetAgents(obj, agents, vs_type);
	
	Load(agents,vs_type);

	auto writer = GetWriter(vs_type);

	MainLoop(obj, agents, writer);

	Save(agents,vs_type);

	GraphSave(writer, vs_type);

#ifndef NDEBUG
	_getch();
#endif // !NDEBUG


    return 0;
}