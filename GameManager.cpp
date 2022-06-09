#include "GameManager.h"
#include "CityMap_list.h"
using namespace wow;
GameManager* GameManager::manager = nullptr;
int GameManager::headerMaxHealth = -1;
GameManager::GameManager()
{
	if (manager == nullptr)
		manager = this;
	else
		throw "twoGameManagers!";
}

GameManager::~GameManager()
{
	manager = nullptr;
}

void GameManager::gameInit()
{
	if (cityMap != nullptr)
		delete cityMap;
	headerMaxHealth = 2;
	cityMap = new CityMap_list();
}

void GameManager::gameRun()
{
	int itr = 0;
	while (1)
	{
		debug.Log("runing");
		for (int i = 0; i < 60; i++)
		{
			if (worldTime == 0)
			{
				basePlace::foreachHourStart();
				baseWarrior::foreachHourStart();
			}
			basePlace::foreachUpdataStart();
			baseWarrior::foreachUpdataStart();
			if (worldTime == 10)
			{
				baseWarrior::foreachMove();
				basePlace::foreachGetifAttack();
			}
			if (worldTime == 30)
			{
				basePlace::foreachBackLive();
			}
			if (worldTime == 40)
			{
				basePlace::foreachAttack();
			}
			basePlace::foreachUpdata();
			baseWarrior::foreachUpdata();

			basePlace::foreachUpdataEnd();
			baseWarrior::foreachUpdataEnd();

			worldTime++;

		}
		basePlace::foreachHourEnd();
		baseWarrior::foreachHourEnd();
		if (cityMap->onlyOnceHeader() != -2)
			break;
		if (maxLoopNum >= 0 && itr > maxLoopNum)
			break;
		GameObject::Clear();
		itr++;
	}
}

void GameManager::gameDeleted()
{
	if (cityMap != nullptr)
	{
		delete cityMap;
		cityMap = nullptr;
	}

	maxLoopNum = -1;
}
