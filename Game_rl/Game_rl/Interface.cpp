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
	level *MyLevel;
	MyLevel = MyGame->GetLevel();
	char flags = MyLevel->GetFlagsFOV(BaseX, BaseY);
	
	int ItemType = MyItems ->GetTypeById (ItemID); //подправлено ItemId на 1 временно.
	int CharCode = MyItems->GetCharCode (ItemID);
	if (flags&FOV_CELL_VISIBLE)
		terminal_color (MyItems->GetColorVisible (ItemID));
	else if (flags&FOV_CELL_VISITED)
		terminal_color (MyItems->GetColorNotVisible (ItemID));
	else return;
	terminal_put (FOVX, FOVY, CharCode);
	
	if ((Mylevel->GetQuantityItemsOnCell(BaseX, BaseY))>1)
	{
		
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

void Interface::PrintEffects (int BaseX, int BaseY, int FOVX, int FOVY)
{
	int Effect = Mylevel->GetEffectTypeByNum (BaseX, BaseY, 1);
	if (Effect == FIRE)
	{
		terminal_color (0xffff7600);
		terminal_layer (5);
		terminal_composition (TK_ON);
		terminal_put (FOVX, FOVY, 0x25a0); //попробовать символы 2591, 2592, 2593, 25cf, 007f
		terminal_composition (TK_OFF);
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
			int Tile = Mylevel->GetTile(x + LeftUpX, y + LeftUpY);
			if ((Mylevel->GetFlagsFOV(x+LeftUpX,y+LeftUpY))&FOV_CELL_VISIBLE)
				terminal_color ("white");
			else if ((Mylevel->GetFlagsFOV(x+LeftUpX,y+LeftUpY))&FOV_CELL_VISITED) 
				terminal_color (0xafdfdfa9);
			else
				terminal_color ("black");
			terminal_put (x+1,y+1,c);
			if (Tile >= 0)
			{
				if ((Mylevel->GetFlagsFOV(x + LeftUpX, y + LeftUpY))&FOV_CELL_VISIBLE)
					terminal_color(0xffbf9e30); //желтый светлый
				else if ((Mylevel->GetFlagsFOV(x + LeftUpX, y + LeftUpY))&FOV_CELL_VISITED)
					terminal_color(0xafbf9e30); //желтый темный
				else
					terminal_color("black");

				if (Tile == 1000)
					terminal_put(x + 1, y + 1, 0x00a9);
				if (Tile == 2000)
					terminal_put(x + 1, y + 1, 0x00fb);
				if (Tile == 2001)
					terminal_put(x + 1, y + 1, 0x00fc);
			}
			if ((x+LeftUpX == GamerCoordX) && (y+LeftUpY == GamerCoordY ))
			{
				terminal_layer (10);
				terminal_put (x+1,y+1, 64);
				GamerCoordXInTerminal = x+1;
				GamerCoordYInTerminal = y+1;
				terminal_layer (0);
			}
			ItemCounter = Mylevel->GetQuantityItemsOnCell (x+LeftUpX,y+LeftUpY);
			if (ItemCounter >0) // рисуем вещи
				if (Tile != 2000 && Tile !=  2001)
					PrintItems (x+LeftUpX,y+LeftUpY, x+1, y+1);
			if ((Mylevel->GetCreature(x+LeftUpX,y+LeftUpY))>=0) // рисуем мобов
			{
				terminal_layer (0);
				PrintCreature (x+1,y+1,x+LeftUpX,y+LeftUpY,Mylevel->GetCreature(x+LeftUpX,y+LeftUpY));
				terminal_layer (0);
			}

			if (Mylevel->GetNumOfEffects(x+LeftUpX,y+LeftUpY) > 0) //рисуем эффекты
			{
				PrintEffects (x+LeftUpX, y+LeftUpY, x+1, y+1);
			}

		}
	PrintBorder();
	PrintMiniMap ();
	PrintMessage ();
	PrintHID();
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
	Message2.clear();
	MessageExist = 1;
	Message = CurrentMessage;
}

void Interface::SetMessage(wstring CurrentMessage)
{
	Message.clear();
	MessageExist = 1;
	Message2 = CurrentMessage;
}

void Interface::PrintMessage ()
{
	if (MessageExist == 1)
	{
		MessageExist = 0;
		terminal_print_ext (2,30,40,5,TK_ALIGN_DEFAULT, Message.c_str());
		terminal_print_ext(2, 30, 40, 5, TK_ALIGN_DEFAULT, Message2.c_str());
		
	}
}

void Interface::PrintMessageNow (string Message)
{
	terminal_clear_area ( 2, 30, 40, 5);
	terminal_print_ext (2,30,40,5,TK_ALIGN_DEFAULT, Message.c_str());
	terminal_refresh();

}

void Interface::PrintMessageNow(wstring Message)
{
	terminal_clear_area(2, 30, 40, 5);
	terminal_print_ext(2, 30, 40, 5, TK_ALIGN_DEFAULT, Message.c_str());
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

void Interface::PrintHID ()
{
	
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	PrintGamerHBar (MyGamer);
	PrintGamerEBar (MyGamer);
	PrintOtherHIDs (MyGamer);
	PrintInventory (MyGamer);
	
}

void Interface::PrintGamerHBar (Gamer *MyGamer)
{
	int HP = MyGamer->GetHP();
	int MaxHP = MyGamer->GetMaxHP();
	int steps = (HP*100)/(MaxHP*100/20);
	char *p = new char[12];
	_itoa (HP,p,10);
	terminal_color ("white");
	terminal_print (44,2, "HP:");
	terminal_print (48,2, p);
	terminal_color ("grey");
	for (int i=0; i<20;i++)
	{
		terminal_put (51+i,2,0x2586);
	}
	if (HP<MaxHP*30/100)
		terminal_color("red");
	else if (HP>=MaxHP*30/100 && HP<MaxHP*50/100)
		terminal_color ("yellow");
	else
		terminal_color ("green");
	for (int i=0; i<steps; i++)
	{
		terminal_put (51+i, 2, 0x2586);
	}
	delete [] p;
	return;

}

void Interface::PrintGamerEBar (Gamer *MyGamer)
{
	int EP = MyGamer->GetEnergy();
	int MaxEP = MyGamer->GetMaxEnergy();
	int steps = (EP*100)/(MaxEP*100/20);
	char *p = new char[3];
	_itoa (EP,p,10);
	terminal_color ("white");
	terminal_print (44,3, "EP:");
	terminal_print (48,3, p);
	terminal_color ("grey");
	for (int i=0; i<20;i++)
	{
		terminal_put (51+i,3,0x2586);
	}
	if (EP<MaxEP*30/100)
		terminal_color("red");
	else if (EP>=MaxEP*30/100 && EP<MaxEP*50/100)
		terminal_color ("yellow");
	else
		terminal_color ("blue");
	for (int i=0; i<steps; i++)
	{
		terminal_put (51+i, 3, 0x2586);
	}
	delete [] p;
	return;
}

void Interface::PrintOtherHIDs (Gamer *MyGamer)
{
	terminal_color ("white");
	char *temp = new char [10];
	int Str = MyGamer->GetStr ();
	_itoa (Str, temp, 10);
	terminal_print (44,5, "Str:");
	terminal_print (49,5, temp);
	int Dex = MyGamer->GetDex ();
	_itoa (Dex, temp, 10);
	terminal_print (44,6, "Dex:");
	terminal_print (49,6, temp);
	int Def = MyGamer->GetDefense ();
	_itoa (Def, temp, 10);
	terminal_print (44,7, "Def");
	terminal_print (49,7, temp);
	Equipment *MyEquipment;
	MyEquipment = MyGamer->GetEquipment();
	int RightHand = MyEquipment->GetIdBySlot(7);
	int LeftHand = MyEquipment->GetIdBySlot (8);
	string RHEquipment, LHEquipment;
	Game *MyGame;
	MyGame = Game::GetGameInstance ();
	Items *MyItems;
	MyItems = MyGame->GetItems ();
	if (RightHand < 0)
		RHEquipment = "---";
	else
	{
		RHEquipment = MyItems->GetNameById (RightHand);
		if (MyItems->GetWeaponNeedsAmmo(RightHand) == 1)
		{
			int Quantity = MyItems->GetWeaponCurrentAmmoQuantity (RightHand);
			_itoa (Quantity, temp, 10);
			RHEquipment = RHEquipment+" ("+temp+")";
		}
		if (MyItems->GetWeaponNeedsEnergy(RightHand) == 1)
		{
			int AmmoID = MyItems->GetWeaponNextAmmo(RightHand);
			int MQuantity = MyItems->GetQuality(AmmoID);
			_itoa(MQuantity, temp, 10);
			RHEquipment = RHEquipment + " (" + temp + ")";
		}
	}
	if (LeftHand < 0)
		LHEquipment = "---";
	else
	{
		LHEquipment = MyItems->GetNameById (LeftHand);
		if (MyItems->GetWeaponNeedsAmmo(LeftHand) == 1)
		{
			int Quantity = MyItems->GetWeaponCurrentAmmoQuantity (LeftHand);
			_itoa (Quantity, temp, 10);
			LHEquipment = LHEquipment+" ("+temp+")";
		}
		if (MyItems->GetWeaponNeedsEnergy(LeftHand) == 1)
		{
			int AmmoID = MyItems->GetWeaponNextAmmo(LeftHand);
			int Quantity = MyItems->GetQuality(AmmoID);
			_itoa(Quantity, temp, 10);
			LHEquipment = LHEquipment + " (" + temp + ")";
		}

	}
	
	terminal_print (44,10, L"ПР:");
	terminal_print_ext (49,10,30,2,TK_ALIGN_LEFT, RHEquipment.c_str());
	terminal_print (44,12, L"ЛР:");
	terminal_print_ext (49,12,30,2,TK_ALIGN_LEFT, LHEquipment.c_str());
	terminal_print (44,19, L"Время:");
	_itoa (MyGame->GetMoves(), temp, 10);
	terminal_print (51, 19, temp);
	delete [] temp;
	return;

}

void Interface::PrintInventory (Gamer *MyGamer)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance ();
	Items *MyItems;
	MyItems = MyGame->GetItems ();
	terminal_print (44,27, L"Инвентарь:");
	Inventory *MyInventory;
	MyInventory = MyGamer->GetInventory();
	terminal_color (0x5fffffff);
	for (int x = 0; x<5; x++)
		for (int y = 0; y <10; y++)
		{
			terminal_put (44+x*6,28+y, 0x0181);
		}
	int InventorySize = MyInventory->GetNumOfSlots();
	if (InventorySize == 0 )
		return;
	char *temp = new char[3];
	
	for (int x = 0; x<5; x++)
	{
		for (int y = 0;y<10; y++)
		{
			int Num = y+x*10;
			if (Num >= InventorySize)
				break;
			int ID = MyInventory->GetIdByNum (Num);
			int CharCode = MyItems->GetCharCode (ID);
			int Stackable = MyItems->GetStackable (ID);
			int Quantity = MyInventory->GetQuantityByNum (Num);
			int Color = MyItems->GetColorVisible (ID);
			terminal_color (Color);
			terminal_put (44+x*6,28+y, CharCode);
			terminal_color (0x7fffffff);
			if (Stackable == 0)
				terminal_print (44+x*6+1,28+y, "----");
			else if (Stackable != 0)
			{
				_itoa (Quantity, temp,10);
				terminal_print (44+x*6+2,28+y, temp);
			}

		
		}
	}
}

string Interface::GetInputString ()
{
	string MyString;
	terminal_put (1,36,'>');
	terminal_refresh();
	while (1)
	{
		char temp;
		int KeyCode = terminal_read();
		if (KeyCode >=4 && KeyCode <= 29)
		{
			temp = KeyCode+61;
			MyString = MyString+temp;
		}
		if (KeyCode >= 30 && KeyCode <= 38)
		{
			temp = KeyCode+19;
			MyString += temp;
		}
		if (KeyCode == 39 || KeyCode == 98)
		{
			MyString += '0';
		}
	
		if (KeyCode >=89 && KeyCode <= 97)
		{
			temp = KeyCode-40;
			MyString += temp;
		}

		if (KeyCode == TK_MINUS && terminal_check(TK_SHIFT))
		{
			MyString+='_';
		}
		if (KeyCode == TK_BACKSPACE && MyString.size()>0)
		{
			MyString.pop_back();
		}
		if (KeyCode == TK_ESCAPE)
		{
			terminal_clear_area (1,36,40,1);
			MyString.clear();
			return MyString;
		}
		if (KeyCode == TK_ENTER)
		{
			terminal_clear_area (1,36,40,1);
			return MyString;
		}
		terminal_clear_area (2,36,40,1);
		terminal_print_ext(2,36,40,1, TK_ALIGN_DEFAULT, MyString.c_str());
		terminal_refresh();
	}
}

int Interface::GetInputNumber()
{
	string MyString;
	terminal_put (1,36,'>');
	terminal_refresh();
	while (1)
	{
		char temp;
		int KeyCode = terminal_read();
		
		if (KeyCode >= 30 && KeyCode <= 38)
		{
			temp = KeyCode+19;
			MyString += temp;
		}
		if (KeyCode == 39 || KeyCode == 98)
		{
			MyString += '0';
		}

		if (KeyCode >=89 && KeyCode <= 97)
		{
			temp = KeyCode-40;
			MyString += temp;
		}

		
		if (KeyCode == TK_BACKSPACE && MyString.size()>0)
		{
			MyString.pop_back();
		}
		if (KeyCode == TK_ESCAPE)
		{
			terminal_clear_area (1,36,40,1);
			MyString.clear();
			return 0;
		}
		if (KeyCode == TK_ENTER)
		{
			terminal_clear_area (1,36,40,1);
			return atoi (MyString.c_str());
		}
		terminal_clear_area (2,36,40,1);
		terminal_print_ext(2,36,40,1, TK_ALIGN_DEFAULT, MyString.c_str());
		terminal_refresh();
	}
}

int Interface::GetInputKey ()
{
	int a = terminal_read();
	return a;
}