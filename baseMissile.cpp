#include "baseMissile.h"
#include "baseWarrior.h"
#include "basePlace.h"

basePlace* baseMissile::getHurtCity()
{
	return fireWarrior->getNextCity();
}

void baseMissile::_fire()
{
	hurtPlace = this->fireWarrior->getNextCity();
	if (!hurtPlace->getOccupier() == fireWarrior->getCamp())
	{
		for (auto i : hurtPlace->Warriors())
		{
			if (i != nullptr)
				if (i->Action())
					if (i->getCamp() != fireWarrior->getCamp())
					{
						i->_getHart(power, false);
						i->_beShoot(this);
						break;
					}
		}
		this->durable--;
		Fire(hurtPlace);
	}
}

