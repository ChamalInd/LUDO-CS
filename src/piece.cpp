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

	std::cout << playerName << " moves piece " << pieceName << " from location " << currentPlace + 1; 

	for (int i = 0; i < dieValue; i++)
	{
		if (currentPlace >= homeBeginCell)
		{
			currentPlace = (currentPlace + 1) % 52;
			countOfCellsMoved += 1;

			if (countOfCellsMoved == 50 && currentPlace == homePathCell) 
			{
				currentPlace = homeBeginCell;
			}
		}
		else
		{
			currentPlace += 1;
		}
	}

	if (currentPlace == homeBeginCell + 5)
	{
		pieceState = FINISHED;
	}

	std::cout << " to " << currentPlace + 1 << " by " << dieValue << " units in " << "clockwise" << " direction." << std::endl;

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
