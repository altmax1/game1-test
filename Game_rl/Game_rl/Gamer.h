#pragma once
#include "level.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Items.h"
//#include "Game.h"

class Gamer
{
private:
	int CoordX;
	int CoordY;
	int HP;
	int MaxHP;
	int Str;
	int Dex;
	int Energy;
	int RangeOfSight;
	int MaxEnergy;
	int MaxAttack;
	int MinAttack;
	int Defense[10]; 
	int BaseDefense[10]{0,0,0,0,0,0,0,0,0,0};
	int RegenHP;
	int RegenEnergy;
	level *MyLevel;
	Inventory *MyInventory;
	Equipment *MyEquipment;
	Items *MyItems;
	//Game *MyGame;
public:
	Gamer(void);
	Gamer (level *LevelPtr);
	~Gamer(void);
	void Move(int Direction);
	void GamerMoveLua (int KeyCode);
	void GamerDistantAttackLua ();
	void GamerMakeCheatsLua();
	void GamerPrint ();
	int GetCoordX () const;
	int GetCoordY () const;
	void SetCoordX (int a);
	void SetCoordY (int a);
	int GetHP () const;
	void SetHP (int a);
	int GetMaxHP () const;
	void SetMaxHP (int a);
	int GetEnergy () const;
	void SetEnergy (int a);
	int GetRangeOfSight () const;
	void SetRangeOfSight (int a);
	int GetMaxEnergy () const;
	void SetMaxEnergy (int a);
	int GetStr () const;
	void SetStr (int a);
	int GetDex () const;
	void SetDex (int a);
	int GetDefense () const;
	void SetDefense (int a);
	int GetDefenseAdvansed(int Num) const;
	void SetDefenseAdvansed(int Num, int Def);
	int GetBaseDefenseAdvansed(int Num) const;
	void SetBaseDefenseAdvansed(int Num, int Def);
	int GetRegenHP () const;
	void SetRegenHP (int a);
	int GetRegenEnergy () const;
	void SetRegenEnergy (int a);
	void GamerPlacing ();
	Inventory* GetInventory ();
	Equipment* GetEquipment ();
	int GetDefenseFromEquipment (int NumOfSlot);
	int GetDefenseFromEquipmentAdvansed (int NumOfSlot, int NumOfDefense);
	int GetItemIdBySlot (int Slot);
	void ReloadWeapon ();
	void UnloadWeapon ();
};

