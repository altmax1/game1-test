#include "StdAfx.h"
#include "Inventory.h"
#include "Game.h"


Inventory::Inventory(void)
{
}


Inventory::~Inventory(void)
{
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
