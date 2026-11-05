#include "../includes/includes.h"


Board::Board()
{
	Color playerColors[] = {RED, GREEN, YELLOW, BLUE};
	
	std::cout << std::string(30, '=') << " LUDO-CS " << std::string(30, '=') << std::endl << std::endl;
	for (int i = 0; i < getNoOfPlayers(); i++)
	{
		std::string full_name = convertEnumToString(playerColors[i], FULL_NAME);
		std::string first_char = convertEnumToString(playerColors[i], FIRST_CHAR);

		std::cout << "The " << full_name << " player has four (04) pieces named ";
		std::cout << first_char << "1, " << first_char << "2, " << first_char << "3, " << first_char << "4." << std::endl; 
	}
	std::cout << std::endl;

	Color firstPlayer = pickFirstPlayer(getNoOfPlayers());

	std::cout << std::endl << convertEnumToString(playerColors[firstPlayer], FULL_NAME) << " player has the highest roll and will begin the game." << std::endl;
	std::cout << "The order of a single round is ";
	for (int i = 0; i < getNoOfPlayers(); i++)
	{
		int index = (firstPlayer + i) % getNoOfPlayers();
		std::cout << convertEnumToString(playerColors[index], FULL_NAME);
		if (i < getNoOfPlayers() - 1) std::cout << ", ";
	}
	std::cout << "." << std::endl; 
}


int Board::getNoOfPlayers() const
{
	return noOfPlayers;
}
