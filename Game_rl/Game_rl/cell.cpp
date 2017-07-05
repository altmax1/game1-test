#include "StdAfx.h"
#include "cell.h"
#include "Game.h"




X_cell::X_cell(void)
{
	creature = -1;
	ConnectorNum = -1;
}


X_cell::~X_cell(void)
{
	
}

bool X_cell::IsEmpty()
{
	int size;
	size = items.size();
	if (size = 0)
		return true;
	return false;
}

int X_cell::FindItemByID (int ID)
{
	list <CellItems>::iterator p;
	p= items.begin();
	int MyCounter=0;
	while (p!=items.end())
	{
		MyCounter++;
		if (p->ID == ID)
			return MyCounter;
		p++;
	}
	return 0;

}


void X_cell::AddItems (int ID, bool Stackable, int Quantity)
{
	CellItems temp;
	temp.ID = ID;
	temp.quantity = Quantity;
	temp.stackable = Stackable;
	items.push_back(temp);
	return;
}

void X_cell::AddItemsInSlot (int ID,  int Quantity, int SlotNumber)
{
	list<CellItems>::iterator p;
	p = items.begin();
	for (int i=1; i <SlotNumber; i++)
		p++;
	p->quantity += Quantity;
	return;

}

int X_cell::GetItemsID(int stacknum)
{
	list<CellItems>::iterator p;
	p = items.begin();
	for (int i = 0; i< stacknum; i++)
		p++;
	return p->ID ;
}

bool X_cell::GetItemsStackable (int stacknum)
{
	list<CellItems>::iterator p;
	p = items.begin();
	for (int i = 0; i< stacknum; i++)
		p++;
	return p->stackable;
}

int X_cell::GetNumsInStack (int stacknum)
{
	list<CellItems>::iterator p;
	p = items.begin();
	for (int i = 0; i< stacknum; i++)
		p++;
	return p->quantity;

}

void X_cell::RemoveItem (int stacknum, int quantity)
{
	
	if (items.size () >0)
	{
	list<CellItems>::iterator p;
	p = items.begin();
	for (int i = 0; i< stacknum; i++)
		p++;
	if (quantity >= p->quantity)
	{
		items.erase (p);
		return;
	}
	p->quantity -= quantity;
	}
	return;
	
}

int X_cell::GetItemsQuantity ()
{
	return items.size();
}

void X_cell::SetBaseType (char p)
{
	BaseType = p;
}

char X_cell::GetBaseType ()
{
	return BaseType;
}
void X_cell::PrintItems ()
{
	if (items.size() == 0)
		return;
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	int startX = 10, startY = 10;
	int iter = 1;
	list <CellItems>::iterator p;
	p = items.begin();
	while (p!= items.end())
	{	
		char *temp, *tempnums;
		temp = new char [4];
		tempnums = new char [4];
		_itoa (iter, temp, 10);
		int nums = p->quantity;
		_itoa (nums, tempnums, 10);
		string stemp;
		stemp = MyItems->GetNameById (p->ID);
		terminal_print (startX, startY, temp);
		terminal_print (startX+3, startY, stemp.c_str());
		terminal_print (startX+20, startY, tempnums);
		p++;
		startY++; startY++;
		iter++;
		delete [] temp ;
	
	}
	return;
}

void X_cell::PrintBorder (int state)
{
	terminal_put (8, 10+state*2, 42);
	return;
}


int X_cell::SelectItem ()
{
	int MenuSize = items.size();
	int state = 0;
	while (1)
	{
		terminal_clear();
		terminal_wprint (10, 7, L"Выберите позицию");
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

int X_cell::SelectQuantity (int num)
{
	list <CellItems>::iterator p;
	p = items.begin();
	for (int i = 0; i <num; i++)
		p++;
	
	int MaxQuantity = p->quantity;
	int TotalQuantity = MaxQuantity;
	while (1)
	{
		terminal_clear();
		terminal_wprint (10, 7, L"Выберите количество");
		terminal_wprint (10, 8, L"Используйте стрелки для изменения");
		terminal_wprint (10, 9, L"Enter для выбора, Escape - выход");
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

void X_cell::SetCreature (int a)
{
	creature = a;
	passable = 0;
	return;
	
}
void X_cell::RemoveCreature ()
{
	creature = -1;
	passable = 1;
	return;
}
int X_cell::GetCreature ()
{
	return creature;
}
int X_cell::GetOpaque ()
{
	return (int)opaque;
}
void X_cell::SetOpaque (int a)
{
	if (a==0)
		opaque = 0;
	if (a >0)
		opaque = 1;
	return;
}
int X_cell::GetPassable ()
{
	return passable;
}
void X_cell::SetPassable (int a)
{
	if (a==0)
		passable = 0;
	if (a>0)
		passable = 1;
	return;
}

void X_cell::AddEffect (int Type, int Power, int Time)
{
	Effect Temp;
	Temp.Type = Type;
	Temp.Power = Power;
	Temp.Time = Time;
	if (Effects.size() == 0)
	{
		Effects.push_back (Temp);
		return;
	}
	int TypeIsExist = -1;
	for (int i = 0; i < Effects.size(); i++) // проверяем, есть ли уже такие эффекты.
	{
		if (Effects[i].Type == Type)
			TypeIsExist = i;
	}
	if (TypeIsExist <0)
		Effects.push_back (Temp);
	if (TypeIsExist >=0  && Effects[TypeIsExist].Time > Temp.Time) 
	{
		if (Effects[TypeIsExist].Power >= Temp.Power)
			return;
		if (Effects[TypeIsExist].Power < Temp.Power)
			Effects[TypeIsExist].Power = Temp.Power;
		return;
	}
		
	if (TypeIsExist >=0  && Effects[TypeIsExist].Time < Temp.Time) 
	{
		if (Effects[TypeIsExist].Power >= Temp.Power)
		{
			Effects[TypeIsExist].Time = Temp.Time;
		}
		if (Effects[TypeIsExist].Power < Temp.Power)
		{
			Effects[TypeIsExist].Time = Temp.Time;
			Effects[TypeIsExist].Power = Temp.Power;
		}
	}


}

int X_cell::GetNumOfEffects ()
{
	return Effects.size();
}

void X_cell::CheckEffects ()
{
	if ( Effects.size() == 0)
		return;
	vector<Effect>::iterator p;
	/*for ( p = Effects.begin(); p != Effects.end(); p++)
	{
		if (p->Time <= 0)
			Effects.erase (p);
	}*/

	for (int i = 0; i< Effects.size(); i++)
	{
		if (Effects[i].Time <= 0)
			Effects.erase (Effects.begin()+i);
	}
	return;
}

int X_cell::GetEffectTypeByNum (int Num)
{
	if (Num >= Effects.size())
		return Effects[Num-1].Type;
	return -1;
}

int X_cell::GetEffectPowerByNum (int Num)
{
	if (Num >= Effects.size())
		return Effects[Num-1].Power;
	return -1;
}

int X_cell::GetEffectTimeByNum (int Num)
{
	if (Num <= Effects.size() && Num > 0)
		return Effects[Num-1].Time;
	return -1;
}

void X_cell::EffectTimeDec ()
{
	for (int i = 0; i < Effects.size(); i++)
		Effects[i].Time--;
	return;
}

int X_cell::GetConnectorNum()
{
	return ConnectorNum;
}

void X_cell::SetConnectorNum(int Num)
{
	ConnectorNum = Num;
}
