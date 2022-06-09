#pragma once
#include "basePlace.h"

class Headquarters :
	public basePlace
{
private:

	int enterEntity = 0;
	size_t nextProductionItr = 0;
	long long productedID = 0;
public:
	int nowEnemyID = -1;
	std::vector<baseWarrior*>production_list;
	std::vector<baseArms*>armsProduction_list;
public:
	Headquarters(int);

	inline int getEnterEntity()const { return enterEntity; }

	int getOccupier()const;
	bool ifHaveSeat(int);
	baseWarrior* enterWarrior(baseWarrior*);
	baseWarrior* exitWarrior(baseWarrior*);
	void BackLiveToHeader();

	void Updata();
	void productedWars();
	void OnHourEnd();
};

