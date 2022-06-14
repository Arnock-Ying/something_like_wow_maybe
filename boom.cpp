#include "boom.h"
#include "faction.h"
#include "basePlace.h"

baseArms* Boom::FactionArm()
{
	return new Boom();
}

bool Boom::ifDestroy()
{
	return ifDis;
}

void Boom::Updata()
{
	if (wow::worldTime == 38)
	{
		if (Holder == nullptr)return;
		for (auto w : Holder->location->Warriors())
		{
			if (w != nullptr)if (w->Action() && Holder->Action())
				if (Holder->getHealth() <= w->getAttack() + w->getArmAttack())
				{
					//Holder->SetAction(false);
					//w->SetAction(false);
					Log("boom!" + w->name + "&" + Holder->name);
					Holder->drawPut(Holder->name + " use boom killed " + w->name);
					ifDis = true;
					break;
				}
		}
	}
}

std::string Boom::to_string()
{
	return "Boom";
}
