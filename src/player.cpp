#include "../includes/includes.h"

#define NO_OF_PIECES 4

Player::Player(Color c, std::string n, int x, int hp, int hb, State s)
{
	playerColor = c;
	playerName = n;
	xMarkedCell = x;
	homePathCell = hp;
	homeBeginCell = hb;
	playerState = s;

	for (int i = 0; i < NO_OF_PIECES; i++)
	{
		std::string name = convertColorToString(playerColor, FIRST_CHAR) + std::to_string(i + 1); 
		Piece piece(name, this);
		playerPieces.push_back(piece);
	}
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

