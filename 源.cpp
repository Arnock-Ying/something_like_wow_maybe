
#include <iostream>
#include "faction.h"
#include "GameManager.h"
#include "nomelWarrior.h"
#include "Sword.h"
#include "Arch.h"

using namespace std;

GameManager gameManager;

int main()
{
	gameManager.setMaxLoop(10);
	gameManager.gameInit();
	Headquarters* blueHeader = gameManager.Header(0);
	Headquarters* redHeader = gameManager.Header(1);

	blueHeader->production_list = { new nomelWarrior() };
	redHeader->production_list = { new nomelWarrior() };
	blueHeader->armsProduction_list = { new Sword(),new Arch() };
	redHeader->armsProduction_list = { new Sword() ,new Arch() };
	gameManager.gameRun();
	gameManager.gameDeleted();

	return 0;
}