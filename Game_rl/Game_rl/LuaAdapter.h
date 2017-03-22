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
	int PathFind (int StartX, int StartY, int EndX, int EndY);
	int GetCellPassable (int x, int y);
	void SetPassable (int x, int y, int passable);
	int GetBeastNumber (int x, int y);
	void RemoveCreature (int Num);
	LuaAdapter(void);
	~LuaAdapter(void);
};

