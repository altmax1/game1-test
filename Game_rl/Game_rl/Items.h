#pragma once
using namespace std;

struct Weapon
{
	int ID;
	string Name;
	string RName;
	int Type; // 0-рубящее, 1 - клинковое длинное, 2 - к. короткое, 3 - дробящее
	int Weight;
	int MaxDamage;
	int MinDamage;
	bool Stackable;
	//int Range;
	//bool Distant;
	//int BlastRadius; //радиус поражения
	//bool NeedsAmmo;
	//int AmmoID;
	//int Accuracy; //кучность
};

class Items
{
private:
	vector <Weapon> Weapons;
public:
	Items(void);
	~Items(void);
	void GetWeaponsFromFile ();
	void InsertWeaponsInStorage (vector <map<string,string>> Temp);
	int QuantityWeaponItems ();
	int GetTypeOfWeapon ( int ID);
	bool GetStackable (int ID);
	string GetNameOfWeapon (int ID);
};

