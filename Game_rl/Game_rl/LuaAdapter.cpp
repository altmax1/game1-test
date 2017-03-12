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
			.beginClass <LuaAdapter> ("LuaAdapter")
			.addFunction ("GetTileBaseType", &LuaAdapter::GetTileBaseType)
			.addFunction ("GetLevelWidth", &LuaAdapter::GetLevelWidth)
			.addFunction ("GetLevelHeight", &LuaAdapter::GetLevelHeight)
			.addFunction ("CreateTheBeast", &LuaAdapter::CreateTheBeast)
		.endClass();
		
}

char  LuaAdapter::GetTileBaseType (int x, int y) const
{
	return MyLevel->GetBaseType (x,y);
}

int LuaAdapter::GetLevelWidth ()
{
	return MyLevel->GetLevelHeight();
}

int LuaAdapter::GetLevelHeight()
{
	return MyLevel->GetLevelHeight();
}

void LuaAdapter::CreateTheBeast (int ID)
{
	MyBestiary->PutCreatureInBOL (ID);
	return;
}