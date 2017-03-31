#include "StdAfx.h"
#include "Gamer.h"
#include "Game.h"
#include "LuaAdapter.h"


Gamer::Gamer(void)
{
	MyInventory = new Inventory;
}

Gamer::Gamer (level *LevelPtr)
{
	MyInventory = new Inventory;
	MyEquipment = new Equipment;
	 MyLevel= LevelPtr;
}

Gamer::~Gamer(void)
{
	delete MyInventory;
	delete MyEquipment;
}

int Gamer::GetCoordX() const
{
	return CoordX;
}
void Gamer::SetCoordX (int a)
{
	CoordX = a;
	return;
}
int Gamer::GetCoordY() const

{
	return CoordY;
}
void Gamer::SetCoordY (int a)
{
	CoordY = a;
	return;
}
int Gamer::GetHP () const
{
	return HP;
}
void Gamer::SetHP (int a)
{
	HP = a;
}
int Gamer::GetMaxHP () const
{
	return MaxHP;
}
void Gamer::SetMaxHP (int a)
{
	MaxHP = a;
}
int Gamer::GetEnergy () const 
{
	return Energy;
}
void Gamer::SetEnergy (int a)
{
	Energy = a;
	return;
}
int Gamer::GetRangeOfSight () const
{
	return RangeOfSight;
}

void Gamer::SetRangeOfSight (int a)
{
	RangeOfSight = a;
	return;
}


int Gamer::GetMaxEnergy () const
{
	return MaxEnergy;
}
void Gamer::SetMaxEnergy (int a)
{
	MaxEnergy = a;
	return;
}
int Gamer::GetStr () const
{
	return Str;
}
void Gamer::SetStr (int a)
{
	Str = a;
	return;
}
int Gamer::GetDex () const
{
	return Dex;
}
void Gamer::SetDex (int a)
{
	Dex = a;
	return;
}
int Gamer::GetDefense () const
{
	return Defense;
}
void Gamer::SetDefense (int a)
{
	Defense = a;
	return;
}
int Gamer::GetRegenHP () const
{
	return RegenHP;
}
void Gamer::SetRegenHP (int a)
{
	RegenHP = a;
	return;
}
int Gamer::GetRegenEnergy () const
{
	return RegenEnergy;
}
void Gamer::SetRegenEnergy (int a)
{
	RegenEnergy = a;
	return;
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
	MyLevel->SetPassable (CoordX, CoordY, 0);
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

	if (Direction ==TK_I)
	{
		MyInventory->PrintInventory();
		return;
	}

	if (Direction == TK_D)
	{
		MyInventory->DropItem ();
		return;
	}

	GamerMoveLua (Direction);

	/*if (Direction == TK_UP || Direction == TK_KP_8)
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
	}*/
	MyLevel->FovProcess (CoordX, CoordY, 7);
	return;
}

void Gamer::GamerMoveLua (int KeyCode)
{
	using namespace luabridge;

	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\GamerMove.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef GamerMove = getGlobal(L, "GamerMove");
	  //
	try {
            GamerMove (Luaad, KeyCode);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }


}

void Gamer::GamerPrint ()
{
	int linear;
	terminal_layer (20);
	terminal_put (CoordX, CoordY, 64);
	terminal_layer (0);
	return;
}
