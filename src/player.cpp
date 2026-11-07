#include "../includes/includes.h"

Player::Player(Color c, std::string n, int x, int hp, int hb, State s)
{
	playerColor = c;
	playerName = n;
	xMarkedCell = x;
	homePathCell = hp;
	homeBeginCell = hb;
	playerState = s;
}
		
void Player::setPlayerPieces(std::vector<Piece>& newPieces)
{
	playerPieces = newPieces;
}

Color Player::getPlayerColor() const
{
	return playerColor;
}
		
std::string Player::getPlayerName() const
{
	return playerName;
}
		
int Player::getPieceCount() const
{
	return (int) playerPieces.size();
}

void Player::calculatePlayerState()
{
	playerState = FINISHED;
	for (Piece p : playerPieces)
	{
		if (p.getStepCount() < 56)
		{
			playerState = PLAYING;
			break;
		}
	}
}
		
void Player::decidePlayerTurn(int diceValue)
{
	// to be implemented
}

