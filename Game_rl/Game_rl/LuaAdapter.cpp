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
			.addFunction ("AttackBeastByNum", &LuaAdapter::AttackBeastByNum)
			.addFunction ("LOS", &LuaAdapter::LOS)
			.addFunction ("PathFind", &LuaAdapter::PathFind)
			.addProperty ("GamerX", &LuaAdapter::GetGamerX, &LuaAdapter::SetGamerX)
			.addProperty ("GamerY", &LuaAdapter::GetGamerY, &LuaAdapter::SetGamerY)
			.addProperty ("GamerHP", &LuaAdapter::GetGamerHP, &LuaAdapter::SetGamerHP)
			.addProperty ("GamerMaxHP", &LuaAdapter::GetGamerMaxHP, &LuaAdapter::SetGamerMaxHP)
			.addProperty ("GamerStr", &LuaAdapter::GetGamerStr, &LuaAdapter::SetGamerStr)
			.addProperty ("GamerDex", &LuaAdapter::GetGamerDex, &LuaAdapter::SetGamerDex)
			.addProperty ("GamerEnergy", &LuaAdapter::GetGamerEnergy, &LuaAdapter::SetGamerEnergy)
			.addProperty ("GamerMaxEnergy", &LuaAdapter::GetGamerMaxEnergy, &LuaAdapter::SetGamerMaxEnergy)
			.addProperty ("GamerDefense", &LuaAdapter::GetGamerDefense, &LuaAdapter::SetGamerDefense)
			.addProperty ("GamerRegenHP", &LuaAdapter::GetGamerRegenHP, &LuaAdapter::SetGamerRegenHP)
			.addProperty ("GamerRegenEnergy", &LuaAdapter::GetGamerRegenEnergy, &LuaAdapter::SetGamerRegenEnergy)
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
		.addProperty ("MaxAttack", &Beast::GetMaxAttack, &Beast::SetMaxAttack)
		.addProperty ("MinAttack", &Beast::GetMinAttack, &Beast::SetMinAttack)
		.addProperty ("AttackType", &Beast::GetAttackType, &Beast::SetAttackType)
		.addProperty ("IsDead", &Beast::GetIsDead, &Beast::SetIsDead)
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

int LuaAdapter::GetGamerHP () const
{
	return MyGamer->GetHP();
}
void LuaAdapter::SetGamerHP (int a)
{
	MyGamer->SetHP (a);
	return;
}
int LuaAdapter::GetGamerStr () const
{
	return MyGamer->GetStr();	
}
void LuaAdapter::SetGamerStr (int a)
{
	MyGamer->SetStr (a);
	return;
}
int LuaAdapter::GetGamerMaxHP () const
{
	return MyGamer->GetMaxHP();
}
void LuaAdapter::SetGamerMaxHP (int a)
{
	MyGamer->SetMaxHP (a);
	return;
}
int LuaAdapter::GetGamerDex () const
{
	return MyGamer->GetDex ();
}
void LuaAdapter::SetGamerDex (int a)
{
	MyGamer->SetDex (a);
	return;
}
int LuaAdapter::GetGamerEnergy () const
{
	return MyGamer->GetEnergy();
}
void LuaAdapter::SetGamerEnergy (int a)
{
	MyGamer->SetEnergy(a);
	return;
}
int LuaAdapter::GetGamerMaxEnergy () const
{
	return MyGamer->GetMaxEnergy();
}
void LuaAdapter::SetGamerMaxEnergy (int a)
{
	MyGamer->SetMaxEnergy(a);
	return;
}
int LuaAdapter::GetGamerDefense () const
{
	return MyGamer->GetDefense();
}
void LuaAdapter::SetGamerDefense (int a)
{
	MyGamer->SetDefense (a);
	return;
}
int LuaAdapter::GetGamerRegenHP () const
{
	return MyGamer->GetRegenHP ();
}
void LuaAdapter::SetGamerRegenHP (int a)
{
	MyGamer->SetRegenHP (a);
	return;
}
int LuaAdapter::GetGamerRegenEnergy () const
{
	return MyGamer->GetRegenEnergy();
}
void LuaAdapter::SetGamerRegenEnergy (int a)
{
	MyGamer->SetRegenEnergy(a);
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

void LuaAdapter::AttackBeastByNum (int Num)
{
	using namespace luabridge;

	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\GamerMove.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef GamerAttack = getGlobal(L, "GamerAttack");
	  //
	try {
            GamerAttack (Luaad, MyBestiary->GetCreatureFromLevel (Num), Num);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }

	
}

int LuaAdapter::LOS (int x1, int y1, int x2, int y2)
{
	return MyLevel->LOS (x1, y1, x2, y2);
}