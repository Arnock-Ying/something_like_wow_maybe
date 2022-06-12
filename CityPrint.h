#pragma once
#include"GUI.h"
#include<string>
#include<fstream>

#define KEYDOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)		//鼠标状态获取参数
#define  TextHigh (Gui_y - 770) / textHigh
#define  TextWidth 920 / textHigh

namespace api {
	extern POINT Mouse;		//鼠标

	constexpr auto textHigh = 50;
	constexpr auto textWidth = textHigh / 2;
	constexpr auto MouseMoveRange = 100;


	void CutText(wchar_t* CutText, wchar_t**& GoalText, int start, int end, int Number);

	class CityPrint
	{
	public:
		int CityModeNumber;
		Image* CityImage;

		int CityNumber;
		int* CityX, * CityY, * CityState;

		int TextOutStart, TextOutEnd;

		int* TextOffest, * LineNumber, * TextOffestMax;

		int Offest = 0, Speed, OffestMax;

		void SetSpeed(int speed)
		{
			Speed = speed;
		}
		void GetCityMode(std::string name)
		{
			std::fstream file;
			file.open(name);
			GetCityMode(file);
		}
		void GetCityMode(std::fstream& FILE)
		{
			FILE >> CityModeNumber;
			if (CityImage != 0)
			{
				delete[] CityImage;
			}
			CityImage = new Image[CityModeNumber];
			for (int midI = 0; midI < CityModeNumber; midI++)
			{
				CityImage[midI].GetImage(FILE);
			}
		}
		void NewCity(int number)
		{
			int midI;
			CityNumber = number;
			CityX = new int[number];
			CityY = new int[number];
			CityState = new int[number];
			TextOffest = new int[number];
			LineNumber = new int[number];
			TextOffestMax = new int[number];
			CityX[0] = 520;
			CityY[0] = Gui_y - 200 - (rand() % 10) * 50;
			CityState[0] = rand() % CityModeNumber;
			TextOffest[0] = 0;
			for (midI = 1; midI < number; midI++)
			{
				CityX[midI] = CityX[midI - 1] + 1000 + (rand() % 10) * 10;
				CityY[midI] = Gui_y - 200 - (rand() % 10) * 50;
				CityState[midI] = (CityState[midI - 1] + rand()) % CityModeNumber;
				TextOffest[midI] = 0;
			}
			OffestMax = CityX[midI - 1] + 520 - Gui_x;
		}
		void PrintCityStatePart1(long long* RGBs)
		{
			int midI, midJ, midK, midL;
			for (midI = 0; midI < CityNumber; midI++)
			{
				if (CityX[midI] + Offest >= -470)
				{
					break;
				}
			}
			midJ = midI;
			for (; midI < CityNumber; midI++)
			{
				if (CityX[midI] + Offest > Gui_x + 470)
				{
					break;
				}
				setlinecolor(RGBs[midI]);
				setlinestyle(PS_DASH, 8);
				roundrect(CityX[midI] + Offest - 470, 50, CityX[midI] + Offest + 470, Gui_y - 700, 30, 30);
				line(CityX[midI] + Offest + 75, Gui_y - 700, CityX[midI] + Offest + 75, CityY[midI] + 50);
			}
			TextOutStart = midJ;
			if (midI == CityNumber)
			{
				TextOutEnd = midI - 1;
			}
			else
			{
				TextOutEnd = midI;
			}
		}
		void Print()
		{
			setlinecolor(WHITE);
			setlinestyle(PS_SOLID, 10);
			int midI, midJ;
			for (midI = 0; midI < CityNumber; midI++)
			{
				if (CityX[midI] + Offest + CityImage[CityState[midI]].image.getwidth() >= 0)
				{
					break;
				}
			}
			if (midI != 0)
				line(CityX[midI - 1] + Offest + 75, CityY[midI - 1] + 50, CityX[midI] + Offest + 75, CityY[midI] + 50);
			for (midJ = midI + 1; midJ < CityNumber; midJ++)
			{
				if (CityX[midJ - 1] + Offest >= Gui_x)
				{
					break;
				}
				line(CityX[midJ - 1] + Offest + 75, CityY[midJ - 1] + 50, CityX[midJ] + Offest + 75, CityY[midJ] + 50);
			}
			for (; midI < CityNumber; midI++)
			{
				if (CityX[midI] + Offest >= Gui_x)
				{
					break;
				}
				CityImage[CityState[midI]].Put(CityX[midI] + Offest, CityY[midI]);
			}
		}

