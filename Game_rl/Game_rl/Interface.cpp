#include "StdAfx.h"
#include "Interface.h"
#include "Game.h"





Interface::Interface(void)
{
	ReadIniFile();
	MessageExist = 0;
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
	else if (ItemType>=10 && ItemType<20)
		terminal_put (FOVX, FOVY,0x00B6);
	else if (ItemType>=20 && ItemType<30)
		terminal_put (FOVX, FOVY, 0x00B9);
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
				GamerCoordXInTerminal = x+1;
				GamerCoordYInTerminal = y+1;
				terminal_layer (0);
			}
			ItemCounter = Mylevel->GetQuantityItemsOnCell (x+LeftUpX,y+LeftUpY);
			if (ItemCounter >0)
				PrintItems (x+LeftUpX,y+LeftUpY, x+1, y+1);
			if ((Mylevel->GetCreature(x+LeftUpX,y+LeftUpY))>=0)
			{
				terminal_layer (0);
				//terminal_put (x+1,y+1, 82);
				PrintCreature (x+1,y+1,x+LeftUpX,y+LeftUpY,Mylevel->GetCreature(x+LeftUpX,y+LeftUpY));
				terminal_layer (0);
			}

		}
	PrintBorder();
	PrintMiniMap ();
	PrintMessage ();
	return;
}

int Interface::SelectTarget ()
{
	terminal_layer(100);
	int TempX = GamerCoordXInTerminal;
	int TempY = GamerCoordYInTerminal;
	while (1)
	{
		terminal_put (TempX, TempY, 0x1000);
		terminal_refresh();
		int a = terminal_read();
		if (a == TK_ESCAPE)
		{
			terminal_clear_area(1,1,FOVWidth, FOVHeight);
			terminal_layer (0);
			return 0;
		}
		if (a==TK_RIGHT || a== TK_KP_6)
			if (TempX < FOVWidth)
				TempX++;
		if (a==TK_LEFT || a == TK_KP_4)
			if (TempX>1)
				TempX--;
		if (a== TK_DOWN || a == TK_KP_2)
			if (TempY < FOVHeight)
				TempY++;
		if (a == TK_UP || a == TK_KP_8)
			if (TempY>1)
				TempY--;
		terminal_clear_area(1,1,FOVWidth, FOVHeight);
		
		if (a == TK_ENTER && terminal_check(TK_SHIFT))
		{
			int DeltaX = TempX-GamerCoordXInTerminal;
			int DeltaY = TempY-GamerCoordYInTerminal;
			int TargetX = GamerCoordX+DeltaX;
			int TargetY = GamerCoordY+DeltaY;
			terminal_layer(0);
			return TargetX*1000+TargetY+1000000000;
		}
		if (a == TK_ENTER)
		{
			int DeltaX = TempX-GamerCoordXInTerminal;
			int DeltaY = TempY-GamerCoordYInTerminal;
			int TargetX = GamerCoordX+DeltaX;
			int TargetY = GamerCoordY+DeltaY;
			terminal_layer(0);
			return TargetX*1000+TargetY;
		}

	}
	return 0;
}

void Interface::SetMessage (string CurrentMessage)
{
	MessageExist = 1;
	Message = CurrentMessage;
}

void Interface::PrintMessage ()
{
	if (MessageExist == 1)
	{
		MessageExist = 0;
		terminal_print_ext (2,30,40,5,TK_ALIGN_DEFAULT, Message.c_str());
		
	}
}

void Interface::PrintMessageNow (string Message)
{
	terminal_clear_area ( 2, 30, 40, 5);
	terminal_print_ext (2,30,40,5,TK_ALIGN_DEFAULT, Message.c_str());
	terminal_refresh();

}

void Interface::PrintCreature (int x, int y, int LevelX, int LevelY, int NumOfCreature)
{
	Bestiary *MyBestiary;
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyBestiary = MyGame->GetBestiary();
	int CharCode = MyBestiary->GetCharCode (NumOfCreature);
	int ColorVisible = MyBestiary->GetColorVisible(NumOfCreature);
	int TempColor = terminal_state(TK_COLOR);
	int ColorNotVisible = MyBestiary->GetColorNotVisible(NumOfCreature);
			if ((Mylevel->GetFlagsFOV(LevelX,LevelY))&FOV_CELL_VISIBLE)
			{
				terminal_color (ColorVisible);
				terminal_put(x,y,CharCode);
				PrintHealthBar (x,y,NumOfCreature,MyBestiary);
			}
	terminal_color(TempColor);
	return;

}

void Interface::PrintHealthBar (int x, int y, int NumOfCreature, Bestiary *A)
{
	terminal_composition (TK_ON);
	int MaxHP = A->GetMaxHP(NumOfCreature);
	int HP = A->GetHP(NumOfCreature);
	if (HP>MaxHP*0.3)
		terminal_color ("green");
	else
		terminal_color ("red");
	int step = (HP*100)/((MaxHP*100)/6)+1;
	cout << "step "<<step<<endl;
	int dx = -3;
	for (int i=0; i<step; i++)
	{
		terminal_put_ext (x,y,dx+i,0,0x02D9);
	}
	terminal_composition (TK_OFF);
	return;	
}
