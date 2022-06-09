#include "baseArms.h"
#include "baseWarrior.h"

baseArms* baseArms::_factionArm(baseWarrior* w)
{
	baseArms* arm = FactionArm();
	arm->Holder = w;
	if (!w->_addArms(arm))
	{
		delete arm;
		return nullptr;
	}
	else
	{
		return arm;
	}
}




