#include "Level.h"
#include <iostream>
#include <random>
#include <conio.h>


Level::Level()
{

}


void Level::loadLevel(string fileName)
{
	
	_inFile.open(fileName);
	if (_inFile.fail())
	{
		perror(fileName.c_str());
	}

	string lineData;

	while (getline(_inFile, lineData))
	{
		_levelData.push_back(lineData);
	}

	loadArmies();
}


void Level::loadArmies()
{
	for (int i = 0; i < _levelData.size(); i++)
	{
		for (int j = 0; j < _levelData[i].length(); j++)
		{
			if (getTile(j, i) == '?')
			{
				_army[0].push_back(new Soldier(100, 25, '?', 0, this));
				_army[0].back()->setPosition(j, i);
			}
			else if (getTile(j, i) == '@')
			{
				_army[1].push_back(new Soldier(100, 25, '@', 1, this));
				_army[1].back()->setPosition(j, i);
			}
		}
	}

	random_device::result_type seed = random_device()();
	mt19937 randomEngine(seed);

	
	Soldier* temp;        //temp to hold el being swapped

	//shuffle armies
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		for (int j = _army[i].size()-1; j >= 0; j--)
		{
			uniform_int_distribution<int> randomSwap(0, _army[i].size() - 1);
			int swap = randomSwap(randomEngine);

			temp = _army[i][swap];			
			_army[i][swap] = _army[i][j];   //swap random el with current el
			_army[i][j] = temp;             //replace current el with swap el
		}
	}
}

void Level::printLevel()
{
	string s(100, '\n');

	cout << s;

	for (auto& str : _levelData)
	{
		cout << str << endl;
	}
}


void Level::closeLevel()
{
	_inFile.close();
	_levelData.clear();

	for (int i = 0; i < NUM_ARMIES; i++)
	{
		for (int j = 0; j < _army[i].size(); j++)
		{
			if (!_army[i].empty())
			{
				delete _army[i][j];
			}
		}
	}
	_army[0].clear();
	_army[1].clear();
}


void Level::moveArmies()
{
	int i = 0;

	bool loop = true;

	while (loop)
	{
		loop = false;
		for (int j = 0; j < NUM_ARMIES; j++)
		{
			if (i < _army[j].size())
			{
				if (_army[j][i])
				{
					_army[j][i]->move(_army[abs(_army[j][i]->getId() - 1)]);
				}
				loop = true;
			}
		}
		i++;
	}

}

void Level::battleArmies()
{
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		for (auto& soldier : _army[i])
		{
			if (soldier)
			{
				soldier->attack(_army[abs(soldier->getId() - 1)]);
			}
		}
	}
}


void Level::update()
{
	

	while (!_army[0].empty() && !_army[1].empty())
	{
	
		_getch();

		moveArmies();
		battleArmies();
		printLevel();
		removeDead();
	}

	if (_army[0].empty())
	{
		cout << "\n\n***Army 2 is the winner!!***\n\n";
	}
	else if(_army[1].empty())
	{
		cout << "\n\n***Army 1 is the winner!!***\n\n";
	}
}


char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::updateTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}


void Level::removeDead()
{
	
	for (auto& army : _army)
	{
		for (auto& soldier : army)
		{

			if (soldier)
			{
				if (!soldier->isAlive())
				{
					delete soldier;
					soldier = nullptr;
				}
			}
		}
		auto itr = remove(army.begin(), army.end(), nullptr);
		army.erase(itr, army.end());
	}
}


int Level::soldierCount(vector<Soldier*> army)
{
	int soldierCount = 0;

	for (auto& soldier : army)
	{
		if (soldier != nullptr)
		{
			soldierCount += 1;
		}
	}

	return soldierCount;
}