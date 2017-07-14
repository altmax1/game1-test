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
	void PutItemInInventory (int x = -1, int y = -1);
	void PutItemInVector (int Id, bool Stackable, int nums);
	void PrintInventory ();
	void PrintItems ();
	bool ItemExist (int ID);
	int FindItemByID (int ID);
	void DropItem ();
	int SelectItem ();
	void PrintBorder (int state);
	int SelectQuantity (int num);
	void RemoveItemFromVector (int num, int Quantity);
	//int FindIdByNumber (int nubmer);
	Inventory(void);
	~Inventory(void);
	void FindItemsByType ( vector<int> &temp, int GlobalType, int Type);
	void FindItemsByCaliber (vector<int> &temp, int Caliber);
	int GetNumOfSlots ();
	int GetIdByNum (int Num);
	int GetQuantityByNum( int Num);
};

