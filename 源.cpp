#include <iostream>
#include "faction.h"
#include "GameManager.h"
#include "nomelWarrior.h"
#include "Sword.h"
#include "Arch.h"
#include "Warriors.h"

using namespace std;

GameManager gameManager;

int main()
{
	gameManager.setMaxLoop(100);
	gameManager.gameInit();
	Headquarters* blueHeader = gameManager.Header(0);
	Headquarters* redHeader = gameManager.Header(1);

	blueHeader->production_list = { new lion(), new dragon(), new ninja(), new iceman(), new wolf() };
	redHeader->production_list = { new iceman(), new lion(), new wolf(), new ninja(), new dragon() };
	blueHeader->armsProduction_list = { new Sword(),new Arch() };
	redHeader->armsProduction_list = { new Sword() ,new Arch() };
	gameManager.gameRun();
	gameManager.gameDeleted();

	return 0;
}