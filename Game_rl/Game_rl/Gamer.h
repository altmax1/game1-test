#pragma once
#include "level.h"
#include "Inventory.h"

class Gamer
{
private:
	int CoordX;
	int CoordY;
	level *MyLevel;
	Inventory *MyInventory;
public:
	Gamer(void);
	Gamer (level *LevelPtr);
	~Gamer(void);
	void Move(int Direction);
	void GamerPrint ();
	int GetCoordX ();
	int GetCoordY ();
	void GamerPlacing ();

	
};

