#pragma once
#include "level.h"
#include "Gamer.h"



class Game
{
private:
	level *MyLevel;
	Gamer *MyGamer;
	
public:
	Game(void);
	~Game(void);
	void GameInit ();
	void MakeLevel (int Type, int Width, int Height, int Density);
	void MakeGamer ();
	
};

