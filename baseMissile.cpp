#include "baseMissile.h"
#include "baseWarrior.h"
#include "basePlace.h"

basePlace* baseMissile::getHurtCity()
{
	return Holder->getNextCity();
}

void baseMissile::_fire()
{
	baseWarrior* killWar = nullptr;
	hurtPlace = this->Holder->getNextCity();
	if (hurtPlace == nullptr) return;
	if (!hurtPlace->getOccupier() == Holder->getCamp())
	{
		for (auto i : hurtPlace->Warriors())
		{
			if (i != nullptr)
				if (i->Action())
					if (i->getCamp() != Holder->getCamp())
					{
						i->_getHart(power, false);
						i->_beShoot(this);
						if (i->getHealth() <= 0)killWar = i;
						break;
					}
		}
		this->durable--;
		Holder->drawPut(Holder->name + " shot " + (killWar == nullptr ? "." : ("kill " + killWar->name)));
		Fire(hurtPlace);
	}
}


