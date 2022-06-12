#include <Windows.h>

#include "GameManager.h"
#include "CityMap_list.h"
#include "CityPrint.h"

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
	cityMap->_panelInit();
}

void GameManager::gameRun()
{
	bool iffinish = false;
	int itr = 0;
	long long time = 0;
	while (1)
	{
		if (!iffinish && (!ifdraw || GetTickCount64() - time > UpdataFixTime))
		{
			time = GetTickCount64();
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
				iffinish = true;
			if (maxLoopNum >= 0 && itr > maxLoopNum)
				iffinish = true;
			GameObject::Clear();
			itr++;
			debug.Log("\n");
		}
		if (ifdraw)
			cityMap->_panelIpdata();
		if (KEYDOWN(VK_ESCAPE))
			break;
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
