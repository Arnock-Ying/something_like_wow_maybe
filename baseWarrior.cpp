#include "baseWarrior.h"
#include "basePlace.h"
#include "Headquarters.h"
#include "GameManager.h"
#include "baseArms.h"
#include <string>
#include <locale>
#include <codecvt>

using namespace wow;
using namespace std;

const int RewardNum = 8;

std::list<baseWarrior*> baseWarrior::Warriors;

void baseWarrior::foreachUpdata()
{
	for (auto i : Warriors)
		if (i != nullptr)
			if (i->Action())
			{
				i->_updata();
			}
}

void baseWarrior::foreachHourStart()
{
	for (auto i : Warriors)
		if (i != nullptr)
			if (i->Action())
			{
				i->OnHourStart();
			}
}

void baseWarrior::foreachHourEnd()
{
	for (auto i : Warriors)
		if (i != nullptr)
			if (i->Action())
			{
				i->OnHourEnd();
			}
}

void baseWarrior::foreachUpdataStart()
{
	for (auto i : Warriors)
		if (i != nullptr)
			if (i->Action())
			{
				i->UpdataStart();
			}
}

void baseWarrior::foreachUpdataEnd()
{
	for (auto i : Warriors)
		if (i != nullptr)
			if (i->Action())
			{
				i->UpdataEnd();
			}
}

void baseWarrior::ResetMapState()
{
	for (auto i : Warriors)
	{
		;
	}
}

void baseWarrior::foreachMove()
{
	for (auto i : Warriors)
		if (i != nullptr)
			if (i->Action())
			{
				i->_move();
			}
}

void baseWarrior::foreachGetReward()
{
	for (auto i = Warriors.rbegin(); i != Warriors.rend(); ++i)
	{
		baseWarrior* war = *i;
		if (war->ifWillGetReward)
		{
			Headquarters* header = GameManager::manager->cityMap->Header(war->campID);
			if (header->getLive() >= RewardNum)
			{
				war->health += RewardNum;
				header->addLive(-RewardNum);
			}
		}
	}
}

void baseWarrior::Clear()
{
	std::list<std::list<baseWarrior*>::iterator> deleteList;
	for (auto i = Warriors.begin(); i != Warriors.end(); i++)
	{
		if ((*i)->Action() == false)deleteList.push_back(i);
	}

	for (auto i : deleteList)
	{
		baseWarrior* ptr = *i;
		Warriors.erase(i);
		delete ptr;
	}
}

baseWarrior* baseWarrior::_factionWar(Headquarters* headquarters)
{
	baseWarrior* war = factionWar();
	war->location = headquarters;
	war->campID = headquarters->getCamp();
	war->destID = headquarters->nowEnemyID;
	Warriors.push_back(war);
	return war;
}

basePlace* baseWarrior::getNextCity()
{
	return GameManager::manager->cityMap->foundNextPlaceFromTo(this->location, campID);
}


baseWarrior::~baseWarrior()
{
	for (auto i = Warriors.begin(); i != Warriors.end(); i++)
	{
		if (*i == this)
		{
			Warriors.erase(i);
			break;
		}
	}
	if (!arms.empty())
		for (auto i : arms)
		{
			if (i != nullptr)
				delete i;
		}
}


int baseWarrior::getArmAttack()
{
	int sum = 0;
	for (auto i : arms)
	{
		if (i != nullptr)
			if (i->Action())
			{
				sum += i->getAttack();
			}
	}
	return sum;
}

void baseWarrior::Destroy()
{
	this->SetAction(false);
	location->exitWarrior(this);
}

void baseWarrior::_getHart(int n, bool ifChangeAction)
{
	health -= n;
	if (health <= 0)
	{
		health = 0;
		if (ifChangeAction)
			SetAction(false);
	}
}

void baseWarrior::_updata()
{
	Updata();
	for (auto a : arms)
		if (a != nullptr)
		{
			a->Updata();
			baseMissile* miss;
			if ((miss = dynamic_cast<baseMissile*>(a)) != nullptr)
			{
				if (miss->FireTime() == wow::worldTime)
				{
					miss->_fire();
				}
			}
		}
	if (wow::worldTime == 55)
	{
		drawPut(to_string());
	}

}

void baseWarrior::_move()
{
	basePlace* destPtr = GameManager::manager->cityMap->foundNextPlaceFromTo(location, destID);
	basePlace* locdPtr = location;
	if (destPtr != nullptr)
		if (destPtr->ifHaveSeat(campID))
			if (locdPtr->exitWarrior(this) != nullptr)
			{
				baseWarrior* temp = nullptr;
				this->location = destPtr;
				temp = destPtr->enterWarrior(this);
				if (temp == nullptr)
				{
					this->location = locdPtr;
					locdPtr->enterWarrior(this);
				}
				OnMoved();
				Log(" moved Success from " + locdPtr->name + " to " + destPtr->name + ".");
				return;
			}
	Log(" moved unSuccess,now in " + locdPtr->name);
	drawPut("move to " + locdPtr->name + " with health= " + std::to_string(health) + " ,power= " + std::to_string(power));
	ifMoved = true;

}

void baseWarrior::afterHartWar(baseWarrior* w)
{
	for (auto& i : arms)
	{
		if (i != nullptr)
		{
			if (i->getAttack() != 0)
			{
				Log(i->Action() ? ("using " + i->name) : ("a unAction " + i->name + "!"));
				i->OnUsing(w);
			}
			if (i->ifDestroy() || !i->Action())
			{
				Log(i->name + " destroy! ");
				auto x = i;
				i = nullptr;
				delete x;
			}
		}
	}
	if (!w->Action())
	{
		w->OnDead(this);
		this->OnKillEnemy(w);
		drawPut(name + " was killed in " + location->name);
	}
}
void baseWarrior::_attack(baseWarrior* w)
{
	drawPut(name + " attack to " + w->name + " with health= " + std::to_string(health) + " ,power= " + std::to_string(power));
	int at = getArmAttack();
	OnAttack(w);
	w->_getHart(at + power);
	afterHartWar(w);
}

void baseWarrior::_countattack(baseWarrior* w)
{
	drawPut(name + " fought back against " + w->name + " in " + location->name);
	if (!ifCounterattack) return;
	int at = getArmAttack();
	OnCounterAttack(w);
	w->_getHart(at + power / 2);
	afterHartWar(w);
}

bool baseWarrior::_addArms(baseArms* a)
{
	if (arms.empty())
		arms.resize(maxArmsNum, nullptr);

	for (auto& i : arms)
	{
		if (i == nullptr)
		{
			i = a;
			return true;
		}
	}
	return false;
}

void baseWarrior::_beShoot(baseMissile* m)//TODO->
{
	Log("be shoot by " + m->name + " from " + m->Holder->name);
	m->OnHart(this);
	OnBeShoot(m);
}

void baseWarrior::drawPut(std::string s)
{
	location->drawPut(s, name);
}

std::string baseWarrior::to_string()
{
	std::string output = name + ":{";
	output += "health=" + std::to_string(health);
	output += ",power=" + std::to_string(power);
	output += ",arms={";
	for (auto a : arms)
		output += (a == nullptr ? "null" : a->to_string()) + ",";

	output += "}}";
	return output;
}
