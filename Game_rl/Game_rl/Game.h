#pragma once
#include "level.h"



class Game
{
private:
	level *MyLevel;
	
public:
	Game(void);
	~Game(void);
	void GameInit ();
	void MakeLevel (int Type, int Width, int Height, int Density);
};

