#include "StdAfx.h"
#include "Game.h"
#include "Dungeon.h"

//#include 

using namespace std;

Game::Game(void)
{
	
}


Game::~Game(void)
{
	delete MyLevel;
	delete MyGamer;
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


void Game::GameInit()
{
	int KeyCode;
	MakeLevel (1,80,40,40);
	MakeGamer ();
	MyLevel->LevelPrint();
	MyGamer->GamerPlacing();
	while (1)
	{
	terminal_color (0xFFDFDFA9);
	MyLevel->LevelPrint();
	terminal_color ("white");
	MyGamer->GamerPrint();
	terminal_refresh();
	KeyCode = terminal_read();
	if (KeyCode == TK_ESCAPE)
		break;
	MyGamer->Move(KeyCode);
	}
	return;
		

}	