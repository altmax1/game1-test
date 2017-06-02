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
	MapPtr = temp[0].find("MiniMapCoordX");
	MiniMapCoordX = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("MiniMapCoordY");
	MiniMapCoordY = atoi(MapPtr->second.c_str());
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
	return;

}
void Interface::PrintMiniMapBorder ()
{
	terminal_color (0xFFA64800);
	int SizeX = (LevelWidth/4);
	if (LevelWidth%4>0)
		SizeX++;
	int SizeY = (LevelHeight/8);
	if (LevelHeight%4>0)
		SizeY++;
	terminal_put (MiniMapCoordX, MiniMapCoordY, 0x2554);
	terminal_put (MiniMapCoordX, MiniMapCoordY+SizeY+1, 0x255A);
	terminal_put (MiniMapCoordX+SizeX+1, MiniMapCoordY, 0x2557);
	terminal_put (MiniMapCoordX+SizeX+1, MiniMapCoordY+SizeY+1, 0x255D);
	for (int i = MiniMapCoordX+1; i<=MiniMapCoordX+SizeX; i++)
	{
		terminal_put (i,MiniMapCoordY, 0x2550);
		terminal_put (i,MiniMapCoordY+SizeY+1, 0x2550);	
	}
	for (int i = MiniMapCoordY+1; i<=MiniMapCoordY+SizeY; i++)
	{
		terminal_put (MiniMapCoordX, i, 0x2551);
		terminal_put (MiniMapCoordX+SizeX+1, i, 0x2551);
	}

}

void Interface::PrintMiniMap ()
{	
	PrintMiniMapBorder ();
	char c, basetype;
	terminal_composition (TK_ON);
	for (int y = 0; y< LevelHeight; y++)
		for (int x = 0; x < LevelWidth; x++)
		{
			basetype = Mylevel->GetBaseType(x,y);
			c = Mylevel->GetFlagsFOV (x, y);
			if ((c&FOV_CELL_VISITED)&& basetype=='#')
			{
				terminal_color ("grey");
				terminal_put_ext (MiniMapCoordX+1,MiniMapCoordY+1, x*2, y*2, 729);
			}
			if ((c&FOV_CELL_VISITED)&& basetype=='.')
			{	
				terminal_color ("blue");
				terminal_put_ext (MiniMapCoordX+1,MiniMapCoordY+1, x*2, y*2, 729);
			}
		}
	terminal_color ("white");
	terminal_put_ext (MiniMapCoordX+1,MiniMapCoordY+1, GamerCoordX*2, GamerCoordY*2, 729);
	terminal_composition (TK_OFF);
	return;
}

void Interface::PrintBorder ()
{
	terminal_color (0xFFA64800);
	terminal_put (0,0,0x250F);
	for (int i = 1; i <=FOVWidth; i++)
	{
		terminal_put (i,0, 0x2501);
		terminal_put (i, FOVHeight+1, 0x2501);
	}
	terminal_put (FOVWidth+1,0, 0x2513);
	for (int i = 1; i <= FOVHeight; i++)
	{
		terminal_put (0,i, 0x2503);
		terminal_put (FOVWidth+1, i, 0x2503);
	}
	terminal_put (0, FOVHeight+1, 0x2517);
	terminal_put (FOVWidth+1, FOVHeight+1, 0x251B);
	
}

void Interface::PrintItems (int BaseX, int BaseY, int FOVX, int FOVY)
{
	int ItemID = Mylevel->GetItemIDByCell (BaseX, BaseY,0);
	Game *MyGame;
	MyGame = Game::GetGameInstance ();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	
	int ItemType = MyItems ->GetTypeById (ItemID); //подправлено ItemId на 1 временно.
	if (ItemType == 0)
		terminal_put (FOVX,FOVY,92);
	else if ((ItemType == 1) || (ItemType == 2))
		terminal_put (FOVX,FOVY,124);
	else terminal_put (FOVX,FOVY, 37);
	if ((Mylevel->GetQuantityItemsOnCell(BaseX, BaseY))>1)
	{
		level *MyLevel;
		MyLevel = MyGame->GetLevel();
		char flags = MyLevel->GetFlagsFOV(BaseX, BaseY);
		if (flags&FOV_CELL_VISITED)
		{
		terminal_layer (2);
		terminal_color ("red");
		terminal_put (FOVX,FOVY, 731);
		terminal_layer (0);
		terminal_color ("white");
		}
	}
}

void Interface::PrintFOV ()
{
	GetGamerAndLevel();
	int LeftUpX, LeftUpY;
	LeftUpX = GamerCoordX - FOVWidth/2;
	LeftUpY = GamerCoordY - FOVHeight/2;
	CorrectLeftUp (LeftUpX, LeftUpY);
	char c;
	int ItemCounter;
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
			terminal_put (x+1,y+1,c);
			if ((x+LeftUpX == GamerCoordX) && (y+LeftUpY == GamerCoordY ))
			{
				terminal_layer (10);
				terminal_put (x+1,y+1, 64);
				terminal_layer (0);
			}
			ItemCounter = Mylevel->GetQuantityItemsOnCell (x+LeftUpX,y+LeftUpY);
			if (ItemCounter >0)
				PrintItems (x+LeftUpX,y+LeftUpY, x+1, y+1);
			if ((Mylevel->GetCreature(x+LeftUpX,y+LeftUpY))>=0)
			{
				terminal_layer (0);
				terminal_put (x+1,y+1, 82);
				terminal_layer (0);
			}

		}
	PrintBorder();
	PrintMiniMap ();
	return;
}