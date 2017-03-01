#include "StdAfx.h"
#include "Game.h"
#include "Dungeon.h"

//#include 

using namespace std;

Game* Game::MyGame = 0;

Game::Game(void)
{
	
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



void Game::MakeLevel (int Type, int Width, int Height, int Density)
{
	MyLevel = new level;
	MyLevel->LevelCreate (Type, Width, Height, Density);
}

void Game::MakeGamer()
{
	MyGamer = new Gamer (MyLevel) ;
	return;
}

void Game::MakeItems()
{
	MyItems = new Items;
	MyItems->GetWeaponsFromFile();
	return;
}
void Game::MakeInterface()
{
	MyInterface = new Interface;
	return;
}


void Game::GameInit()
{
	int KeyCode;
	MakeItems();
	MakeLevel (1,128,40,40);
	MakeGamer ();
	MakeInterface();
	MyLevel->PlaceItems();
	MyLevel->LevelPrint();
	MyGamer->GamerPlacing();
	while (1)
	{
	terminal_color (0xFFDFDFA9);
	MyInterface->PrintFOV();
	//MyLevel->LevelPrint();
	terminal_color ("white");
	//MyGamer->GamerPrint();
	terminal_refresh();
	KeyCode = terminal_read();
	if (KeyCode == TK_ESCAPE)
		break;
	MyGamer->Move(KeyCode);
	}
	return;
		

}	