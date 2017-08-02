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
	FullLogging = 1;
	for (int i = 0; i < 100; i++)
		MemoryCell[i] = 0;
	
	//Luaad = new LuaAdapter;
	//Luaad->LuaDesc(L);

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
	MyGame = nullptr;
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
	//MyLevel = new level;
	//MyLevel->LevelCreate (Type, Width, Height, Density);
	CreateNewLevel();
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
	//MyBestiary->MakeCreatures();
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

Log * Game::GetLog()
{
	return MyLog;
}

void Game::GameInit()
{
	int KeyCode;
	MakeLog();
	MakeItems();
	MakeBestiary();
	MakeLevel (1,128,40,40);
	MakeGamer ();
	MakeInterface();
	MakeLuaadapter();
	MyLevel->PlaceItems();
	//MyLevel->LevelPrint();
	MyGamer->GamerPlacing();
	//MyLevel->LoadLevel();
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
	MyLevel->LevelProcessEffects();
	MakeAIMove();
	}
	//Destructor();
	return;
		

}

void Game::MakeLog()
{
	MyLog = new Log;
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

int Game::GetFullLogging()
{
	return FullLogging;
}

void Game::CreateNewLevel()
{
	MyLevel = new level;
	Levels.push_back(MyLevel);
	MyLevel->SetLevelNum(Levels.size());
	using namespace luabridge;

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\MakeLevel.lua");
	lua_pcall(L, 0, 0, 0);
	luabridge::LuaRef MakeLevel = luabridge::getGlobal(L, "MakeLevel");
	//
	try {
		MakeLevel(Luaad, MyLevel);
	}
	catch (luabridge::LuaException const& e) {
		std::cout << "LuaException: " << e.what() << std::endl;
	}


}

void Game::SetCurrentLevel(int NumOfLevel)
{
	if (NumOfLevel > 0 && NumOfLevel <= Levels.size())
		MyLevel = Levels[NumOfLevel - 1];
}

void Game::Destructor()
{
	delete MyGamer;
	//delete MyInterface;
	delete MyBestiary;
	delete MyInterface;
	delete MyItems;
	/*vector <level*>::iterator p;
	p = Levels.begin();
	while (p!= Levels.end())
	{
		
		delete *p;
		p++;
	}*/
	/*for (int i = 0; i < Levels.size(); i++)
	{
		Levels[i]->~level();
		delete Levels[i];
	}*/
	//delete MyLevel;

	Levels.clear();
	
}

lua_State* Game::GetLuaState()
{
	return L;
}

void Game::MakeLuaadapter()
{
	L = luaL_newstate();
	luabridge:luaL_openlibs(L);
	Luaad = new LuaAdapter;
	Luaad->LuaDesc(L);
}

LuaAdapter*  Game::GetLuaadapter()
{
	return Luaad;
}

int Game::GetMemotyCell(int Num)
{
	if (Num >= 0 && Num < 100)
	return MemoryCell[Num];
}

void Game::SetMemoryCell(int Num, int Value)
{
	if (Num >= 0 && Num < 100)
		MemoryCell[Num] = Value;
}

void Game::SaveGame()
{
	//MyLevel->SaveLevel();
	ofstream out(".\\Files\\save\\level.sav", ios::binary | ios::out );
	int NumOfLevels = Levels.size();
	out.write((char*)&NumOfLevels, sizeof NumOfLevels);
	out.close();
	for (int i = 0; i < NumOfLevels; i++)
	{
		Levels[i]->SaveLevel();
	}
	MyBestiary->SaveBestiary();
	MyItems->SaveItems();
	MyGamer->SaveGamer();
	SaveGameVariables();

}

void Game::LoadGame()
{
	ifstream in(".\\Files\\save\\level.sav", ios::binary | ios::in);
	int NumOfLevels;
	in.read((char*)&NumOfLevels, sizeof NumOfLevels);
	Levels.clear();
	for (int i = 0; i<NumOfLevels; i++)
	{
		MyLevel = new level;
		MyLevel->LoadLevel(in);
		Levels.push_back(MyLevel);
	}
	MyBestiary->LoadBestiary();
	MyItems->LoadItems();
	MyGamer->LoadGamer();
	LoadGameVariables();

}

void Game::SaveGameVariables()
{
	ofstream out(".\\Files\\Save\\game.sav", ios::binary | ios::out);
	int temp = MyLevel->GetLevelNum();
	out.write((char*)&temp, sizeof temp);
	out.write((char*)&DeveloperMode, sizeof DeveloperMode);
	out.write((char*)&FullLogging, sizeof FullLogging);
	out.write((char*)&PlayerMoved, sizeof PlayerMoved);
	out.write((char*)MemoryCell, sizeof MemoryCell[0] * 100);
}

void Game::LoadGameVariables()
{
	ifstream in(".\\Files\\Save\\game.sav", ios::binary | ios::in);
	int temp;
	in.read((char*)&temp, sizeof temp);
	in.read((char*)&DeveloperMode, sizeof DeveloperMode);
	in.read((char*)&FullLogging, sizeof FullLogging);
	in.read((char*)&PlayerMoved, sizeof PlayerMoved);
	in.read((char*)MemoryCell, sizeof MemoryCell[0] * 100);
	MyLevel = Levels[temp - 1];
}
