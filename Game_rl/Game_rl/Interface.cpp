#include "StdAfx.h"
#include "Interface.h"
#include "Game.h"




Interface::Interface(void)
{
	ReadIniFile();
}


Interface::~Interface(void)
{
}

void Interface::ReadIniFile()
{
	FileContent MyFile;
	vector <map <string,string>> temp;
	X_File::X_ReadFile ((LPCTSTR)L".\\Files\\Interface.ini", MyFile);
	X_File::X_ParseIniFile (MyFile, temp);
	map <string,string>::iterator MapPtr;
	MapPtr = temp[0].find("WindowHeight");
	WindowHeight = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("WindowWidth");
	WindowWidth = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("FOVHeight");
	FOVHeight = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("FOVWidth");
	FOVWidth = atoi(MapPtr->second.c_str());
	return;

}
void Interface::GetGamerAndLevel ()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Mylevel = MyGame->GetLevel();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	GamerCoordX = MyGamer->GetCoordX();
	GamerCoordY = MyGamer->GetCoordY();
	LevelWidth = Mylevel->GetLevelWidth();
	LevelHeight = Mylevel->GetLevelHeight();
	return;
}

void Interface::CorrectLeftUp ( int &x, int &y)
{
	if (x<0)
		x=0;
	if (y<0)
		y=0;
	if (x>LevelWidth-1-FOVWidth)
		x = LevelWidth-1-FOVWidth;
	if (y>LevelHeight-1-FOVHeight)
	y = LevelHeight-1-FOVHeight;
	cout << x<< " " << y<< endl;
	return;

}

void Interface::PrintFOV ()
{
	GetGamerAndLevel();
	int LeftUpX, LeftUpY;
	LeftUpX = GamerCoordX - FOVWidth/2;
	LeftUpY = GamerCoordY - FOVHeight/2;
	CorrectLeftUp (LeftUpX, LeftUpY);
	char c;
	terminal_clear();
	for (int y = 0; y <FOVHeight; y++)
		for (int x =0; x < FOVWidth; x++)
		{
			c = Mylevel->GetBaseType(x+LeftUpX,y+LeftUpY);
			if ((Mylevel->GetFlagsFOV(x+LeftUpX,y+LeftUpY))&FOV_CELL_VISIBLE)
				terminal_color ("white");
			else if ((Mylevel->GetFlagsFOV(x+LeftUpX,y+LeftUpY))&FOV_CELL_VISITED) 
				terminal_color (0xafdfdfa9);
			else
				terminal_color ("black");
			terminal_put (x,y,c);
			if ((x+LeftUpX == GamerCoordX) && (y+LeftUpY == GamerCoordY ))
				terminal_put (x,y, 64);
		}

	/*terminal_layer (20);
	terminal_put (GamerCoordX, GamerCoordX, 64);
	terminal_layer (0);*/
	return;
}