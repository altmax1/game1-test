#pragma once
#include "level.h"

class Gamer
{
private:
	int CoordX;
	int CoordY;
	level *MyLevel;
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

