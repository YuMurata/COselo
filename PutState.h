#pragma once

#include"stdafx.h"

#include<Coordinate.h>

#include<vector>
#include<functional>

using CellCoord = TCoordinate<int>;

class PutState
{
public:
	CellCoord put;//置いた座標
	std::vector<CellCoord> flip;//裏返した座標
	int color;//色

	PutState()
		:PutState(CellCoord(), std::vector<CellCoord>(), 0) {}

	PutState(const CellCoord &put, const std::vector<CellCoord> &flip, const int &color)
		:put(put), flip(flip), color(color) {}

	bool IsPut()const
	{
		return !this->flip.empty();
	}
};