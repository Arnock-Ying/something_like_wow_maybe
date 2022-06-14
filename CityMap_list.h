#pragma once
#include "CityMap.h"

class CityMap_list :
	public CityMap
{
private:
	Headquarters* blueHeader, * redHeader;

	std::vector<long long> RGBList;
	std::vector<std::wstring> KeyList;

public:
	CityMap_list(int length = 5);
	~CityMap_list() = default;
	basePlace* foundNextPlaceFromTo(basePlace* nowPlace, Headquarters* destination);
	basePlace* foundNextPlaceFromTo(basePlace* nowPlace, int destination);

	//void foreachUpdata();
	//void foreachHourStart();
	//void foreachUpdataStart();
	//void foreachUpdataEnd();
	//void ResetMapState();
	//void foreachMove();

	int onlyOnceHeader();

	void PanelInit();
	void PanelUpdata();
};

