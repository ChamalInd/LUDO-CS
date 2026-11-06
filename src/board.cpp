#include "../includes/includes.h"


Board::Board()
{
	Color playerColors[] = {RED, GREEN, YELLOW, BLUE};
	int playersXMarkedCells[] = {39, 0, 13, 26};
	int playersHomePathCells[] = {37, 50, 11, 24};
	int playersHomeBeginCells[] = {70, 52, 58, 64};

	// getting ready the player order and the start screen of the game.
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
		std::string playerName = convertEnumToString(playerColors[index], FULL_NAME);
		std::string pieceChar = convertEnumToString(playerColors[index], FIRST_CHAR);
		std::cout << playerName;
		if (i < getNoOfPlayers() - 1) std::cout << ", ";
	
		// setting up the players.
		std::vector<Piece> pieces;
		for (int j = 0; j < getNoOfPieces(); j++)
		{
			std::string pieceName = pieceChar + std::to_string(j + 1);
			Piece piece(j, pieceName);
			pieces.push_back(piece);
		}

		Player player(playerColors[index], playerName, pieces, playersXMarkedCells[index], playersHomePathCells[index], playersHomeBeginCells[index]);
		insertIntoPlayersVector(player);
	}
	std::cout << "." << std::endl; 

	// setting up the board.
	for (int i = 0; i < getNoOfCells(); i++)
	{
		CellType type = NORMAL;
		if (i / 52) type = COLOR_SPECIFIC;
		Cell cell(i, type);
		insertIntoCellsVector(cell);
	}

	// setting the game over signal.
	setGameOverSignal(false);
}

void Board::startGame()
{
	std::cout << getGameOverSignal();
	while (!getGameOverSignal())
	{
		std::cout << "Started";
		// checking whether the game is over.
		setGameOverSignal(true);
		for (Player p : players)
		{
			std::vector<Piece> pieces = p.getPlayerPieces();
			for (Piece x : pieces)
			{
				if (x.getPieceState() != FINISHED)
				{
					setGameOverSignal(false);
					break;
				}
			}
			if (!getGameOverSignal()) break;
		}


	}
}

void Board::setGameOverSignal(bool signal)
{
	gameOverSignal = signal;
}

void Board::insertIntoPlayersVector(Player& player)
{
	players.push_back(player);
}

void Board::insertIntoCellsVector(Cell& cell)
{
	cells.push_back(cell);
}

int Board::getNoOfPlayers() const
{
	return noOfPlayers;
}

int Board::getNoOfPieces() const
{
	return noOfPieces;
}

int Board::getNoOfCells() const
{
	return noOfNormalCells + noOfColorSpecificCells;
}

bool Board::getGameOverSignal() const
{
	return gameOverSignal;
}
