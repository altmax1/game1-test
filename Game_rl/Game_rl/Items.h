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

struct Armour
{
	int ID;
	string Name;
	string RName;
	int Type; // слоты занимаемые, 1 - голова, 2 - перч, 3 - тело, 4 - руки
	int Type2; // доп слоты если большое
	int Weight;
	int Defense;
	int Defense2;
	int TypeOfDefense2;
	bool Stackable;

};

class Items
{
private:
	vector <Weapon> Weapons;
	vector <Armour> Armours;
public:
	Items(void);
	~Items(void);
	void GetWeaponsFromFile ();
	void InsertWeaponsInStorage (vector <map<string,string>> Temp);
	void GetArmoursFromFile ();
	void InsertArmoursInStorage ( vector <map <string, string>> Temp);
	int QuantityWeaponItems ();
	int GetTypeOfWeapon (int ID);
	int GetTypeOfArmour (int ID);
	int GetType2OfArmour (int ID);
	int GetDefenseOfArmour (int ID);
	int GetDefense2OfArmour (int ID);
	int GetTypeOfDef2Armour (int ID);
	bool GetStackable (int ID);
	string GetNameOfWeapon (int ID);
	string GetNameOfArmour (int ID);
	string GetNameById (int ID);
	int GetTypeById (int ID);
	int GetType2ById (int ID);
	int GetDefenseById (int ID);
	int GetDefense2ById (int ID);
	int GetTypeOfDefense2 (int ID);
};

