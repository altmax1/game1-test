#include "StdAfx.h"
#include "Inventory.h"
#include "Game.h"


Inventory::Inventory(void)
{
}


Inventory::~Inventory(void)
{
}

void Inventory::PrintItems()
{	
	if (MyInventory.size() == 0)
		return;
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	int startX = 10, startY = 10;
	int iter = 1;
	vector <InventoryCell>::iterator p;
	p = MyInventory.begin();
	while (p!= MyInventory.end())
	{	
		char* temp;
		temp = new char [2];
		_itoa (iter, temp, 10);
		string stemp;
		stemp = MyItems->GetNameOfWeapon (p->ID);
		terminal_print (startX, startY, temp);
		terminal_print (startX+3, startY, stemp.c_str());
		p++;
		startY++; startY++;
		iter++;
		delete [] temp ;
	
	}
	return;
}
void Inventory::PrintInventory()
{
	terminal_clear();
	terminal_refresh();
	int a;
		while (1)
	{
		terminal_wprint (10, 7, L"Инвентарь");
		PrintItems ();
		terminal_refresh();
		a = terminal_read();
		if (a==TK_ESCAPE)
		 return;
	}
}

void Inventory::PutItemInVector (int ID)
{
	InventoryCell temp;
	temp.ID = ID;
	temp.Quantity = 1;
	temp.stackable = 0;
	MyInventory.push_back (temp);
	return;
}

void Inventory::PutItemInInventory ()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	level *MyLevel;
	MyLevel = MyGame->GetLevel();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	int CoordX, CoordY;
	CoordX = MyGamer->GetCoordX();
	CoordY = MyGamer->GetCoordY();
	int ItemsQuantity;
	ItemsQuantity = MyLevel->GetQuantityItemsOnCell(CoordX, CoordY);
	if (ItemsQuantity >0)
	{	
		int ID = MyLevel->GetItemIDByCell(CoordX, CoordY);
		PutItemInVector (ID);
		MyLevel->RemoveItemFromCell(CoordX, CoordY);
			
	}

	return;	


}
