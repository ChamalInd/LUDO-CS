#include "../includes/includes.h"

void Cell::setCellOccupentID(std::string newOccupent)
{
	occupentID = newOccupent;
}
		
std::string Cell::getCellOccupentID() const
{
	return occupentID;
}

