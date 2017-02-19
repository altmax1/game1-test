#include "StdAfx.h"
#include "cell.h"


X_cell::X_cell(void)
{
}


X_cell::~X_cell(void)
{
}

void X_cell::AddItems (int ID)
{
	items.push_back(ID);
	return;
}

int X_cell::GetItemsID()
{
	list<int>::iterator p;
	p = items.begin();
	return *p;

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
