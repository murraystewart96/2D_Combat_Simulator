#pragma once
#include <string>
#include "Level.h"

using namespace std;

class GameSystem
{
public:
	GameSystem();
	void initialise(string fileName);
	void update();
private:
	string _fileName;
	Level _level;
};

