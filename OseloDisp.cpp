#include"OseloImpl.h"
#include"OseloSystem.h"

#include"Define.h"

using namespace std;

//盤面の描画
void OseloClass::DrawBoard()const
{
	OseloSystem::DrawBoard(this->pimpl->board);
}

//盤面の描画
void OseloSystem::DrawBoard(const BoardClass &board)
{
#ifndef NO_DISP

	const char *cell[] =
	{
		"□","○","●",
	};

	const char line[] = "------------------";

	cout << endl << line << line << endl << endl;

	auto board_size = board.GetBoardSize();

	cout << "  ";
	for (int x = 0; x < board_size.x; ++x)
	{
		cout << x << "  ";
	}
	cout << endl;

	CellCoord coord;
	for (coord.y = 0; coord.y < board_size.y; ++coord.y)
	{
		cout << char('a' + coord.y) << " ";
		for (coord.x = 0; coord.x < board_size.x; ++coord.x)
		{
			auto color = board.GetCellState(coord) + 1;
			cout << cell[color] << " ";
		}
		cout << char('a' + coord.y) << endl;
	}


	cout << "  ";
	for (int x = 0; x < board_size.x; ++x)
	{
		cout << x << "  ";
	}

	cout << endl << line << line << endl << endl;

#endif
}

//石の数を表示
void OseloSystem::DispCells(const int &black_count, const int &white_count)
{
	cout << "[BLACK]:" << black_count << endl;
	cout << "[WHITE]:" << white_count << endl;
}

//石を配置できない場合に呼び出す
void OseloSystem::Pass(const int &color)
{
	const char *turn_color[] =
	{
		"BLACK",
		"WHITE",
	};

	cout << "[" << turn_color[color - 1] << "] cant put !" << endl;
}