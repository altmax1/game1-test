#include "StdAfx.h"
#include "Gamer.h"
#include "Game.h"
#include "LuaAdapter.h"


Gamer::Gamer(void)
{
	MyInventory = new Inventory;
	//L = luaL_newstate();
	//luaL_openlibs(L);
	
}

Gamer::Gamer (level *LevelPtr)
{
	MyInventory = new Inventory;
	MyEquipment = new Equipment;
	 MyLevel= LevelPtr;
	 Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyItems = MyGame->GetItems();
	for (int i = 0; i <= 9; i++)
	{
		Defense[i] = 0;
		BaseDefense[i] = 0;
			
	}
	
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
	return Defense[0];
}
void Gamer::SetDefense (int a)
{
	Defense[0] = a;
	return;
}

int Gamer::GetDefenseAdvansed(int Num) const
{
	if (Num >=1 && Num <=10 ) 
		return Defense[Num-1];
	else
		return 0;
}

void Gamer::SetDefenseAdvansed(int Num, int Def)
{
	if (Num >= 1 && Num <= 10)
		Defense[Num - 1] = Def;
	return;
}

int Gamer::GetBaseDefenseAdvansed(int Num) const
{
	if (Num >=1 && Num <= 10)
		return BaseDefense[Num-1];
	else 
		return 0;
}

void Gamer::SetBaseDefenseAdvansed(int Num, int Def)
{
	if (Num >= 1 && Num <= 10)
		BaseDefense[Num - 1] = Def;
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
	Game *MyGame;
	MyGame = Game::GetGameInstance();

	int NextX, NextY;
	int linear;
	NextX = CoordX;
	NextY = CoordY;
	char NextCellType;
	if (Direction == TK_T)
	{
		MyInventory->PutItemInInventory();
		MyGame->SetPlayerMoved();
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
		MyGame->SetPlayerMoved();
		return;
	}

	if (Direction == TK_E)
	{
		MyEquipment->SelectEquipment();
		return;
	}

	if (Direction == TK_R)
		if (terminal_check(TK_SHIFT))
		{
			UnloadWeapon();
			MyGame->SetPlayerMoved();
		}
		else
		{
			ReloadWeapon();
			MyGame->SetPlayerMoved();
		}
	if (Direction == TK_F)
	{
		GamerDistantAttackLua();
		MyGame->SetPlayerMoved();
	}
	if (Direction == TK_EQUALS && terminal_check(TK_SHIFT))
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		MyGame->ChangeGameMode();
	}
	if (Direction == TK_S && terminal_check(TK_SHIFT))
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		MyGame->SaveGame();
	}
	if (Direction == TK_PERIOD && terminal_check(TK_SHIFT))
	{
		if (MyLevel->GetTile(CoordX, CoordY) == 1000)
		{
			MoveToOtherLevelLua();
		}
	}
	if (Direction == TK_GRAVE && MyGame->GetDeveloperMode() ==1)
	{
		GamerMakeCheatsLua ();
	}

	if (Direction == TK_A)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Log *MyLog;
		MyLog = MyGame->GetLog();
		MyLog->PrintLog();
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
	Game *MyGame;
	level *MyLevel;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	lua_State *L = MyGame->GetLuaState();
	LuaAdapter *Luaad = MyGame->GetLuaadapter();
	luaL_dofile(L, ".\\Files\\lua\\GamerMove.lua");
	//lua_pcall(L, 0, 0, 0);
    LuaRef GamerMove = getGlobal(L, "GamerMove");
	  //
	try {
            GamerMove (*Luaad, KeyCode);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
		
}

