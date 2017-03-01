// OseloSystem.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include"OseloClass.h"

#include"UserAgent.h"
#include"RandomAgent.h"
#include"QAgent.h"
#include"QLTLAgent.h"

using namespace std;

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

int main()
{
	shared_ptr<OseloClass> obj(new OseloClass(8, BoardClass::Cell_BLACK));

	unique_ptr<QLTLAgent> black(new QLTLAgent(obj, BoardClass::Cell_BLACK, 64));
	//unique_ptr<QAgent> black(new QAgent(obj, BoardClass::Cell_BLACK));
	//unique_ptr<RandomAgent> white(new RandomAgent(obj, BoardClass::Cell_WHITE));
	unique_ptr<QAgent> white(new QAgent(obj, BoardClass::Cell_WHITE));

	//black->LoadFile("black.ql");
	//white->LoadFile("white.ql");

	unique_ptr<BaseAgent> agents[BoardClass::Cell_NUM];

	agents[black->GetColor()] = move(black);
	agents[white->GetColor()] = move(white);

	const int learn_num = 100;
	
	unique_ptr<BaseVS> writer(new VSRandom);
	
	if (typeid(*agents[1]) != typeid(RandomAgent))
	{
		writer.reset(new VSRL);
	}


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

	//dynamic_cast<QLTLAgent*>(agents[0].get())->WriteFile(("black.ql"));
	//dynamic_cast<QAgent*>(agents[1].get())->WriteFile(("white.ql"));

	//cout << win_count[BoardClass::Cell_BLACK+1] << ":" << win_count[BoardClass::Cell_WHITE+1] << ":" << win_count[BoardClass::Cell_Empty + 1]<< endl;

	string file_name;

	if (typeid(*writer) == typeid(VSRandom))
	{
		file_name = typeid(*agents[0]).name() + string("_win.xls");
	}
	else
	{
		file_name = "qltl_vs_q.xls";
	}

	writer->Write(file_name);

#ifndef NDEBUG
	_getch();
#endif // !NDEBUG


    return 0;
}