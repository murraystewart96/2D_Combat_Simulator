#pragma once
#include <vector>
#include <string>

using namespace std;

class Level;


class Soldier
{
public:
	Soldier(int health, int attack, char symbol, int armyID, Level* level);
	Soldier* findClosetEnemy(const vector<Soldier*> &enemyArmy);
	int distanceToEnemy(int x1, int x2, int y1, int y2);
	void move(const vector<Soldier*>& enemyArmy);
	bool processMove(int moveX, int moveY);
	void takeDamage(int amount);
	void attack(const vector<Soldier*>& enemyArmy);
	bool nextToEnemy(Soldier* enemy);


	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int& x, int& y);
	int getId() { return _armyId; }
	bool isAlive() { return _isAlive; }

private:
	int _health;
	int _attack;
	char _symbol;
	int _x;
	int _y;
	int _armyId;
	bool _isAlive;
	Level* _level;
};

