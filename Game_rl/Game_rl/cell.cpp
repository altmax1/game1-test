#include "StdAfx.h"
#include "cell.h"




X_cell::X_cell(void)
{
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

int X_cell::GetItemsID()
{
	list<CellItems>::iterator p;
	p = items.begin();
	return p->ID ;
}

bool X_cell::GetItemsStackable ()
{
	list<CellItems>::iterator p;
	p = items.begin();
	return p->stackable;
}

int X_cell::GetNumsInStack ()
{
	list<CellItems>::iterator p;
	p = items.begin();
	return p->quantity;

}

void X_cell::RemoveItem ()
{
	int a;
	if (items.size () >0)
		items.pop_front();
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
