#pragma once
#include "level.h"



class Game
{
private:
	level *MyLevel;
	char *DungeonCells;

public:
	Game(void);
	~Game(void);
	void GameInit ();
	void MakeDungeon ();
	void MakeLevel ( int Width, int Height, char *DungeonCells);
};

