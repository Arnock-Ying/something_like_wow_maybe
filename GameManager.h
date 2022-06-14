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
	bool iffinish = false;
	int UpdataFixTime = 200;
	int CityNum = 5;
public:
	GameManager();
	~GameManager();

	inline void setMaxLoop(int n = -1) { maxLoopNum = n; }
	inline Headquarters* Header(int n) { return cityMap->Header(n); }

	void readNumFromScreen();
	void gameInit(int msg = 0);
	void gameRun();
	void gameDeleted();

};

enum GameManagerMessage
{
	GMM_DRAW = 0,
	GMM_NOTDRAW = 1
};
