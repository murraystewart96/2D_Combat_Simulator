#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Soldier.h"

using namespace std;

const int NUM_ARMIES = 2;

class Level
{
public:
	Level();
	void loadLevel(string fileName);
	void printLevel();
	void closeLevel();
	void loadArmies();
	void moveArmies();
	void battleArmies();
	void update();
	void updateTile(int x, int y, char tile);
	void removeDead();
	int soldierCount(vector<Soldier*> army);


	//Getters
	char getTile(int x, int y);
	vector<string>& getLevelData() { return _levelData; }
private:
	ifstream _inFile;
	vector<string> _levelData;
	vector<Soldier*> _army[NUM_ARMIES];
	vector <vector<Soldier*>> _soldierGrid;
};