void Gamer::GamerDistantAttackLua ()
{
	using namespace luabridge;

	Game *MyGame;
	MyGame = Game::GetGameInstance();
	lua_State *L = MyGame->GetLuaState();
	LuaAdapter *Luaad = MyGame->GetLuaadapter();
	luaL_dofile(L, ".\\Files\\lua\\GamerDistAttack.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef GamerDistAttack = getGlobal(L, "GamerDistAttack");
	  //
	try {
            GamerDistAttack (*Luaad);
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

int Gamer::GetDefenseFromEquipmentAdvansed (int NumOfSlot, int NumOfDefense)
{
	return MyEquipment->GetDefBySlotAdvansed (NumOfSlot, NumOfDefense);
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
	if (MyItems->GetWeaponNeedsAmmo(Id) == 0 && MyItems->GetWeaponNeedsEnergy(Id) == 0)
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

void Gamer::UnloadWeapon ()
{
	int Id = MyEquipment->GetIdBySlot (7);
	if (Id<0)
		return;
	if (MyItems->GetGlobalType(Id) !=0)
		return;
	if (MyItems->GetWeaponNeedsAmmo(Id) == 0 && MyItems->GetWeaponNeedsEnergy(Id) == 0)
		return;
	int CurrentAmmo = MyItems->GetWeaponCurrentAmmoQuantity(Id);
	for (int i = CurrentAmmo; i>0; i--)
	{
		int NextAmmoId = MyItems->GetWeaponNextAmmo(Id);
		int Stackable = MyItems->GetStackable(NextAmmoId);
		MyInventory->PutItemInVector (NextAmmoId, Stackable, 1);
		MyItems->UnloadWeapon(Id);
	}
	return;
}

void Gamer::LevelUpdate()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
}

void Gamer::SaveGamer()
{
	ofstream out(".\\Files\\Save\\gamer.sav", ios::binary | ios::out);
	out.write((char*)&CoordX, sizeof CoordX);
	out.write((char*)&CoordY, sizeof CoordY);
	out.write((char*)&HP, sizeof HP);
	out.write((char*)&MaxHP, sizeof MaxHP);
	out.write((char*)&Str, sizeof Str);
	out.write((char*)&Dex, sizeof Dex);
	out.write((char*)&Energy, sizeof Energy);
	out.write((char*)&RangeOfSight, sizeof RangeOfSight);
	out.write((char*)&MaxEnergy, sizeof MaxEnergy);
	out.write((char*)&MaxAttack, sizeof MaxAttack);
	out.write((char*)&MinAttack, sizeof MinAttack);
	out.write((char*)&Defense, (sizeof Defense[0]) * 10);
	out.write((char*)&BaseDefense, (sizeof BaseDefense[0]) * 10);
	out.write((char*)&RegenHP, sizeof RegenHP);
	out.write((char*)&RegenEnergy, sizeof RegenEnergy);
	MyInventory->SaveInventory();
	MyEquipment->SaveEquipment();


}

void Gamer::LoadGamer()
{
	ifstream in(".\\Files\\Save\\gamer.sav", ios::binary | ios::in);
	in.read((char*)&CoordX, sizeof CoordX);
	in.read((char*)&CoordY, sizeof CoordY);
	in.read((char*)&HP, sizeof HP);
	in.read((char*)&MaxHP, sizeof MaxHP);
	in.read((char*)&Str, sizeof Str);
	in.read((char*)&Dex, sizeof Dex);
	in.read((char*)&Energy, sizeof Energy);
	in.read((char*)&RangeOfSight, sizeof RangeOfSight);
	in.read((char*)&MaxEnergy, sizeof MaxEnergy);
	in.read((char*)&MaxAttack, sizeof MaxAttack);
	in.read((char*)&MinAttack, sizeof MinAttack);
	in.read((char*)&Defense, (sizeof Defense[0]) * 10);
	in.read((char*)&BaseDefense, (sizeof BaseDefense[0]) * 10);
	in.read((char*)&RegenHP, sizeof RegenHP);
	in.read((char*)&RegenEnergy, sizeof RegenEnergy);

	MyInventory->LoadInventory();
	MyEquipment->LoadEquipment();
}

void Gamer::GamerMakeCheatsLua ()
{
	using namespace luabridge;

	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\GamerMakeCheats.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef GamerMakeCheats = getGlobal(L, "GamerMakeCheats");
	  //
	try {
            GamerMakeCheats (Luaad);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
}

void Gamer::MoveToOtherLevelLua()
{
	using namespace luabridge;
	Game *MyGame;
	level *MyLevel;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	lua_State *L = MyGame->GetLuaState();
	LuaAdapter *Luaad = MyGame->GetLuaadapter();
	luaL_dofile(L, ".\\Files\\lua\\GamerMoveToLevel.lua");
	lua_pcall(L, 0, 0, 0);
	LuaRef GamerMoveToLevel = getGlobal(L, "GamerMoveToLevel");
	//
	try {
		GamerMoveToLevel(*Luaad, MyLevel);
	}
	catch (luabridge::LuaException const& e) {
		std::cout << "LuaException: " << e.what() << std::endl;
	}

}
