#include "../includes/includes.h"

void Piece::movePieceToX(int x)
{
	currentPlace = x;
}

bool Piece::movePieceAroundBoard(std::string playerName, int dieValue, int homePathCell, int homeBeginCell, std::vector<Cell>& cells)
{
	const int totalSteps = 56;
	int prevPlace = currentPlace;

	if (countOfCellsMoved + dieValue > totalSteps) return false;

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

	if (countOfCellsMoved != totalSteps && cells[currentPlace].getCellOccupent() != nullptr)
	{
		// ignore going into cells occupied by the same player
		if (cells[currentPlace].getCellOccupent()->getPieceName()[0] == pieceName[0])
		{
			return false;
		}
		// capturing opponent pieces
		else
		{
			Piece* occupent = cells[currentPlace].getCellOccupent();
			occupent->setPieceState(IDLE);
			occupent->setCurrentPlace(-1);
			occupent->setCountOfCellsMoved(0);
		}
	}

	cells[currentPlace].setCellOccupent(this);

	std::cout << playerName << " player moves piece " << pieceName << " from location " << prevPlace + 1; 
	std::cout << " to " << currentPlace + 1 << " by " << dieValue << " units in " << "clockwise" << " direction." << std::endl;
	
	if (countOfCellsMoved == totalSteps)
	{
		pieceState = FINISHED;
		std::cout << playerName << " player's piece " << pieceName << " reached Home." << std::endl;
	}

	return true;
}

void Piece::setPieceState(State newState)
{
	pieceState = newState;
}

void Piece::setCurrentPlace(int newPlace)
{
	currentPlace = newPlace;
}
		
void Piece::setCountOfCellsMoved(int newCount)
{
	countOfCellsMoved = newCount;
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
