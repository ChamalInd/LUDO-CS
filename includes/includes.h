#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

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

class Piece
{
	private:
		int pieceID;
		std::string pieceName;
		int currentPlace = -1;
		bool isRoundComplete = false;
	
	public:
		Piece(int& i, std::string& n) : pieceID(i), pieceName(n) {}

		int getPieceID() const;
		std::string getPieceName() const;
		int getCurrentPlace() const;
		bool getRoundCompletion() const;
		
};

class Cell
{
	private:
		int cellID;
		CellType cellType;
		bool cellPermision = false;
	
	public:
		Cell(int& i, CellType& c) : cellID(i), cellType(c) {}

		void setCellPermission(Piece& piece);

		int getCellID() const;
		CellType getCellType() const;
		bool getCellPermission() const;
};

class Player
{
	private:
		Color playerColor;
		std::string playerName;
		std::vector<Piece> playerPieces;
		int xMarkedCell;
		int homePathCell;

	public:
		Player(Color& c, std::string& n, std::vector<Piece>& p, int& x, int& h) : playerColor(c), playerName(n), playerPieces(p), xMarkedCell(x), homePathCell(h) {}

		Color getPlayerColor() const;
		std::string getPlayerName() const;
		std::vector<Piece> getPlayerPieces() const;
};

class Board
{
	private:
		std::vector<Cell> cells;
		std::vector<Player> players;
		int noOfPlayers = 4;

	public:
		Board();

		int getNoOfPlayers() const;
};


int rollDie();
std::string convertEnumToString(Color color, NameType type);
Color pickFirstPlayer(int noOfPlayers);
