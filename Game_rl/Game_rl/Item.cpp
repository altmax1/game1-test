#include "StdAfx.h"
#include "Item.h"


Item::Item(void)
{
}


Item::~Item(void)
{
}

int Item::GetItemID ()
{
	return ID;
}

void Item::SetItemId (int Id)
{
	ID = Id;
	return;

}

int Item::GetWeight ()
{
	return Weight;
}

void Item::SetWeight (int W)
{
	Weight = W;
	return;
}

bool Item::GetUnique ()
{
	return Unique;
}

void Item::SetUnique (int a)
{
	if (a!=0)
		Unique = 1;
	else 
		Unique = 0;
}

string Item::GetName ()
{
	return Name;
}

void Item::SetName (string s)
{
	Name = s;
	return;
}

string Item::GetRName ()
{
	return RName;
}

void Item::SetRName (string s)
{
	RName = s;
	return;
}