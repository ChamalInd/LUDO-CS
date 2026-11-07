#include "../includes/includes.h"

#define NO_OF_PLAYERS 4


GameManager::GameManager()
{
	Color playerColors[] = {RED, GREEN, YELLOW, BLUE};
	int playersXMarkedCells[] = {39, 0, 13, 26};
	int playersHomePathCells[] = {37, 50, 11, 24};
	int playersHomeBeginCells[] = {70, 52, 58, 64};

	// getting ready the player order and the start screen of the game.
	std::cout << std::string(30, '=') << " LUDO-CS " << std::string(30, '=') << std::endl << std::endl;
	for (int i = 0; i < NO_OF_PLAYERS; i++)
	{
		std::string full_name = convertColorToString(playerColors[i], FULL_NAME);
		std::string first_char = convertColorToString(playerColors[i], FIRST_CHAR);

		std::cout << "The " << full_name << " player has four (04) pieces named ";
		std::cout << first_char << "1, " << first_char << "2, " << first_char << "3, " << first_char << "4." << std::endl; 
	}
	std::cout << std::endl;

	Color firstPlayer = pickFirstPlayer(NO_OF_PLAYERS);

	std::cout << std::endl << convertColorToString(playerColors[firstPlayer], FULL_NAME) << " player has the highest roll and will begin the game." << std::endl;
	std::cout << "The order of a single round is ";
	
	// implementing the players
	for (int i = 0; i < NO_OF_PLAYERS; i++)
	{
		int index = (firstPlayer + i) % NO_OF_PLAYERS; 
		std::string playerName = convertColorToString(playerColors[index], FULL_NAME);
		std::string pieceChar = convertColorToString(playerColors[index], FIRST_CHAR);
		std::cout << playerName;
		if (i < NO_OF_PLAYERS - 1) std::cout << ", ";
	
		Player player(playerColors[i], playerName, playersXMarkedCells[i], playersHomePathCells[i], playersHomeBeginCells[i], PLAYING);
		players.push_back(player);
	}
	std::cout << "." << std::endl; 
}

void GameManager::gameLoop()
{

}

