#pragma once
#include "faction.h"
#include "CityMap.h"
#include "Headquarters.h"

class GameManager
{
private:
	int maxLoopNum = -1;
	
public:
	static int headerMaxHealth;
	CityMap* cityMap = nullptr;
	static GameManager* manager;
	
	bool ifdraw = true;
	int UpdataFixTime = 200;
public:
	GameManager();
	~GameManager();

	inline void setMaxLoop(int n = -1) { maxLoopNum = n; }
	inline Headquarters* Header(int n) { return cityMap->Header(n); }

	void readNumFromScreen();
	void gameInit();
	void gameRun();
	void gameDeleted();

};
