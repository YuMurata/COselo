#include"BoardImpl.h"

using namespace std;

bool BoardClass::operator==(const BoardClass &obj)const
{
	return this->pimpl->board == obj.pimpl->board;
}

bool BoardClass::operator<(const BoardClass &obj)const
{
	return this->pimpl->board < obj.pimpl->board;
}


ostream& operator<<(ostream &stream, const BoardClass &board)
{
	ostream_iterator<int> out(stream, ",");

	auto board_mat = board.GetBoard();

	auto func = [&out](const vector<int> &line)
	{
		copy(begin(line), end(line), out);
	};

	for_each(begin(board_mat), end(board_mat), func);

	return stream;
}

BoardClass& BoardClass::operator=(const Board &input)
{
	this->pimpl->board = input;
	this->pimpl->board_size = BoardSize(size(input[0]), size(input));

	return *this;
}

BoardClass& BoardClass::operator=(const BoardClass &board)
{
	this->pimpl.reset(new Impl(*board.pimpl));
	return *this;
}
