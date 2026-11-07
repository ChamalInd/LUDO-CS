#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>

enum Color
{
	RED, GREEN, YELLOW, BLUE
};

enum NameType
{
	FULL_NAME, FIRST_CHAR
};

enum State
{
	IDLE, PLAYING, FINISHED
}; 

class GameManager;
class Player;
class Piece;
class Board;
class Cell;


class GameManager
{
	private:
		std::vector<Player> players;
	
	public:
		GameManager();

		void initializeGame();
		void gameLoop();
};

class Board
{
	private:
		std::vector<Cell> cells;
	
	public:
		Board(std::vector<Cell>& c) : cells(c) {}

		bool checkCellValidity(int cellID);
};

class Cell
{
	private:
		int cellID;
		std::string occupentID = "NONE";

	public:
		Cell(int id) : cellID(id) {}

		void setCellOccupentID(std::string newOccupent);
		
		std::string getCellOccupentID() const;
};

class Player
{
	private:
		Color playerColor;
		std::string playerName;
		std::vector<Piece> playerPieces;
		State playerState = IDLE;

	protected:
		int xMarkedCell;
		int homePathCell;
		int homeBeginCell;
	
	public:
		Player(Color c, std::string n, int x, int hp, int hb, State s);
		
		void setPlayerPieces(std::vector<Piece>& newPieces);

		Color getPlayerColor() const;
		std::string getPlayerName() const;
		int getPieceCount() const;
		
		void calculatePlayerState();
		void decidePlayerTurn(int diceValue);
};

class Piece : public Player
{
	private:
		std::string pieceID;
		std::string pieceName;
		int stepCount = 0;
		int pieceLocation = -1;
	
	public:
		Piece(Player& owner, std::string ID, std::string n) : Player(owner), pieceID(ID), pieceName(n) {}

		std::string getPieceID() const;
		std::string getPieceName() const;
		int getStepCount() const;
		int getPieceLocation() const;

		void movePiece(int diceValue);
};

