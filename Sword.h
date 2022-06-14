#pragma once
#include "baseArms.h"
class Sword :
	public baseArms
{
public:
	baseArms* FactionArm();
public:
	bool ifDestroy();
	void OnUsing(baseWarrior*);
	std::string to_string() { return "Sword(" + std::to_string(power) + ")"; }
};

