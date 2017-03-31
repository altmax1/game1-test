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
	bool Stackable;
	//int Range;
	//bool Distant;
	//int BlastRadius; //������ ���������
	//bool NeedsAmmo;
	//int AmmoID;
	//int Accuracy; //��������
};

struct Armour
{
	int ID;
	string Name;
	string RName;
	int Type; // ����� ����������, 1 - ������, 2 - ����, 3 - ����, 4 - ����
	int Type2; // ��� ����� ���� �������
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
	bool GetStackable (int ID);
	string GetNameOfWeapon (int ID);
};

