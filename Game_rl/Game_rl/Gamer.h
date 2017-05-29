#pragma once
#include "level.h"
#include "Inventory.h"
#include "Equipment.h"

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
	int Defense;  // ���������� ������
	int Defense2; // ���������� ������
	int Defense3; // ������ �� ����
	int Defense4; // ������ �� ���, ������. ������, �� �������
	int Defense5; // ������ �� ������
	int RegenHP;
	int RegenEnergy;
	level *MyLevel;
	Inventory *MyInventory;
	Equipment *MyEquipment;
public:
	Gamer(void);
	Gamer (level *LevelPtr);
	~Gamer(void);
	void Move(int Direction);
	void GamerMoveLua (int KeyCode);
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
	int GetDefense2 () const;
	void SetDefense2 (int a);
	int GetDefense3 () const;
	void SetDefense3 (int a);
	int GetDefense4 () const;
	void SetDefense4 (int a);
	int GetDefense5 () const;
	void SetDefense5 (int a);
	int GetRegenHP () const;
	void SetRegenHP (int a);
	int GetRegenEnergy () const;
	void SetRegenEnergy (int a);
	void GamerPlacing ();
	Inventory* GetInventory ();
	Equipment* GetEquipment ();
	int GetDefenseFromEquipment (int NumOfSlot);
	int GetDefense2FromEquipment (int NumOfSlot);
	int GetDefense3FromEquipment (int NumOfSlot);
	int GetDefense4FromEquipment (int NumOfSlot);
	int GetDefense5FromEquipment (int NumOfSlot);
	
};

