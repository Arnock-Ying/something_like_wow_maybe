#include <Windows.h>

#include "GameManager.h"
#include "CityMap_list.h"
#include "CityPrint.h"
#include "Arch.h"
#include "Warriors.h"

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

void GameManager::readNumFromScreen(std::istream& os)
{
	int M, N, R, K, T;
	int h[5], a[5];
	os >> M >> N >> R >> K >> T;
	for (int i = 0; i < 5; i++)os >> h[i];
	for (int i = 0; i < 5; i++)os >> a[i];

	Headquarters::BaseHealth = M;
	CityNum = N;
	Arch::basePower = R;
	lion::setK(K);
	setMaxLoop(T);


	dragon x1;
	ninja  x2;
	iceman x3;
	lion   x4;
	wolf   x5;

	x1.DefaultHealth() = h[0];
	x2.DefaultHealth() = h[1];
	x3.DefaultHealth() = h[2];
	x4.DefaultHealth() = h[3];
	x5.DefaultHealth() = h[4];

	x1.DefaultAttack() = a[0];
	x2.DefaultAttack() = a[1];
	x3.DefaultAttack() = a[2];
	x4.DefaultAttack() = a[3];
	x5.DefaultAttack() = a[4];
}

void GameManager::gameInit(int msg)
{
	if (cityMap != nullptr)
		delete cityMap;
	headerMaxHealth = 2;
	cityMap = new CityMap_list(CityNum);
	if (msg & GMM_NOTDRAW)ifdraw = false;
	else ifdraw = true;
	cityMap->_panelInit();
	iffinish = false;

}

void GameManager::gameRun()
{
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
					basePlace::foreachAttack();
				}
				if (worldTime == 40)
				{
					basePlace::foreachBackLive();
				}
				basePlace::foreachUpdata();
				baseWarrior::foreachUpdata();

				basePlace::foreachUpdataEnd();
				baseWarrior::foreachUpdataEnd();

				worldTime++;
				if (iffinish)break;
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
		if (KEYDOWN(VK_ESCAPE) || (!ifdraw && iffinish))
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

	basePlace::Delete();
	baseWarrior::Delete();

	iffinish = false;
	ifdraw = true;
	wow::worldTime.clear();
	maxLoopNum = -1;
}
