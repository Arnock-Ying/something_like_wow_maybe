#include "CityMap.h"
#include "GameManager.h"

CityMap::CityMap(int n)
{
	placeList.resize(n);
}

CityMap::~CityMap()
{
	for (auto i : placeList)
	{
		if (i != nullptr)
			delete i;
	}
}

basePlace* CityMap::foundNextPlaceFromTo(basePlace* nowPlace, int destination)
{
	return foundNextPlaceFromTo(nowPlace, headquarters[destination]);
}

int CityMap::onlyOnceHeader()
{
	int winner = -1;
	for (auto i : headquarters)
	{
		if (i != nullptr)
			if (i->Action())
			{
				if (winner == -1)
					winner = i->getCamp();
				else
					return -2;
			}
	}
	return winner;
}

void CityMap::_panelInit()
{
	if (!GameManager::manager->ifdraw)return;
	onInit = true;
	PanelInit();
}

void CityMap::_panelIpdata()
{
	if (!GameManager::manager->ifdraw)return;
	if (!onInit)return;
	PanelUpdata();
}
