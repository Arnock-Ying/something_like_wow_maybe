#include"CityPrint.h"

#define  TextHigh (Gui_y - 770) / textHigh
#define  TextWidth 920 / textHigh

namespace api {
	POINT Mouse;

	void CutText(wchar_t* CutText, wchar_t**& GoalText, int start, int end, int Number)
	{
		int midI, midJ;
		wchar_t** midText = new wchar_t* [Number + 1];
		memcpy(midText, GoalText, Number * sizeof(wchar_t*));
		midText[Number] = new wchar_t[end - start + 1];
		memcpy(midText[Number], CutText + start, (end - start) * sizeof(wchar_t));
		midText[Number][end - start] = 0;
		delete[] GoalText;
		GoalText = midText;
	}

	CityPrint CityManage;

	void UIinitialize(int n)
	{
		srand(time(NULL));
		inipretreatment();
		std::string CityModeAddress = "City\\City.txt";
		std::string BackAddress = "Back\\Back.txt";
		CityManage.GetCityMode(CityModeAddress);
		CityManage.NewCity(n);
		CityManage.SetSpeed(n);
		BackImageManage.SetImage(BackAddress);
		BackImageManage.SetState();
		settextcolor(WHITE);
		settextstyle(textHigh, textWidth, L"ºÚÌå");
	}
}