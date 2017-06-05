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
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyItems = MyGame->GetItems();
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

int Gamer::GetDefense2 () const
{
	return Defense2;
}
void Gamer::SetDefense2 (int a)
{
	Defense2 = a;
	return;
}

int Gamer::GetDefense3 () const
{
	return Defense3;
}
void Gamer::SetDefense3 (int a)
{
	Defense3 = a;
	return;
}

int Gamer::GetDefense4 () const
{
	return Defense4;
}
void Gamer::SetDefense4 (int a)
{
	Defense4 = a;
	return;
}

int Gamer::GetDefense5 () const
{
	return Defense5;
}
void Gamer::SetDefense5 (int a)
{
	Defense5 = a;
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

	if (Direction == TK_E)
	{
		MyEquipment->SelectEquipment();
		return;
	}

	if (Direction == TK_R)
		ReloadWeapon();

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

Inventory* Gamer::GetInventory ()
{
	return MyInventory;
}

Equipment* Gamer::GetEquipment ()
{
	return MyEquipment;
}

int Gamer::GetDefenseFromEquipment (int NumOfSlot)
{
	return MyEquipment->GetDefBySlot (NumOfSlot);
}

int Gamer::GetDefense2FromEquipment (int NumOfSlot)
{
	return MyEquipment->GetDef2BySlot (NumOfSlot);
}

int Gamer::GetDefense3FromEquipment (int NumOfSlot)
{
	return MyEquipment->GetDef3BySlot (NumOfSlot);
}

int Gamer::GetDefense4FromEquipment (int NumOfSlot)
{
	return MyEquipment->GetDef4BySlot (NumOfSlot);
}

int Gamer::GetDefense5FromEquipment (int NumOfSlot)
{
	return MyEquipment->GetDef5BySlot (NumOfSlot);
}

int Gamer::GetItemIdBySlot (int Slot)
{
	return MyEquipment->GetIdBySlot (Slot);
}

void Gamer::ReloadWeapon ()
{
	int Id = MyEquipment->GetIdBySlot (7);
	if (Id<0)
		return;
	if (MyItems->GetGlobalType(Id) !=0)
		return;
	if (MyItems->GetWeaponNeedsAmmo(Id) == 0)
		return;
	int CurrentAmmo = MyItems->GetWeaponCurrentAmmoQuantity(Id);
	int AmmoQuantity = MyItems->GetWeaponAmmoQuantity(Id);
	int DeltaAmmo = AmmoQuantity-CurrentAmmo;
	if (CurrentAmmo >= AmmoQuantity)
		return;
	vector<int> temp;
	MyInventory->FindItemsByCaliber (temp, MyItems->GetWeaponCaliber (Id));
	if (temp.size() ==0)
		return;
	vector<int>::iterator p;
	p = temp.begin ();
	while (p!= temp.end())
	{
		int AmmoInventoryQuantity = MyInventory->GetQuantityByNum (*p);
		if (AmmoInventoryQuantity>= DeltaAmmo)
		{
			int AmmoId = MyInventory->GetIdByNum (*p);
			MyInventory->RemoveItemFromVector (*p, DeltaAmmo);
			MyItems->LoadWeapon (Id, AmmoId, DeltaAmmo);
			break;
		}

		if (AmmoInventoryQuantity<DeltaAmmo)
		{
			int AmmoId = MyInventory->GetIdByNum (*p);
			MyInventory->RemoveItemFromVector (*p, AmmoInventoryQuantity);
			MyItems->LoadWeapon (Id, AmmoId,AmmoInventoryQuantity);
		}
		p++;
	}
	return;
}