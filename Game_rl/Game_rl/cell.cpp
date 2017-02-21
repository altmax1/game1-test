#include "StdAfx.h"
#include "cell.h"




X_cell::X_cell(void)
{
}


X_cell::~X_cell(void)
{
}

void X_cell::AddItems (int ID, bool Stackable)
{
	CellItems temp;
	temp.ID = ID;
	temp.quantity = 1;
	temp.stackable = Stackable;
	items.push_back(temp);
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
