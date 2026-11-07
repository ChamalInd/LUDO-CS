#include "../includes/includes.h"

#define NO_OF_CELLS 72

Board::Board()
{
	for (int i = 0; i < NO_OF_CELLS; i++)
	{
		Cell cell(i);
		cells.push_back(cell);
	}
}

bool Board::checkCellValidity(int cellID)
{
	// to be implemented
}
