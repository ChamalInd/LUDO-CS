#include "../includes/includes.h"

#define NO_OF_PLAYERS 4

GameManager::GameManager()
{
	Color playerColors[] = {RED, GREEN, YELLOW, BLUE};
	int playersXMarkedCells[] = {39, 0, 13, 26};
	int playersHomePathCells[] = {37, 50, 11, 24};
	int playersHomeBeginCells[] = {70, 52, 58, 64};
	
	// creating the board
	Board gameBoard;

	// implementing the players
	for (int i = 0; i < NO_OF_PLAYERS; i++)
	{
		std::string name = convertColorToString(playerColors[i], FULL_NAME);
		Player player(playerColors[i], name, playersXMarkedCells[i], playersHomePathCells[i], playersHomeBeginCells[i], PLAYING);
		players.push_back(player);
	}
}

void GameManager::initializeGame()
{

}

void GameManager::gameLoop()
{

}

