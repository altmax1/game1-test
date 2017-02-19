#pragma once
#include "level.h"
#include "Gamer.h"
#include "Items.h"



class Game
{
private:
	static Game *MyGame;
	level *MyLevel;
	Gamer *MyGamer;
	Items *MyItems;
	Game(void);

public:
	static Game* GetGameInstance ();
	~Game(void);
	void GameInit ();
	void MakeLevel (int Type, int Width, int Height, int Density);
	void MakeGamer ();
	void MakeItems ();
	Items* GetItems ();
	
};

