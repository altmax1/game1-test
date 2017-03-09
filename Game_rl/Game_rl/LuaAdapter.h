#pragma once
#include "Game.h"
class LuaAdapter
{
private:
	Game *MyGame;
	level *MyLevel;
	Gamer *MyGamer;
	Bestiary *MyBestiary;
public:
	void LuaDesc ();
	char GetTileBaseType (int x, int y) const;
	int GetLevelWidth();
	int GetLevelHeight ();
	void CreateTheBeast (int ID);
	LuaAdapter(void);
	~LuaAdapter(void);
};

