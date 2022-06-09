#include "Headquarters.h"
#include "CityMap.h"
#include "faction.h"
#include "GameManager.h"

Headquarters::Headquarters(int i)
{
	campfig = i;
	name = "Headqurters " + std::to_string(i);
	life = 200;
}

int Headquarters::getOccupier()const
{
	return campfig;
}

bool Headquarters::ifHaveSeat(int)
{
	return true;
}

baseWarrior* Headquarters::enterWarrior(baseWarrior* war)
{
	warriors.push_back(war);
	war->location = this;
	if (war->getCamp() != campfig)
		++enterEntity;
	if (enterEntity >= GameManager::headerMaxHealth)
	{
		Log("has takend!");
		SetAction(false);
	}
	return war;
}

baseWarrior* Headquarters::exitWarrior(baseWarrior* war)
{
	for (auto i = warriors.begin(); i != warriors.end(); i++)
		if (*i == war)
		{
			warriors.erase(i);
			return war;
		}
	return nullptr;
}

void Headquarters::BackLiveToHeader()
{
}

void Headquarters::Updata()
{

	if (wow::worldTime.getMin() == 0)
		productedWars();
}

void Headquarters::productedWars()
{
	if (!production_list.empty())
	{

		for (size_t i = 0; i < production_list.size(); ++i)
		{

			if (production_list[nextProductionItr]->DefaultHealth() <= life)
			{
				baseWarrior* war = this->enterWarrior(production_list[nextProductionItr]->_factionWar(this));
				life -= production_list[nextProductionItr]->DefaultHealth();
				war->setHealth(war->DefaultHealth());
				war->setAttack(war->DefaultAttack());
				war->name = "No." + std::to_string(productedID) + (campfig == 0 ? " blue" : " red") + " warrior";
				Log(war->name + " bron! last life " + std::to_string(life));
				for (int armI = 0; armI < production_list[nextProductionItr]->getmaxArmsNum(); armI++)
				{
					baseArms* arm = armsProduction_list[(productedID + armI) % armsProduction_list.size()]->_factionArm(war);
					if (arm->ifDestroy())
						arm->SetAction(false);
				}
				nextProductionItr = (++nextProductionItr) % production_list.size();
				productedID++;
				war->Start();
				break;
			}
			else
			{
				nextProductionItr++;
				if (nextProductionItr >= production_list.size())
					nextProductionItr = 0;
			}
		}
	}

}

void Headquarters::OnHourEnd()
{
	Log("have life:" + std::to_string(life));
}
