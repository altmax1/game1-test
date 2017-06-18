#include "StdAfx.h"
#include "Game.h"
#include "Dungeon.h"
#include "LuaAdapter.h"

//#include 

using namespace std;

Game* Game::MyGame = 0;

Game::Game(void)
{
	DeveloperMode = 0;
	PlayerMoved = 0;
	Moves = 0;
}

Game* Game::GetGameInstance ()
{
	if (!MyGame)
	{
		MyGame  = new Game;
	}
	return MyGame;

}


Game::~Game(void)
{
	delete MyLevel;
	delete MyGamer;
}

Items* Game::GetItems ()
{
	return MyItems;
}

level* Game::GetLevel()
{
	return MyLevel;
}

Gamer* Game::GetGamer()
{
	return MyGamer;
}

Bestiary* Game::GetBestiary()
{
	return MyBestiary;
}

Interface* Game::GetInterface ()
{
	return MyInterface;
}

void Game::MakeLevel (int Type, int Width, int Height, int Density)
{
	MyLevel = new level;
	MyLevel->LevelCreate (Type, Width, Height, Density);
}

void Game::MakeGamer()
{
	using namespace luabridge;
	MyGamer = new Gamer (MyLevel) ;
	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\Gamer.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef MakeGamerLua = getGlobal(L, "MakeGamer");
    //
	try {
            MakeGamerLua (Luaad);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
	return;
}

void Game::MakeItems()
{
	MyItems = new Items;
	//MyItems->GetWeaponsFromFile();
	//MyItems->GetArmoursFromFile();
	return;
}


void Game::MakeInterface()
{
	MyInterface = new Interface;
	return;
}

void Game::MakeBestiary()
{
	MyBestiary = new Bestiary;
	MyBestiary->MakeCreatures();
	return;
}

void Game::MakeAIMove ()
{
	if (PlayerMoved == 1)
	{
	MyBestiary->MakeBeastsMove ();
	ResetPlayerMoved ();
	}
	return;
}

void Game::GameInit()
{
	int KeyCode;
	MakeItems();
	MakeLevel (1,128,40,40);
	MakeGamer ();
	MakeInterface();
	MakeBestiary();
	MyLevel->PlaceItems();
	MyLevel->LevelPrint();
	MyGamer->GamerPlacing();
	while (1)
	{
	terminal_color (0xFFDFDFA9);
	MyInterface->PrintFOV();
	terminal_color ("white");
	terminal_refresh();
	KeyCode = terminal_read();
	if (KeyCode == TK_ESCAPE)
		break;
	MyGamer->Move(KeyCode);
	MakeAIMove();
	}
	return;
		

}	

void Game::ChangeGameMode ()
{
	if (DeveloperMode == 0)
	{
		DeveloperMode = 1;
		MyInterface->SetMessage ("Developer Mode ON");
	}
	else
	{
		DeveloperMode = 0;
		MyInterface->SetMessage ("Developer Mode OFF");
	}
	return;
}