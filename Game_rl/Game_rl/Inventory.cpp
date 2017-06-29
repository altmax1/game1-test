#include "StdAfx.h"
#include "Inventory.h"
#include "Game.h"


Inventory::Inventory(void)
{
}


Inventory::~Inventory(void)
{
}

bool Inventory::ItemExist (int ID)
{
	vector <InventoryCell>::iterator p;
	p = MyInventory.begin();
	while (p!=MyInventory.end())
	{
		if (p->ID == ID)
			return true;
		p++;
	}
	return false;
}

int Inventory::FindItemByID (int ID)
{
	int iter = 0;
	vector <InventoryCell>::iterator p;
	p = MyInventory.begin();
	while (p!=MyInventory.end())
	{
		if (p->ID == ID)
			return iter;
		iter++;
		p++;
	}

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
		char *temp, *tempnums;
		temp = new char [4];
		tempnums = new char [4];
		_itoa (iter, temp, 10);
		int nums = p->Quantity;
		_itoa (nums, tempnums, 10);
		string stemp;
		stemp = MyItems->GetNameById (p->ID);
		if (MyItems->GetGlobalType(p->ID) == 0) // ���� � ��������� - ������ ����������
			if (MyItems->GetWeaponNeedsAmmo(p->ID) == 1)
			{
				int NumAmmo = MyItems->GetWeaponCurrentAmmoQuantity (p->ID);
				char *temp3 = new char [4];
				_itoa (NumAmmo, temp3, 10);
				stemp = stemp +'('+temp3+')';
				delete [] temp3;
			}
		terminal_print (startX, startY, temp);
		terminal_print (startX+3, startY, stemp.c_str());
		terminal_print (startX+30, startY, tempnums);
		p++;
		startY++; startY++;
		iter++;
		delete [] temp ;
		delete [] tempnums;
	
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
		terminal_wprint (10, 7, L"� � � � � � � � �");
		PrintItems ();
		terminal_refresh();
		a = terminal_read();
		if (a==TK_ESCAPE)
		 return;
	}
}

void Inventory::PutItemInVector (int ID, bool Stackable, int nums)
{
	InventoryCell temp;
	if (Stackable)
	{
		if (ItemExist(ID))
		{
			MyInventory[FindItemByID (ID)].Quantity += nums;
			return;	
		}
		
	}
	temp.ID = ID;
	temp.Quantity = nums;
	temp.stackable = Stackable;
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
	int StackQuantity;
	StackQuantity = MyLevel->GetQuantityItemsOnCell(CoordX, CoordY);
	if (StackQuantity == 1)
	{	
		int ID = MyLevel->GetItemIDByCell(CoordX, CoordY,0);
		bool Stackable = MyLevel->GetStackableByCell (CoordX, CoordY,0);
		int Nums = MyLevel->GetNumsInStack (CoordX, CoordY,0);
		if (Nums>1)
			Nums = MyLevel->SelectQuantity (CoordX, CoordY, 0);
		PutItemInVector (ID, Stackable, Nums);
		MyLevel->RemoveItemFromCell(CoordX, CoordY,0,Nums);
			
	}
	if (StackQuantity >1)
	{
		int itemnum = MyLevel->SelectItem (CoordX, CoordY);
		if (itemnum == 1000000)
			return;
		int ItemQuantity = 1;
		if (MyLevel->GetNumsInStack (CoordX, CoordY,itemnum) >1)
			ItemQuantity = MyLevel->SelectQuantity (CoordX, CoordY, itemnum);
		if (ItemQuantity==0)
			return;
		int ID = MyLevel->GetItemIDByCell(CoordX, CoordY,itemnum);
		bool Stackable = MyLevel->GetStackableByCell (CoordX, CoordY,itemnum);
		PutItemInVector (ID, Stackable, ItemQuantity);
		MyLevel->RemoveItemFromCell(CoordX, CoordY,itemnum, ItemQuantity);
	}

	return;	
}

void Inventory::PrintBorder (int state)
{
	terminal_put (8, 10+state*2, 42);
	return;
}

int Inventory::SelectItem ()
{
	int MenuSize = MyInventory.size();
	int state = 0;
	while (1)
	{
		terminal_clear();
		terminal_wprint (10, 7, L"�������� �������");
		PrintItems ();
		PrintBorder (state);
		terminal_refresh();
		int a = terminal_read();
		if (a == TK_UP && state >0)
			state--;
		if (a == TK_DOWN && state < MenuSize-1)
			state++;
		if (a==TK_ENTER)
			return state;
		if (a==TK_ESCAPE)
			return 1000000;
	}
}

