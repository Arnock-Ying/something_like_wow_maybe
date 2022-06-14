#include"GUI.h"

namespace api {
	int Gui_x, Gui_y;
	float DPIx, DPIy;

	BackImageMan BackImageManage;

	char midCharAdd[512];
	std::string midStringAdd;

	bool inipretreatment()
	{						//»´∆¡œ‘ Ω
		Gui_x = GetSystemMetrics(SM_CXSCREEN);
		Gui_y = GetSystemMetrics(SM_CYSCREEN);
		/*
		HDC hdc = GetDC(NULL);
		Gui_x = GetDeviceCaps(hdc, DESKTOPHORZRES);
		Gui_y = GetDeviceCaps(hdc, DESKTOPVERTRES);
		ReleaseDC(NULL, hdc);
		*/

		initgraph(Gui_x, Gui_y, EW_SHOWCONSOLE);

		HWND hwnd = GetHWnd();
		SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, Gui_x, Gui_y, SWP_SHOWWINDOW);
		return true;
	}
}