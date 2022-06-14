#include <iostream>
#include <fstream>
#include "faction.h"
#include "GameManager.h"
#include "nomelWarrior.h"
#include "Sword.h"
#include "Arch.h"
#include "Warriors.h"
#include "boom.h"

using namespace std;

GameManager gameManager;

int main()
{
	fstream fin("data.ini");
	int N;
	fin >> N;
	for (int itr = 0; itr < N; itr++)
	{
		cout << "Case " << itr + 1 << ':' << endl;
		gameManager.readNumFromScreen(fin);
		gameManager.setMaxLoop(100);
		gameManager.gameInit(GMM_NOTDRAW);
		Headquarters* blueHeader = gameManager.Header(0);
		Headquarters* redHeader = gameManager.Header(1);

		blueHeader->production_list = { new lion(), new dragon(), new ninja(), new iceman(), new wolf() };
		redHeader->production_list = { new iceman(), new lion(), new wolf(), new ninja(), new dragon() };
		blueHeader->armsProduction_list = { new Sword(),new Arch(),new Boom() };
		redHeader->armsProduction_list = { new Sword() ,new Arch(),new Boom() };
		gameManager.gameRun();
		gameManager.gameDeleted();
	}
	return 0;
}