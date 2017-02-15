#include "StdAfx.h"
#include "Game.h"
#include "Dungeon.h"

//#include 

using namespace std;

Game::Game(void)
{
	cout << "Game constructor" << endl;
}


Game::~Game(void)
{
	cout << "Game destructor" << endl;
	//MyLevel->~level();
	delete MyLevel;
}




void Game::MakeLevel (int Type, int Width, int Height, int Density)
{
	MyLevel = new level;
	MyLevel->LevelCreate (Type, Width, Height, Density);
}



void Game::GameInit()
{
	MakeLevel (1,80,40,40);
	MyLevel->LevelPrint();
	return;
		

}	