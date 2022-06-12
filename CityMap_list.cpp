#include "CityMap_list.h"
#include "City_small.h"
#include "Headquarters.h"
#include "nomelWarrior.h"
#include "GameManager.h"
#include "Sword.h"
#include "Arch.h"
#include "CityPrint.h"

CityMap_list::CityMap_list(int lengh) :CityMap(lengh + 2)
{
	headquarters.resize(2);
	KeyList.resize(lengh + 2);
	RGBList.resize(lengh + 2, WHITE);


	for (auto i : { 0,1 })
	{
		headquarters[i] = new Headquarters(i);
		placeList[i ? lengh + 1 : 0] = headquarters[i];
		headquarters[i]->nowEnemyID = i ? 0 : 1;
	}
	blueHeader = headquarters[0];
	redHeader = headquarters[1];

	for (int i = 1; i <= lengh; ++i)
	{
		placeList[i] = new City_small();
		placeList[i]->drawText.str(KeyList[i]);
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

void CityMap_list::PanelInit()
{
	api::UIinitialize(placeList.size());
}

void CityMap_list::PanelUpdata()
{
	long long colors[] = { WHITE,RED,BLUE };
	BeginBatchDraw();

	api::BackImageManage.PutImage();

	wchar_t** keyText = new wchar_t* [placeList.size()];
	for (int i = 0; i < placeList.size(); ++i)
	{
		keyText[i] = new wchar_t[KeyList[i].size() + 1];
		for (int j = 0; j < KeyList[i].size(); ++j)
			keyText[i][j] = KeyList[i][j];
		keyText[i][KeyList[i].size()] = L'\0';

		RGBList[i] = colors[placeList[i]->getCamp() + 1];
	}
	GetCursorPos(&api::Mouse);
	api::CityManage.Move(api::Mouse);
	api::CityManage.PrintCityStatePart1(RGBList.data());
	api::CityManage.TextPrint(keyText, api::Mouse);

	api::CityManage.Print();
	EndBatchDraw();
	for (int i = 0; i < placeList.size(); ++i)delete[] keyText[i];
	delete[] keyText;
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
