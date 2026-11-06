#include "../includes/includes.h"

void Piece::movePlayerToX(int x)
{
	currentPlace = x;
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
