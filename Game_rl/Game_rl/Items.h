#pragma once
using namespace std;

struct ColdWeapon
{
	int ID;
	string Name;
	string RName;
	int Type; // 0-рубящее, 1 - клинковое длинное, 2 - к. короткое, 3 - дробящее
	int Weight;
	int MaxDamage;
	int MinDamage;
};

class Items
{
private:
	vector <ColdWeapon> ColdWeapons;
public:
	Items(void);
	~Items(void);
	void GetWeaponsFromFile ();
	void InsertWeaponsInStorage (vector <map<string,string>> Temp);
	int QuantityColdWeaponItems ();
	int GetTypeOfWeapon ( int ID);
};

