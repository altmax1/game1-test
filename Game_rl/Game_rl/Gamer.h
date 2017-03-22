#pragma once
#include "level.h"
#include "Inventory.h"

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
	int MaxEnergy;
	level *MyLevel;
	Inventory *MyInventory;
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
	int GetMaxEnergy () const;
	void SetMaxEnergy (int a);
	int GetStr () const;
	void SetStr (int a);
	int GetDex () const;
	void SetDex (int a);
	void GamerPlacing ();

	
};

