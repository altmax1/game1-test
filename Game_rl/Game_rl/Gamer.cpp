#include "StdAfx.h"
#include "Gamer.h"


Gamer::Gamer(void)
{
	MyInventory = new Inventory;
}

Gamer::Gamer (level *LevelPtr)
{
	MyInventory = new Inventory;
	 MyLevel= LevelPtr;
}

Gamer::~Gamer(void)
{
	delete MyInventory;
}

int Gamer::GetCoordX()
{
	return CoordX;
}
int Gamer::GetCoordY()

{
	return CoordY;
}

void Gamer::GamerPlacing()
{
	int x, y, linear;
	char type;
	do
	{
		x = rand () % (MyLevel->GetLevelWidth());
		y = rand () % (MyLevel->GetLevelHeight());
		linear = MyLevel->DecartToLinear(x,y);
		type = MyLevel->cells[linear].GetBaseType();

	} while (type!= 46);

	CoordX = x;
	CoordY = y;
	MyLevel->FovProcess (CoordX, CoordY, 7);
	return;

}

void Gamer::Move (int Direction)
{
	int NextX, NextY;
	int linear;
	NextX = CoordX;
	NextY = CoordY;
	char NextCellType;
	if (Direction == TK_T)
	{
		MyInventory->PutItemInInventory();
		return;
	}
	if (Direction == TK_UP || Direction == TK_KP_8)
		NextY -=1;
	if (Direction == TK_DOWN || Direction == TK_KP_2)
		NextY += 1;
	if (Direction == TK_LEFT || Direction == TK_KP_4)
		NextX -= 1;
	if (Direction == TK_RIGHT || Direction == TK_KP_6)
		NextX +=1;
	if (Direction == TK_KP_7)
		{NextY -=1; NextX-=1;}
	if (Direction == TK_KP_9)
		{NextY -= 1; NextX +=1;}
	if (Direction == TK_KP_3)
		{NextX += 1; NextY +=1;}
	if (Direction == TK_KP_1)
		{NextX -=1; NextY +=1;}	
	if ( NextX>=0 && NextX < (MyLevel->GetLevelWidth()) && NextY >=0 && NextY < (MyLevel->GetLevelHeight()))
	{
		linear = MyLevel->DecartToLinear (NextX, NextY);
		NextCellType = MyLevel->cells[linear].GetBaseType();
		if (NextCellType == 46)
		{	
			CoordX = NextX;
			CoordY = NextY;
			MyLevel->FovProcess (CoordX, CoordY, 7);
		}
	}

	return;
}

void Gamer::GamerPrint ()
{
	int linear;
	terminal_layer (20);
	terminal_put (CoordX, CoordY, 64);
	terminal_layer (0);
	return;
}
