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

struct Armour: public Item
{
	//int Type -  ����� ����������, 1 - ������, 2 - ����, 3 - ����, 4 - ����
	int Type2; // ��� ����� ���� �������
	int Defense; //������
	int Defense2; //����������
	int Defense3; //�����
	int Defense4; //��������, ��, �������
	int Defense5; //�����
	bool CanBuiltedIn; //����� �� �������� ���-����
	int NumOfBuiltedInSlots;
	vector <int> SlotForBuiltIn;
	int BuiltInType; // ��� ������������
		

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
	int GetWeaponQuality (int Id);
	void SetWeaponQuality (int Id, int Quality);
	int GetWeaponIsDestroyed (int Id);
	void SetWeaponIsDestroyed (int Id, int a);
	int GetWeaponRange (int Id);
	void SetWeaponRange (int Id, int Range);
	int GetWeaponBlastRadius (int Id);
	void SetWeaponBlastRadius (int Id, int Radius);
	int GetWeaponNextAmmo (int Id);
	void UnloadWeapon (int Id);
	void ReloadWeapon (int Id);

};

