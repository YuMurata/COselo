#include"AgentImpl.h"
#include"UserAgent.h"
#include"RandomAgent.h"
#include"OseloSystem.h"

#include<iostream>

using namespace std;

void UserAgent::Put()
{
	this->base_pimpl->DispTurn();

	CellCoord coord;
	cout << "put x y" << endl;
	cin >> coord.x >> coord.y;
	coord.y -= 'a';

	while (!this->base_pimpl->oselo->Put(coord).IsPut())
	{
		cout << "put error! try again!" << endl;
		cout << "put x y" << endl;
		cin >> coord.x >> coord.y;
		coord.y -= 'a';
	}
}

void RandomAgent::Put()
{
	this->base_pimpl->DispTurn();

	auto as = OseloSystem::GetPutable(this->base_pimpl->oselo->GetBoard(), this->base_pimpl->my_color);

	shuffle(begin(as), end(as), this->mt);

	this->base_pimpl->oselo->Put(as.front());
}

int BaseAgent::GetColor()const
{
	return this->base_pimpl->my_color;
}