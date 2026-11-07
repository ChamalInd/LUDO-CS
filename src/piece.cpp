#include "../includes/includes.h"

std::string Piece::getPieceID() const
{
	return pieceID;
}
		
std::string Piece::getPieceName() const
{
	return pieceName;
}
		
int Piece::getStepCount() const
{
	return stepCount;
}
		
int Piece::getPieceLocation() const
{
	return pieceLocation;
}

void Piece::movePiece(int diceValue)
{
	// to be implemented
}

