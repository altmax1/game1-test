#pragma once
using namespace std;

struct Item{
	int ID;
	int Weight;
	bool Unique;
	string Name;
	string RName;
	bool Stackable;
	int Type;
};

struct Weapon: public Item
{
	int MaxDamage;
	int MinDamage;
	bool NeedsAmmo; //нужны ли патроны
	bool IsAmmo; //является ли зарядом/патроном
	int Caliber; //калибр
	int AmmoQuantity; // max количество патронов в обойме
	vector <int> Ammo; //патроны здесь - пихаем их ID
	int Quality; //качество - износ мб, если батарея, то заряд.
	bool Destroyed; //если разрушено оружие, ставим 1. у not unique не учитывать.
	int Range;  // дистанция поражения (стрельбы)
	int BlastRadius; //радиус поражения
};

struct Armour
{
	int ID;
	string Name;
	string RName;
	int Type; // слоты занимаемые, 1 - голова, 2 - перч, 3 - тело, 4 - руки
	int Type2; // доп слоты если большое
	int Weight;
	int Defense; //физика
	int Defense2; //ментальная
	int Defense3; //огонь
	int Defense4; //биологич, яд, кислота
	int Defense5; //холод
	int TypeOfDefense2;
	bool Stackable;

};

class Items
{
private:
	//vector <Weapon> Weapons; //удалить после рефакторинга
	vector <Armour> Armours; // и это тоже удалить
	vector <Weapon> UniqueWeapon;
	vector <Weapon> CommonWeapon;
	vector <Weapon> WeaponFromLevel;
public:
	Items(void);
	~Items(void);
	void GetUniqueWeaponsFromFile ();
	void GetCommonWeaponsFromFile ();
	void InsertUniqueWeaponsInStorage (vector <map<string,string>> Temp);
	void InsertCommonWeaponsInStorage (vector <map<string,string>> Temp);
	void GetArmoursFromFile ();
	void InsertArmoursInStorage ( vector <map <string, string>> Temp);
	int QuantityUniqueWeapon();
	int QuantityCommonWeapon ();
	int GetIdForCreation (int Id);
	int GetTypeOfWeapon (int ID);
	int GetTypeOfArmour (int ID);
	int GetType2OfArmour (int ID);
	int GetDefenseOfArmour (int ID);
	int GetDefense2OfArmour (int ID);
	int GetDefense3OfArmour (int ID);
	int GetDefense4OfArmour (int ID);
	int GetDefense5OfArmour (int ID);
	int GetTypeOfDef2Armour (int ID);
	bool GetStackable (int ID);
	string GetNameOfWeapon (int ID);
	string GetNameOfArmour (int ID);
	string GetNameById (int ID);
	int GetTypeById (int ID);
	int GetType2ById (int ID);
	int GetDefenseById (int ID);
	int GetDefense2ById (int ID);
	int GetDefense3ById (int ID);
	int GetDefense4ById (int ID);
	int GetDefense5ById (int ID);
	int GetTypeOfDefense2 (int ID);
	int GetGlobalType (int ID);
};

