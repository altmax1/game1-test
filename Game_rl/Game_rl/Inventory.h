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
	void PutItemInVector (int Id);
	Inventory(void);
	~Inventory(void);
};

