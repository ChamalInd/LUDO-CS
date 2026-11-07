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

int rollDie();
std::string convertColorToString(Color color, NameType type);

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
		Board();

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
		
		Color getPlayerColor() const;
		std::string getPlayerName() const;
		int getPieceCount() const;
		
		void calculatePlayerState();
		void decidePlayerTurn(int diceValue);
};

class Piece
{
	private:
		std::string pieceID;
		Player* owner = nullptr;
		int stepCount = 0;
		int pieceLocation = -1;
	
	public:
		Piece(std::string ID, Player* o) : pieceID(ID), owner(o) {}

		std::string getPieceID() const;
		int getStepCount() const;
		int getPieceLocation() const;

		void movePiece(int diceValue);
};

