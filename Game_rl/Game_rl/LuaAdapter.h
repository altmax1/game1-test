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
	int GetGamerHP () const;
	void SetGamerHP (int a);
	int GetGamerStr () const;
	void SetGamerStr (int a);
	int GetGamerMaxHP () const;
	void SetGamerMaxHP (int a);
	int GetGamerDex () const;
	void SetGamerDex (int a);
	int GetGamerEnergy () const;
	void SetGamerEnergy (int a);
	int GetGamerMaxEnergy () const;
	void SetGamerMaxEnergy (int a);
	int GetGamerDefense () const;
	void SetGamerDefense (int a);
	int GetGamerRegenHP () const;
	void SetGamerRegenHP (int a);
	int GetGamerRegenEnergy () const;
	void SetGamerRegenEnergy (int a);
	int GetBeastNumber (int x, int y);
	void RemoveCreature (int Num);
	void AttackBeastByNum (int Num);
	int LOS (int x1, int y1, int x2, int y2);
	LuaAdapter(void);
	~LuaAdapter(void);
};

