#include "../includes/includes.h"

void Piece::movePieceToX(int x)
{
	currentPlace = x;
}

bool Piece::movePieceAroundBoard(std::string playerName, int dieValue, int homePathCell, int homeBeginCell)
{
	const int totalSteps = 56;

	if (countOfCellsMoved + dieValue > totalSteps) return false;

	std::cout << playerName << " player moves piece " << pieceName << " from location " << currentPlace + 1; 

	for (int i = 0; i < dieValue; i++)
	{
		if (currentPlace >= homeBeginCell) 
		{
			currentPlace += 1;
		}
		else if (countOfCellsMoved == 50 && currentPlace == homePathCell)
		{
			currentPlace = homeBeginCell;
		}
		else
		{
			currentPlace = (currentPlace + 1) % 52;
		}
		countOfCellsMoved += 1;
	}

	if (countOfCellsMoved == totalSteps)
	{
		pieceState = FINISHED;
	}

	std::cout << " to " << currentPlace + 1 << " by " << dieValue << " units in " << "clockwise" << " direction." << std::endl;

	if (pieceState == FINISHED)
	{
		std::cout << playerName << " player's piece " << pieceName << " reached Home." << std::endl;
	}

	return true;
}

void Piece::setPieceState(State newState)
{
	pieceState = newState;
}

int Piece::getPieceID() const
{
	return pieceID;
}
		
std::string Piece::getPieceName() const
{
	return pieceName;
}
		
int Piece::getCurrentPlace() const
{
	return currentPlace;
}
		
State Piece::getPieceState() const
{
	return pieceState;
}
