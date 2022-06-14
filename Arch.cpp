#include "Arch.h"

int Arch::basePower = 0;

baseArms* Arch::FactionArm()
{
	baseArms* arm = new Arch();
	arm->name = "Arch";
	return arm;
}

Arch::Arch()
{
	power = basePower;
}
