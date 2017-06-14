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
	int Quality; //качество - износ мб, если батарея, то заряд.
	bool Destroyed; //если разрушено, ставим 1. у not unique не учитывать.
	int CharCode; //Символ для печати
	int ColorVisible;
	int ColorNotVisible;
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
	int Range;  // дистанция поражения (стрельбы)
	int BlastRadius; //радиус поражения
	int ShotsPerStep; //выстрелов в очереди
	int AfterEffectType; // тип последствий выстрела
	int AfterEffectTime; // время последствий
	int AfterEffectPower; // сила последствий
};

struct Armour: public Item
{
	//int Type -  слоты занимаемые, 1 - голова, 2 - перч, 3 - тело, 4 - руки
	int Type2; // доп слоты если большое
	int Defense; //физика
	int Defense2; //ментальная
	int Defense3; //огонь
	int Defense4; //биологич, яд, кислота
	int Defense5; //холод
	bool CanBuiltedIn; //можно ли встроить что-либо
	int NumOfBuiltedInSlots;
	vector <int> SlotForBuiltIn;
	int BuiltInType; // что встраивается
		

};

class Items
{
private:
	vector <Weapon> UniqueWeapon;
	vector <Weapon> CommonWeapon;
	vector <Weapon> WeaponFromLevel;
	vector <Armour> UniqueArmour;
	vector <Armour> CommonArmour;
	vector <Armour> ArmourFromLevel;
public:
	Items(void);
	~Items(void);
	void GetUniqueWeaponsFromFile ();
	void GetCommonWeaponsFromFile ();
	void InsertUniqueWeaponsInStorage (vector <map<string,string>> Temp);
	void InsertCommonWeaponsInStorage (vector <map<string,string>> Temp);
	void GetUniqueArmourFromFile ();
	void GetCommonArmourFromFile ();
	void InsertUniqueArmourInStorage (vector <map<string,string>> Temp);
	void InsertCommonArmourInStorage (vector <map<string,string>> Temp);
	int QuantityUniqueWeapon ();
	int QuantityCommonWeapon ();
	int GetIdForCreation (int Id);
	int GetType2OfArmour (int ID);
	bool GetStackable (int ID);
	string GetNameById (int ID);
	int GetTypeById (int ID);
	int GetType2ById (int ID);
	int GetDefenseById (int ID);
	int GetDefense2ById (int ID);
	int GetDefense3ById (int ID);
	int GetDefense4ById (int ID);
	int GetDefense5ById (int ID);
	int GetGlobalType (int ID);
	//-------ToDo
	int GetWeightById (int Id);
	int GetWeaponMaxDamage (int Id);
	void SetWeaponMaxDamage (int Id, int MaxDamage);
	int GetWeaponMinDamage (int Id);
	void SetWeaponMinDamage (int Id, int MinDamage);
	int GetWeaponNeedsAmmo (int Id);
	int GetWeaponIsAmmo (int Id);
	int GetWeaponCaliber (int Id);
	int GetWeaponAmmoQuantity (int Id);
	void SetWeaponAmmoQuantity (int Id, int Quantity);
	int GetWeaponCurrentAmmoQuantity (int Id);
	int GetQuality (int Id);
	void SetQuality (int Id, int Quality);
	int GetIsDestroyed (int Id);
	void SetIsDestroyed (int Id, int a);
	int GetWeaponRange (int Id);
	void SetWeaponRange (int Id, int Range);
	int GetWeaponBlastRadius (int Id);
	void SetWeaponBlastRadius (int Id, int Radius);
	int GetWeaponNextAmmo (int Id);
	void UnloadWeapon (int Id);
	void LoadWeapon (int Id, int AmmoId, int AmmoQuantity);
	void WeaponMakeOneShot (int Id);
	int GetWeaponShotPerStep (int Id);
	void SetWeaponShotPerStep (int Id, int Shots);
	int GetCharCode (int Id);
	void SetCharCode (int Id, int Code);
	int GetColorVisible (int Id);
	void SetColorVisible (int Id, int Color);
	int GetColorNotVisible (int Id);
	void SetColorNotVisible (int Id, int Color);

};

