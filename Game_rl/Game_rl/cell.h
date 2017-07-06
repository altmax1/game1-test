#pragma once
using namespace std;
struct CellItems
{
	int ID;
	int quantity;
	bool stackable;

};

struct Effect
{
	int Type;
	int Power;
	int Time;
};

class X_cell
{
private:
	int tile;
	char BaseType;
	unsigned char visible:1;
	unsigned char opaque:1;
	unsigned char visited:1;
	unsigned char passable:1;
	unsigned char empty_cell:1;// 1 если тайл пустой и без эффектов
	list <CellItems> items;
	vector <Effect> Effects;
	int creature;
	int ConnectorNum;

public:
	X_cell(void);
	~X_cell(void);
	void SetBaseType ( char p);
	char GetBaseType ();
	void AddItems (int ID, bool Stackable, int Quantity);
	int GetItemsQuantity ();
	int GetItemsID (int stacknum);
	bool GetItemsStackable(int stacknum);
	int GetNumsInStack(int stacknum);
	void RemoveItem (int stacknum, int quantity);
	bool IsEmpty ();
	int FindItemByID (int ID);
	void AddItemsInSlot (int ID, int Quantity, int SlotNumber);
	int SelectItem ();
	void PrintItems ();
	void PrintBorder (int state);
	int SelectQuantity (int num);
	int GetCreature ();
	void SetCreature (int a);
	void RemoveCreature ();
	int GetOpaque ();
	void SetOpaque (int a);
	int GetPassable ();
	void SetPassable (int a);
	void AddEffect (int Type, int Power, int Time);
	int GetNumOfEffects ();
	void CheckEffects ();
	int GetEffectTypeByNum (int Num);
	int GetEffectPowerByNum (int Num);
	int GetEffectTimeByNum (int Num);
	void EffectTimeDec ();
	int GetConnectorNum();
	void SetConnectorNum(int Num);
	int GetTile();
	void SetTile(int Tile);
};

