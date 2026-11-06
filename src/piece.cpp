#include "../includes/includes.h"

void Piece::movePieceToX(int x)
{
	currentPlace = x;
}

bool Piece::movePieceAroundBoard(std::string playerName, int dieValue, int homePathCell, int homeBeginCell)
{
	if (currentPlace >= homeBeginCell)
	{
		if (dieValue > ((homeBeginCell + 5) - currentPlace)) return false;
	}

	std::cout << playerName << " moves piece " << pieceName << " from location ";
	std::cout << currentPlace + 1 << " to " << currentPlace + dieValue + 1;
	std::cout << " by " << dieValue << " units in " << "clockwise" << " direction." << std::endl;

	for (int i = 0; i < dieValue; i++)
	{
		currentPlace = (currentPlace + 1) % 52;
		countOfCellsMoved += 1;

		if (countOfCellsMoved == 49 && currentPlace == homePathCell)
		{
			currentPlace = homeBeginCell;
		}
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
