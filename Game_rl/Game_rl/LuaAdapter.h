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
	void LuaDesc (lua_State *L);
	char GetTileBaseType (int x, int y) const;
	int GetLevelWidth();
	int GetLevelHeight ();
	int GetRandom (int a);
	void CreateTheBeast (int ID, int x, int y);
	int GetGamerX () const;
	void SetGamerX ( int a);
	int GetGamerY () const;
	void SetGamerY (int a);
	LuaAdapter(void);
	~LuaAdapter(void);
};

