#pragma once
#include "level.h"
#include "Gamer.h"
#include "Items.h"
#include "Interface.h"
#include "X_File.h"



class Game
{
private:
	static Game *MyGame;
	level *MyLevel;
	Gamer *MyGamer;
	Items *MyItems;
	Interface *MyInterface;
	Game(void);

public:
	static Game* GetGameInstance ();
	~Game(void);
	void GameInit ();
	void MakeLevel (int Type, int Width, int Height, int Density);
	void MakeGamer ();
	void MakeItems ();
	void MakeInterface();
	Items* GetItems ();
	level *GetLevel();
	Gamer* GetGamer();
	
};

