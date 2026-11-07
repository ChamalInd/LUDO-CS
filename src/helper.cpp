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
