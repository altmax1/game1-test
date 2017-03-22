#include "StdAfx.h"
#include "LuaAdapter.h"

using namespace std;
using namespace luabridge;
LuaAdapter::LuaAdapter(void)
{
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyGamer = MyGame->GetGamer();
	MyBestiary = MyGame->GetBestiary();
}


LuaAdapter::~LuaAdapter(void)
{
}
void LuaAdapter::LuaDesc (lua_State *L)
{
	
	
	getGlobalNamespace(L)
			.beginClass <LuaAdapter> ("Game")
			.addFunction ("GetTileBaseType", &LuaAdapter::GetTileBaseType)
			.addFunction ("GetLevelWidth", &LuaAdapter::GetLevelWidth)
			.addFunction ("GetLevelHeight", &LuaAdapter::GetLevelHeight)
			.addFunction ("CreateTheBeast", &LuaAdapter::CreateTheBeast)
			.addFunction ("MyRandom", &LuaAdapter::GetRandom)
			.addFunction ("PathFind", &LuaAdapter::PathFind)
			.addFunction ("GetCellPassable", &LuaAdapter::GetCellPassable)
			.addFunction ("SetCellPassable", &LuaAdapter::SetPassable)
			.addFunction ("GetBeastNumber", &LuaAdapter::GetBeastNumber)
			.addFunction ("RemoveCreature", &LuaAdapter::RemoveCreature)
			.addProperty ("GamerX", &LuaAdapter::GetGamerX, &LuaAdapter::SetGamerX)
			.addProperty ("GamerY", &LuaAdapter::GetGamerY, &LuaAdapter::SetGamerY)
		.endClass();

	getGlobalNamespace (L)
		.beginClass <Beast> ("Beast")
		.addProperty ("CoordX", &Beast::GetCoordX, &Beast::SetCoordX)
		.addProperty ("CoordY", &Beast::GetCoordY, &Beast::SetCoordY)
		.addProperty ("HP", &Beast::GetHP,&Beast::SetHP)
		.addProperty ("Dex", &Beast::GetDex, &Beast::SetDex)
		.addProperty ("Energy", &Beast::GetEnergy, &Beast::SetEnergy)
		.addProperty ("Defense", &Beast::GetDefence, &Beast::SetDefense)
		.addProperty ("Speed", &Beast::GetSpeed, &Beast::SetSpeed)
		.addProperty ("RegenHP", &Beast::GetRegenHp, &Beast::SetRegenHP)
		.addProperty ("RegenEnergy", &Beast::GetRegenEnergy, &Beast::SetRegenEnergy)
		.addProperty ("Str", &Beast::GetRegenEnergy, &Beast::SetRegenEnergy)
		.addProperty ("Behavior", &Beast::GetBehavior, &Beast::SetBehavior)
		.addProperty ("Sleeping", &Beast::GetSleep, &Beast::SetSleep)
		.addProperty ("Active", &Beast::GetActive, &Beast::SetActive)
		.endClass();
		
}

char  LuaAdapter::GetTileBaseType (int x, int y) const
{
	return MyLevel->GetBaseType (x,y);
}

int LuaAdapter::GetLevelWidth ()
{
	return (MyLevel->GetLevelWidth());
}

int LuaAdapter::GetLevelHeight()
{
	return (MyLevel->GetLevelHeight());
}

int LuaAdapter::GetGamerX () const 
{
	return MyGamer->GetCoordX ();
}
int LuaAdapter::GetGamerY () const 
{
	return MyGamer->GetCoordY ();
}
void LuaAdapter::SetGamerX (int a)
{
	MyGamer->SetCoordX (a);
	return;
}
void LuaAdapter::SetGamerY (int a)
{
	MyGamer->SetCoordY (a);
	return;
}
void LuaAdapter::CreateTheBeast (int ID, int x, int y)
{
	MyBestiary->MakeCreature (ID, x, y);
	return;
}

int LuaAdapter::GetRandom (int a)
{
	return (rand() %a);
}

int LuaAdapter::PathFind (int StartX, int StartY, int EndX, int EndY)
{
	return MyLevel->PathFind (StartX, StartY, EndX, EndY);
}

int LuaAdapter::GetCellPassable (int x, int y)
{
	return MyLevel->GetPassable (x,y);
}

void LuaAdapter::SetPassable (int x, int y, int passable)
{
	MyLevel->SetPassable (x,y,passable);
	return;
}

int LuaAdapter::GetBeastNumber (int x, int y)
{
	return MyLevel->GetCreature (x,y);
}

void LuaAdapter::RemoveCreature (int Num)
{
	MyBestiary->RemoveCreature (Num);
	return;
}