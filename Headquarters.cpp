#include "Headquarters.h"
#include "CityMap.h"
#include "faction.h"
#include "GameManager.h"

int Headquarters::BaseHealth = 200;
Headquarters::Headquarters(int i)
{
	campfig = i;
	name = std::string(i==0?"blue ":"red ") + "Headqurter";
	life = BaseHealth;
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
	{
		++enterEntity;
		war->drawPut(war->name + " enter " + name + "  with health= " + std::to_string(war->getHealth()) + " ,power= " + std::to_string(war->getAttack()));
	}
	if (enterEntity >= GameManager::headerMaxHealth)
	{
		Log("has takend!!!!!!!!\n--------------------");
		drawPut(name + " has been taken!");
		SetAction(false);
		GameManager::manager->iffinish = true;
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
	if (wow::worldTime == 55)
	{
		Log("show life " + std::to_string(life));
		drawPut(std::to_string(life) + " elements in " + name);
	}
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
				war->name = (campfig == 0 ? " blue " : " red ") + war->name + ' ' + std::to_string(productedID);
				Log(war->name + " bron! last life " + std::to_string(life));
				drawPut(war->name + " bron!");
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
