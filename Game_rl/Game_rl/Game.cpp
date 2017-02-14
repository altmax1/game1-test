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
}

void Game::MakeDungeon ()
{
	Dungeon *ptr;
	ptr = Dungeon::MakeDungeon (1, 80, 40, 40);
	ptr->ReturnDungeon (DungeonCells);
	//delete ptr;

}

void Game::MakeLevel ( int Width, int Height, char *DungeonCells)
{
	MyLevel = new level;
	MyLevel->LevelCreate (Width, Height, DungeonCells);
}

void Game::GameInit()
{
	MakeDungeon();
	cout << "MakeDungeon(); complite";
	MakeLevel (80,40,DungeonCells);

	//временный кусок для проверки
	terminal_clear();
	int iter = 0;
	for (int y = 0; y < 40; y++)
		for (int x = 0; x<80; x++)
		{
		terminal_put (x, y, DungeonCells [iter]);
		iter++;
		}
	terminal_refresh();
	terminal_read();
	

}	