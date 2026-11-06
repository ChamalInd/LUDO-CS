#include "../includes/includes.h"

void Player::playTurn()
{	
	playerState = FINISHED;
	for (Piece piece : playerPieces)
	{
		if (piece.getPieceState() != FINISHED)
			{
				playerState = PLAYING;
				break;
			}
	}

	if (playerState == FINISHED) return;

	int dieValue = rollDie();
	std::cout << playerName << " player rolled a " << dieValue << "." << std::endl;

	for (Piece& piece : playerPieces)	
	{
		State state = piece.getPieceState();
		std::cout << state << " ";
		if (state == FINISHED) continue;

		if (state == IDLE)
		{
			if (dieValue == 6)
			{
				piece.setPieceState(PLAYING);
				piece.movePlayerToX(xMarkedCell);

				std::cout << playerName << " player moves piece " << piece.getPieceName() << " to the starting point." << std::endl;
				break;
			}
		}
		
		if (state == PLAYING)
		{
			continue;
		}
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
		
std::vector<Piece> Player::getPlayerPieces() const
{
	return playerPieces;
}

State Player::getPlayerState() const
{
	return playerState;
}
