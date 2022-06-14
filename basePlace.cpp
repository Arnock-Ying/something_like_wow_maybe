#include "basePlace.h"
#include "CityMap.h"
#include "GameManager.h"
#include <corecrt_wstring.h>

std::list<basePlace*> basePlace::Places;

void basePlace::foreachUpdata()
{
	for (auto i : Places)
	{
		i->Updata();
	}
}

void basePlace::foreachAttack()
{
	for (auto i : Places)
	{
		i->_attack();
		if (i->ifAttack)
			i->BackLiveToHeader();
	}
}

void basePlace::foreachClear()
{
	for (auto i : Places)
	{
		i->_clear();
	}
}

void basePlace::Delete()
{
	//for (auto i : Places)
	//	delete i;
	Places.clear();
}

void basePlace::foreachHourStart()
{
	for (auto i : Places)
	{
		i->OnHourStart();
	}
}

void basePlace::ResetMapState()
{
	for (auto i : Places)
	{
		//i->OnHourEnd();
	}
}

void basePlace::foreachUpdataEnd()
{
	for (auto i : Places)
	{
		i->UpdataEnd();
	}
}

void basePlace::foreachHourEnd()
{
	for (auto i : Places)
	{
		i->OnHourEnd();
	}
}

void basePlace::foreachGetifAttack()
{
	for (auto i : Places)
	{
		i->ifAttack = i->getOccupier() == -1;
	}
}

void basePlace::foreachBackLive()
{
	for (auto i : Places)
	{
		i->BackLiveToHeader();
	}
}

void basePlace::foreachUpdataStart()
{
	for (auto i : Places)
	{
		i->UpdataStart();
	}
}

static int placeIDNum_temp = 0;
basePlace::basePlace()
{
	id = placeIDNum_temp;
	placeIDNum_temp++;
	name = "City " + std::to_string(id);
	Places.push_back(this);
}

basePlace::~basePlace()
{
	for (auto i : warriors)
	{
		if (i != nullptr)
		{
			i->SetAction(false);
		}
	}
	for (auto i = Places.begin(); i != Places.end(); i++)
	{
		if (*i == this)
		{
			Places.erase(i);
			break;
		}
	}
}

void basePlace::BackLiveToHeader()
{
	if (this->getOccupier() != -1)
	{
		auto header = GameManager::manager->cityMap->Header(this->getOccupier());
		header->addLive(life);

		Log(header->name + " get this live!");
		for (auto i : Warriors())
			if (i != nullptr)if (i->Action())
				if (i->getCamp() == this->getOccupier())
				{
					i->drawPut(i->name + " earned " + std::to_string(life) + " for his headquarter.");
					break;
				}
		life = 0;
	}
}

void basePlace::_attack()
{
	//¸üÐÂAction×´Ì¬
	for (auto i : warriors)
	{
		if (i != nullptr)
			if (i->Action())
			{
				if (i->getHealth() <= 0)
					i->SetAction(false);
			}
	}
	std::vector<baseWarrior*> copy_warriors(warriors.size(), nullptr);
	auto itr_after = warriors.begin();
	for (auto i : warriors)
	{
		if (i == nullptr)
			continue;
		if (i->Action())
			if (((campfig == -1 && (i->getCamp() % 2) == (id % 2)) || (campfig != -1 && campfig == i->getCamp())))
			{
				//Log(i->name + " camp:" + std::to_string(i->getCamp()) + ";" + name + " id:" + std::to_string(id) + ", camp:" + std::to_string(campfig));
				auto figCircle = itr_after;
				while (1)
				{
					itr_after++;
					if (itr_after == warriors.end())
						itr_after = warriors.begin();
					//if ((*warriors.begin()) != nullptr)
						//Log((*warriors.begin())->name);

					if (*itr_after != nullptr)
						if ((*itr_after)->Action())
							if ((*itr_after)->getCamp() != i->getCamp())
							{
								i->Log("fight with" + (*itr_after)->name);
								i->_attack(*itr_after);
								if ((*itr_after)->Action())
									(*itr_after)->_countattack(i);
								break;
							}

					if (itr_after == figCircle)
					{
						break;
					}

				}

			}
	}

	if (this->ifAttack)
	{
		Log("Attack finish!");
		OnAttack();
		bool haveWar = false;
		for (auto i : warriors)
		{
			if (i != nullptr)
				if (i->Action())
				{
					haveWar = true;
					i->OnAfterAttack();
				}
		}
		if (haveWar)
			if (this->getOccupier() >= 0)
			{
				int winCamp = this->getOccupier();
				if (lastWinnerCamp == winCamp)
				{
					campfig = winCamp;
					Log("flig to" + std::to_string(winCamp));
					drawPut(std::string(winCamp == 1 ? "red" : "blue") + " flag raised in " + name);
				}
				for (auto i : warriors)
				{
					if (i != nullptr)
						if (i->Action())
							if (i->getCamp() == winCamp)
							{
								i->OnWinAttack();
								i->ifWillGetReward = true;
							}
				}
				lastWinnerCamp = winCamp;
			}


		for (auto i : warriors)
		{
			if (i != nullptr)
				if (i->Action())
				{
					i->OnAfterAttack();
				}
		}
	}
}

//void basePlace::_getMissile(baseMissile* miss)
//{
	//missList.push_back(miss);
//}

int basePlace::getOccupier()const
{
	bool ifOnly = true;
	int onlyID = -1;

	for (auto i : warriors)
	{
		if (i != nullptr)
			if (i->Action())
			{
				if (onlyID != -1 && onlyID != i->getCamp())
					ifOnly = false;
				if (onlyID == -1)
					onlyID = i->getCamp();
			}
	}
	if (ifOnly)
		return onlyID;
	return -1;
}

void basePlace::_clear()
{
	for (auto& i : warriors)
	{
		if (i != nullptr)
			if (!i->Action())
				i = nullptr;
	}
	Clear();
}

void basePlace::drawPut(std::string s, std::string n)
{
	if (n == "\114")n = name;
	wow::output << (GameManager::manager->ifdraw ? name + " drawPut-" : "") << s << std::endl;

	if (!GameManager::manager->ifdraw)return;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	drawText.fill(L'0');
	drawText.width(3);
	drawText << wow::worldTime.getHour();
	drawText << L":";
	drawText.width(2);
	drawText << wow::worldTime.getMin() << L' ' << converter.from_bytes(n) << L": " << converter.from_bytes(s) << std::endl;
}