int Inventory::SelectQuantity (int num)
{
	int MaxQuantity = MyInventory[num].Quantity;
	int TotalQuantity = MaxQuantity;
	while (1)
	{
		terminal_clear();
		terminal_wprint (10, 7, L"�������� ����������");
		terminal_wprint (10, 8, L"����������� ������� ��� ���������");
		terminal_wprint (10, 9, L"Enter ��� ������, Escape - �����");
		char temp[10];
		_itoa ( TotalQuantity, temp, 10);
		terminal_print (15, 12, temp);
		terminal_refresh();
		int a = terminal_read ();
		if (a==TK_UP && TotalQuantity < MaxQuantity)
			TotalQuantity++;
		if (a==TK_DOWN && TotalQuantity >1)
			TotalQuantity--;
		if (a==TK_ENTER)
			return TotalQuantity;
		if (a==TK_ESCAPE)
			return 0;

	}

}

void  Inventory::RemoveItemFromVector (int num, int Quantity)
{
	if (Quantity == MyInventory[num].Quantity)
	{	
		vector <InventoryCell>::iterator p;
		p = MyInventory.begin ();
		p += num;
		MyInventory.erase (p);
		return;
		
	}

	if (Quantity < MyInventory[num].Quantity)
	{
		MyInventory[num].Quantity -= Quantity;
		return;
	}
}

void Inventory::DropItem ()
{
	int size;
	size = MyInventory.size();
	if (size==0)
		return;
	int ItemNum; int ItemQuantity;
	ItemNum = SelectItem ();
	if (ItemNum == 1000000)
		return;
	ItemQuantity = 1;
	if (MyInventory[ItemNum].Quantity >1)
		ItemQuantity = SelectQuantity (ItemNum);
	if (ItemQuantity==0)
		return;
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	level *MyLevel;
	MyLevel = MyGame->GetLevel();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	int CoordX, CoordY;
	CoordX = MyGamer->GetCoordX();
	CoordY = MyGamer->GetCoordY();
	bool Stackable = MyInventory[ItemNum].stackable;
	MyLevel->PutItemsOnCell (MyInventory[ItemNum].ID, ItemQuantity, MyInventory[ItemNum].stackable, CoordX, CoordY);
	RemoveItemFromVector (ItemNum, ItemQuantity);
	return;

}

void Inventory::FindItemsByType ( vector<int> &temp, int GlobalType, int Slot)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	vector <InventoryCell>::iterator p;
	p = MyInventory.begin();
	int IterC = 0;
	if (Slot>=1 && Slot <=6)
	{
	while (p!=MyInventory.end())
	{
		if ( (MyItems->GetGlobalType (p->ID) == GlobalType) && (MyItems->GetTypeById (p->ID)-1000000 == Slot))
			temp.push_back (IterC);
		
		p++;
		IterC++;
			
	}
	}
	if (Slot==7 || Slot==8)
	{
		while (p!=MyInventory.end())
	{
		if (( MyItems->GetGlobalType (p->ID)) == 0 && (MyItems->GetTypeById (p->ID)) >=0 && 
			(MyItems->GetTypeById (p->ID)-1000000 <100))
				temp.push_back (IterC);
		p++;
		IterC++;
		
	}
	}

	return;
}

int Inventory::GetNumOfSlots ()
{
	return MyInventory.size();
}

int Inventory::GetIdByNum (int Num)
{	
	if ( Num>=0 && Num < MyInventory.size ()) 
		return MyInventory[Num].ID;
	return -1;
}

int Inventory::GetQuantityByNum (int Num)
{
	if ( Num>=0 && Num < MyInventory.size ()) 
		return MyInventory[Num].Quantity;
	return -1;
}

void Inventory::FindItemsByCaliber (vector <int> &temp, int Caliber)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	vector <InventoryCell>::iterator p;
	p = MyInventory.begin();
	int IterC=0;
	while (p!=MyInventory.end())
	{
		if (MyItems->GetGlobalType (p->ID) == 0)
			if (MyItems->GetWeaponIsAmmo (p->ID) == 1)
				if (MyItems->GetWeaponCaliber(p->ID) == Caliber)
					temp.push_back (IterC);
		p++;
		IterC++;
	
	}
}

