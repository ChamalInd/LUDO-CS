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
	std::cout << std::endl << playerName << " player rolled a " << dieValue << "." << std::endl;

	// sorting the pieces vector based on their state,
	// so idle pieces get priority to move from the base before other player play.
	std::sort(playerPieces.begin(), playerPieces.end(), [](const Piece& a, const Piece& b)
	{
		return a.getPieceState() < b.getPieceState();
	});

	for (Piece& piece : playerPieces)	
	{
		State state = piece.getPieceState();
		if (state == FINISHED) continue;

		if (state == IDLE)
		{
			if (dieValue == 6)
			{
				piece.setPieceState(PLAYING);
				piece.movePieceToX(xMarkedCell);
				noOfIdlePieces -= 1;

				std::cout << playerName << " player moves piece " << piece.getPieceName() << " to the starting point." << std::endl;
				std::cout << playerName << " player now has " << noOfPieces - noOfIdlePieces << "/4 of pieces on the board and " << noOfIdlePieces << "/4 of pieces on the base." << std::endl;
				break;
			}
		}
		
		if (state == PLAYING)
		{
			piece.movePieceAroundBoard(dieValue, homePathCell, homeBeginCell);
			break;
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
