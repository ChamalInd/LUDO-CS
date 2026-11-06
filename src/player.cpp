#include "../includes/includes.h"

Color Player::getPlayerColor() const
{
	return playerColor;
}
		
std::string Player::getPlayerName() const
{
	return playerName;
}
		
std::vector<Piece> Player::getPlayerPieces() const
{
	return playerPieces;
}
