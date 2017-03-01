#pragma once

#include"BoardClass.h"

template<>
struct std::hash<BoardClass>
{	
	size_t operator()(const BoardClass &s) const
	{	
		auto board = s.GetBoard();
		const int C = 997;

		auto func1 = [&C](const size_t &left, const int &right)
		{
			return left*C + right;
		};

		auto func2 = [&func1](const size_t &left, const std::vector<int> &right)
		{
			return accumulate(begin(right), end(right), left, func1);
		};

		auto ret=std::accumulate(begin(board), end(board), 0, func2);

		return ret;
	}
};

template<>
struct std::hash<CellCoord>
{
	size_t operator()(const CellCoord &a) const
	{
		const auto &coord = a;
		const int C = 997;

		auto ret = C*coord.x+coord.y;

		return ret;
	}
};