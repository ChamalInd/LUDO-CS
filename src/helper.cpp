#include "../includes/includes.h"

int rollDie()
{
	return rand() % 6 + 1;
}

std::string convertColorToString(Color color, NameType type)
{
	std::string name;

	switch (color)
	{
		case RED:
			if (type == FULL_NAME) name = "Red";
			else name = "R";
			break;
		case YELLOW:
			if (type == FULL_NAME) name = "Yellow";
			else name = "Y";
			break;
		case GREEN:
			if (type == FULL_NAME) name = "Green";
			else name = "G";
			break;
		case BLUE:
			if (type == FULL_NAME) name = "Blue";
			else name = "B";
			break;
	}

	return name;
}

Color pickFirstPlayer(int noOfPlayers)
{
	std::vector<int> playerDieRolls = {0, 0, 0, 0};
	Color players[] = {RED, GREEN, YELLOW, BLUE};
	bool isValid = false;

	while (!isValid)
	{
		for (int i = 0; i < noOfPlayers; i++)
		{
			playerDieRolls[i] = rollDie();
		}

		isValid = true;
		for (int i = 0; i < noOfPlayers; i++)
		{
			for (int j = i + 1; j < noOfPlayers; j++)
			{
				if (playerDieRolls[i] == playerDieRolls[j])
				{
					isValid = false;
					break;
				}
			}
		}
	}
	
	for (int i = 0; i < noOfPlayers; i++)
	{
		std::cout << convertColorToString(players[i], FULL_NAME) << " player rolls " << playerDieRolls[i]  << "."<< std::endl;
	}
	
	int maxDieRoll = 0;
	int firstPlayer = 0;

	for (int i = 0; i < noOfPlayers; i++)
	{
		if (playerDieRolls[i] > maxDieRoll)
		{
			maxDieRoll = playerDieRolls[i];
			firstPlayer = i;
		}
	}

	return players[firstPlayer];

}
