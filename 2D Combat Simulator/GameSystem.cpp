#include "GameSystem.h"
#include <iostream>

GameSystem::GameSystem()
{

}

void GameSystem::initialise(string fileName)
{
	_fileName = fileName;
	_level.loadLevel(fileName);
	_level.printLevel();
}

void GameSystem::update()
{
	bool isDone = false;

	while (!isDone)
	{

		_level.update();

		cout << "Would you like to play again? (Y/N): ";
		char input;
		cin >> input;
		input = toupper(input);

		cout << "\n" << input << endl;

		while (input != 'Y' && input != 'N')
		{
			cin.clear();
			cin.ignore();
			cout << "Enter (Y/N): ";
			cin >> input;
			input = toupper(input);
		}

		if (input == 'Y')
		{
			_level.closeLevel();
			_level.loadLevel(_fileName);
			_level.printLevel();
		}
		else
		{
			isDone = true;
		}
	}
}