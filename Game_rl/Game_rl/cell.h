#pragma once
using namespace std;
struct CellItems
{
	int ID;
	int quantity;
	bool stackable;

};

class X_cell
{
private:
	int tile;
	char BaseType;
	char visible:1;
	char opaque:1;
	char visited:1;
	char passable:1;
	char empty_cell:1;// 1 если тайл пустой и без эффектов
	list <CellItems> items;
	int creature;

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
};

