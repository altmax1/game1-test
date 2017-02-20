#pragma once
using namespace std;

struct Weapon
{
	int ID;
	string Name;
	string RName;
	int Type; // 0-�������, 1 - ��������� �������, 2 - �. ��������, 3 - ��������
	int Weight;
	int MaxDamage;
	int MinDamage;
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
};

