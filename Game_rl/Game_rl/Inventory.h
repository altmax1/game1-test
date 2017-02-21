#pragma once
using namespace std;

struct InventoryCell
{
int ID;
int Quantity;
bool stackable;
};

class Inventory
{
private:
vector <InventoryCell> MyInventory;
int MaxCellCount;
int CurrentCellCount;

public:
	void PutItemInInventory ();
	void PutItemInVector (int Id, bool Stackable, int nums);
	void PrintInventory ();
	void PrintItems ();
	bool ItemExist (int ID);
	int FindItemByID (int ID);
	Inventory(void);
	~Inventory(void);
};

