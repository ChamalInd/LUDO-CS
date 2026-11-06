#include "../includes/includes.h"

void Cell::setCellOccupent(Piece* piece)
{
	cellOccupent = piece;
}

Piece* Cell::getCellOccupent() const
{
	return cellOccupent;
}

int Cell::getCellID() const
{
	return cellID;
}
		
CellType Cell::getCellType() const
{
	return cellType;
}
