#pragma once
#include "basePlace.h"
class City_small :
	public basePlace
{
private:
	static int idCount;
public:
	City_small();

	int getOccupier()const;
	bool ifHaveSeat(int);
	baseWarrior* enterWarrior(baseWarrior*);
	baseWarrior* exitWarrior(baseWarrior*);

	void OnHourEnd();
	void Updata();
};

