#include "CityMap_list.h"
#include "City_small.h"
#include "Headquarters.h"
#include "nomelWarrior.h"
#include "GameManager.h"
#include "Sword.h"
#include "Arch.h"

CityMap_list::CityMap_list(int lengh) :CityMap(lengh + 2)
{
	headquarters.resize(2);

	for (auto i : { 0,1 })
	{
		headquarters[i] = new Headquarters(i);
		placeList[i ? lengh + 1 : 0] = headquarters[i];
		headquarters[i]->nowEnemyID = i ? 0 : 1;
	}
	blueHeader = headquarters[0];
	redHeader = headquarters[1];

	blueHeader->production_list = { new nomelWarrior() };
	redHeader->production_list = { new nomelWarrior() };
	blueHeader->armsProduction_list = { new Sword(),new Arch() };
	redHeader->armsProduction_list = { new Sword() ,new Arch() };

	for (int i = 1; i <= lengh; ++i)
	{
		placeList[i] = new City_small();
	}
}



basePlace* CityMap_list::foundNextPlaceFromTo(basePlace* nowPlace, Headquarters* destination)
{
	if (nowPlace == destination)
		return nullptr;

	bool foundedfig = false;
	size_t i = 0;
	for (; i < placeList.size(); ++i)
	{
		if (placeList[i] == nowPlace)
		{
			foundedfig = true;
			break;
		}
	}

	if (!foundedfig)
		return nullptr;

	if (destination == redHeader)
		return placeList[i + 1];
	if (destination == blueHeader)
		return placeList[i - 1];

	return nullptr;
}

basePlace* CityMap_list::foundNextPlaceFromTo(basePlace* nowPlace, int destination)
{
	return foundNextPlaceFromTo(nowPlace, destination == 0 ? blueHeader : redHeader);
}

//void CityMap_list::foreachUpdata()
//{
//	for (auto& i : placeList)
//	{
//		i->Updata();
//	}
//}
//
//void CityMap_list::foreachHourStart()
//{
//	for (auto& i : placeList)
//	{
//		i->OnHourStart();
//	}
//}
//
//void CityMap_list::foreachUpdataStart()
//{
//	for (auto& i : placeList)
//	{
//		i->UpdataStart();
//	}
//}
//
//void CityMap_list::foreachUpdataEnd()
//{
//	for (auto& i : placeList)
//	{
//		i->UpdataEnd();
//	}
//}
//
//void CityMap_list::ResetMapState()
//{
//
//	if (redHeader->getEnterEntity() >= GameManager::headerMaxHealth)
//	{
//		redHeader->SetAction(false);
//		//redHeader = nullptr;
//	}
//
//	if (blueHeader->getEnterEntity() >= GameManager::headerMaxHealth)
//	{
//		blueHeader->SetAction(false);
//		//blueHeader = nullptr;
//	}
//
//}
//
//void CityMap_list::foreachMove()
//{
//	for (auto& i : placeList)
//	{
//		for (auto& w : i->Warriors())
//		{
//			if (w != nullptr)
//				w->_move();
//		}
//	}
//}
//
int CityMap_list::onlyOnceHeader()
{
	if (!redHeader->Action() || !blueHeader->Action())
	{
		if (redHeader->Action())
			return 1;
		else if (blueHeader->Action())
			return 0;
		else
			return -1;
	}
	else
		return -2;
}
