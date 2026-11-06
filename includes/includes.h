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

enum CellType
{	
	NORMAL, COLOR_SPECIFIC
};

enum NameType
{
	FULL_NAME, FIRST_CHAR
};

enum State
{
	IDLE, PLAYING, FINISHED
}; 

class Piece;
class Player;
class Cell;
class Board;

class Piece { 
	private: 
		int pieceID; 
		std::string pieceName; 
		int currentPlace = -1;
		int countOfCellsMoved = 0;
		State pieceState = IDLE;
	
	public:
		Piece(int i, std::string& n) : pieceID(i), pieceName(n) {}
		
		void movePieceToX(int x);
		bool movePieceAroundBoard(std::string playerName, int dieValue, int homePathCell, int homeBeginCell, std::vector<Cell>& cells);

		void setPieceState(State newState);
		void setCurrentPlace(int newPlace);
		void setCountOfCellsMoved(int newCount);

		int getPieceID() const;
		std::string getPieceName() const;
		int getCurrentPlace() const;
		State getPieceState() const;
};

class Cell
{
	private:
		int cellID;
		CellType cellType;
		Piece* cellOccupent = nullptr;
	
	public:
		Cell(int i, CellType& c) : cellID(i), cellType(c) {}

		void setCellOccupent(Piece* piece);

		int getCellID() const;
		CellType getCellType() const;
		Piece* getCellOccupent() const;
};

class Player
{
	private:
		Color playerColor;
		std::string playerName;
		std::vector<Piece> playerPieces;
		int xMarkedCell;
		int homePathCell;
		int homeBeginCell;
		State playerState = PLAYING;
		int noOfPieces = 4;
		int noOfIdlePieces = 4;

	public:
		Player(Color c, std::string& n, std::vector<Piece>& p, int x, int hp, int hb) : 
			playerColor(c), playerName(n), playerPieces(p), 
			xMarkedCell(x), homePathCell(hp), homeBeginCell(hb) {}

		bool playTurn(int dieValue, std::vector<Cell>& cells);

		Color getPlayerColor() const;
		std::string getPlayerName() const;
		std::vector<Piece> getPlayerPieces() const;
		State getPlayerState() const;
};

class Board
{
	private:
		std::vector<Cell> cells;
		std::vector<Player> players;
		bool gameOverSignal = true;
		int noOfPlayers = 4;
		int noOfPieces = 4; // per player
		int noOfNormalCells = 52;
		int noOfColorSpecificCells = 20;

	public:
		Board();

		void startGame();
		
		void insertIntoPlayersVector(Player& player);
		void insertIntoCellsVector(Cell& cell);
		
		void setGameOverSignal(bool signal);

		int getNoOfPlayers() const;
		int getNoOfPieces() const;
		int getNoOfCells() const;
		bool getGameOverSignal() const;
};


int rollDie();
std::string convertEnumToString(Color color, NameType type);
Color pickFirstPlayer(int noOfPlayers);