		void Move(POINT Mouse)
		{
			if (Mouse.x <= MouseMoveRange)
			{
				if (abs(Offest) < Speed)
				{
					Offest = 0;
				}
				else
					Offest += Speed;
			}
			if (Mouse.x >= Gui_x - MouseMoveRange)
			{
				if (-Offest > OffestMax - Speed)
				{
					Offest = -OffestMax;
				}
				else
					Offest -= Speed;
			}
		}

		void TextPrint(wchar_t** Text, POINT mouse)
		{
			int midI, midJ, midK, midL;
			int TextState;
			wchar_t*** LinePut;
			LinePut = new wchar_t** [CityNumber];
			for (midI = TextOutStart; midI <= TextOutEnd; midI++)
			{
				LinePut[midI] = new wchar_t* [1];
				for (midJ = 0, LineNumber[midI] = 0, TextState = 0, midL = 1; Text[midI][midJ] != 0; midJ++, midL++)
				{
					if (midL % (TextWidth + 1) == 0 || Text[midI][midJ] == (wchar_t)'\n')
					{
						CutText(Text[midI], LinePut[midI], midJ - midL + 1, midJ, LineNumber[midI]);
						midL = 1;
						LineNumber[midI]++;
					}
				}
				TextOffestMax[midI] = LineNumber[midI] * textHigh + (Gui_y - 770);
				if (TextOffestMax[midI] < 0)
				{
					TextOffestMax[midI] = 0;
				}
				if (TextOffest[midI] > TextOffestMax[midI])
				{
					TextOffest[midI] = TextOffestMax[midI];
				}
			}
			if (mouse.y >= 50 && mouse.y <= Gui_y - 720)
			{
				for (midI = TextOutStart; midI <= TextOutEnd; midI++)
				{
					if (mouse.x >= CityX[midI] + Offest - 460 && mouse.x <= CityX[midI] + Offest + 460)
					{
						if (mouse.y <= 150)
						{
							if (TextOffest[midI] <= Speed * 2)
							{
								TextOffest[midI] = 0;
							}
							else
							{
								TextOffest[midI] -= Speed * 2;
							}
						}
						else
							if (mouse.y >= Gui_y - 820)
							{
								if (TextOffest[midI] >= TextOffestMax[midI] - Speed * 2)
								{
									TextOffest[midI] = TextOffestMax[midI];
								}
								else
								{
									TextOffest[midI] += Speed * 2;
								}
							}
					}
				}
			}
			for (midI = TextOutStart; midI <= TextOutEnd; midI++)
			{
				for (midJ = TextOffest[midI] / textWidth, midK = 0; midJ < TextOffestMax[midI] / textWidth + TextHigh && midK < TextHigh && midK < LineNumber[midI]; midJ++, midK++)
				{
					outtextxy(CityX[midI] + Offest - 460, midK * textHigh + 70, LinePut[midI][midJ]);
				}
			}
			for (midI = TextOutStart; midI <= TextOutEnd; midI++)
			{
				for (midJ = 0; midJ < LineNumber[midI]; midJ++)
				{
					delete[] LinePut[midI][midJ];
				}
				delete[] LinePut[midI];
			}
			delete[] LinePut;
		}
	};

	void UIinitialize(int n);
	extern CityPrint CityManage;
}

#undef TextHigh
#undef TextWidth