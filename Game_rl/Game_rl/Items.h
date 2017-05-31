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
	bool NeedsAmmo; //����� �� �������
	bool IsAmmo; //�������� �� �������/��������
	int Caliber; //������
	int AmmoQuantity; // max ���������� �������� � ������
	vector <int> Ammo; //������� ����� - ������ �� ID
	int Quality; //�������� - ����� ��, ���� �������, �� �����.
	bool Destroyed; //���� ��������� ������, ������ 1. � not unique �� ���������.
	int Range;  // ��������� ��������� (��������)
	int BlastRadius; //������ ���������
};

struct Armour
{
	int ID;
	string Name;
	string RName;
	int Type; // ����� ����������, 1 - ������, 2 - ����, 3 - ����, 4 - ����
	int Type2; // ��� ����� ���� �������
	int Weight;
	int Defense; //������
	int Defense2; //����������
	int Defense3; //�����
	int Defense4; //��������, ��, �������
	int Defense5; //�����
	int TypeOfDefense2;
	bool Stackable;

};

class Items
{
private:
	//vector <Weapon> Weapons; //������� ����� ������������
	vector <Armour> Armours; // � ��� ���� �������
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

