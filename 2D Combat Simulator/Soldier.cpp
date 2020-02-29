#include "Soldier.h"
#include "Level.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
using namespace std;

Soldier::Soldier(int health, int attack, char symbol, int armyId, Level* level)
{
	_health = health;
	_attack = attack;
	_symbol = symbol;
	_x = 0;
	_y = 0;
	_armyId = armyId;
	_isAlive = true;
	_level = level;
}

void Soldier::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}


int Soldier::distanceToEnemy(int x1, int x2, int y1, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}


Soldier* Soldier::findClosetEnemy(const vector<Soldier*>& enemyArmy)
{

	

	//Calculate the initial distance to enemy
	int distance = INT_MAX;

	Soldier* closestEnemy = nullptr;
	int enemyX, enemyY;

	//Find the cloest Enemy
	for (auto& enemy : enemyArmy)
	{
		if (enemy)
		{
			enemy->getPosition(enemyX, enemyY);
			if (distanceToEnemy(_x, enemyX, _y, enemyY) < distance)
			{
				closestEnemy = enemy;
				distance = distanceToEnemy(_x, enemyX, _y, enemyY);
			}
		}
	}

	return closestEnemy;
}


void Soldier::move(const vector<Soldier*>& enemyArmy)
{
	Soldier* target = findClosetEnemy(enemyArmy);


	if (target)
	{
		int targetX = 0;
		int targetY = 0;
		target->getPosition(targetX, targetY);

		int distanceX, distanceY;

		distanceX = abs(_x - targetX);
		distanceY = abs(_y - targetY);

		int directionX = _x - targetX;
		int directionY = _y - targetY;

		if(directionX != 0)directionX = (directionX / abs(directionX)) * -1;
		if(directionY != 0)directionY = (directionY / abs(directionY)) * -1;

		if (distanceX > distanceY) 
		{
			//directionX = (directionX / abs(directionX)) * -1;
			if (!processMove(directionX, 0)) processMove(0, directionY);
		}
		else if (distanceY > distanceX)
		{
			//directionY = (directionY / abs(directionY)) * -1;
			if (!processMove(0, directionY)) processMove(directionX, 0);
		}
		else if(distanceX == distanceY)
		{
			int randNum = 1 + rand() % 2;

			if (randNum == 1)
			{
				//directionX = (directionX / abs(directionX)) * -1;
				if (!processMove(directionX, 0)) processMove(0, directionY);
			}
			else
			{
				//directionY = (directionY / abs(directionY)) * -1;
				if (!processMove(0, directionY)) processMove(directionX, 0);
			}
		}
	}

}


bool Soldier::processMove(int moveX, int moveY)
{
	int targetX = _x + moveX;
	int targetY = _y + moveY;

	
	char targetTile = _level->getTile(targetX, targetY);

	if (targetTile == '.')
	{
		_level->updateTile(targetX, targetY, _symbol);
		_level->updateTile(_x, _y, '.');
		setPosition(targetX, targetY);
		return true;
	}
	else if (targetTile == _symbol)
	{
		return false;
	}
}


void Soldier::attack(const vector<Soldier*>& enemyArmy)
{
	Soldier* target = findClosetEnemy(enemyArmy);

	if (target)
	{
		int randAttack = 1 + rand() % _attack;

		if (nextToEnemy(target))
		{
			target->takeDamage(randAttack);
		}
	}
}

bool Soldier::nextToEnemy(Soldier* enemy)
{
	int enemyX, enemyY;
	enemy->getPosition(enemyX, enemyY);

	if (distanceToEnemy(_x, enemyX, _y, enemyY) == 2)
	{
		return true;
	}

	return false;
}

void Soldier::takeDamage(int amount)
{
	_health -= amount;

	if (_health <= 0)
	{
		_isAlive = false;
		_level->updateTile(_x, _y, '.');
	}
}


void Soldier::getPosition(int& x, int& y)
{
	x = _x;
	y = _y;
}