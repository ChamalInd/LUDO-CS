#include "../includes/includes.h"

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
