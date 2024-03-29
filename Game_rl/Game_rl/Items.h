#pragma once
using namespace std;

struct Item{
	int ID;
	int Weight;
	bool Unique;
	string Name;
	string RName;
	string Description;
	bool Stackable;
	int Type;
	int Quality; //�������� - ����� ��, ���� �������, �� �����.
	bool Destroyed; //���� ���������, ������ 1. � not unique �� ���������.
	int CharCode; //������ ��� ������
	int ColorVisible;
	int ColorNotVisible;
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
	int Range;  // ��������� ��������� (��������)
	int BlastRadius; //������ ���������
	int ShotsPerStep; //��������� � �������
	int AfterEffectType; // ��� ����������� ��������
	int AfterEffectTime; // ����� �����������
	int AfterEffectPower; // ���� �����������
	int MaxDamage2;
	int MinDamage2;
	int Damage2Type;
	int MaxDamage3;
	int MinDamage3;
	int Damage3Type;
	int NeedsEnergy;
	int EnergyPerUse;
	int FacultativeEnergy;
};

struct Armour: public Item
{
	//int Type -  ����� ����������, 1 - ������, 2 - ����, 3 - ����, 4 - ����
	int Type2; // ��� ����� ���� �������
	int Defense[10]; 
	bool CanBuiltedIn; //����� �� �������� ���-����
	int NumOfBuiltedInSlots;
	vector <int> SlotForBuiltIn;
	int BuiltInType; // ��� ������������
		

};

struct Stuff : public Item
{


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
	vector <Stuff> UniqueStuff;
	vector <Stuff> CommonStuff;
	vector <Stuff> StuffFromLevel;
	set <int> ExistingID; // ��� �������� ������������ ID ��� ������ �������� ����
public:
	Items(void);
	~Items(void);
	void GetUniqueWeaponsFromFile ();
	void GetCommonWeaponsFromFile ();
	void InsertUniqueWeaponsInStorage (vector <map<string,string>> Temp);
	void InsertCommonWeaponsInStorage (vector <map<string,string>> Temp);
	void ReadWeaponFromMap(map <string, string> &MyMap, Weapon &Temp);
	void GetUniqueArmourFromFile ();
	void GetCommonArmourFromFile ();
	void InsertUniqueArmourInStorage (vector <map<string,string>> Temp);
	void InsertCommonArmourInStorage (vector <map<string,string>> Temp);
	void ReadArmourFromMap(map <string, string> &MyMap, Armour &Temp);
	void GetUniqueStuffFromFile();
	void GetCommonStuffFromFile();
	void InsertUniqueStuffInStorage(vector <map<string, string>> Temp);
	void InsertCommonStuffInStorage(vector <map<string, string>> Temp);
	void ReadStuffFromMap(map <string, string> &MyMap, Stuff &Temp);
	int QuantityUniqueWeapon ();
	int QuantityCommonWeapon ();
	int GetIdForCreation (int Id); // ������� ����� ���������� ���� � ���������� � ID ��� �������� 
	int GetType2OfArmour (int ID);
	bool GetStackable (int ID);
	string GetNameById (int ID);
	int GetTypeById (int ID);
	int GetType2ById (int ID);
	int GetDefenseById (int ID);
	int GetDefenseByIdAdvanced (int Id, int NumOfDefense);
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
	int GetWeaponAfterEffectType (int Id);
	void SetWeaponAfterEffectType (int Id, int Type);
	int GetWeaponAfterEffectTime (int Id);
	void SetWeaponAfterEffectTime (int Id, int Time);
	int GetWeaponAfterEffectPower (int Id);
	void SetWeaponAfterEffectPower (int Id, int Power);
	int CheckID (int ID); // ���������, ���������� �� ����� ID ��� �������� ����
	void SetWeaponDamage2Type(int ID, int Type);
	int GetWeaponDamage2Type( int ID);
	void SetWeaponMaxDamage2(int ID, int Damage);
	int GetWeaponMaxDamage2(int ID);
	void SetWeaponMinDamage2(int ID,int Damage);
	int GetWeaponMinDamage2(int ID);
	void SetWeaponDamage3Type(int ID,int Type);
	int GetWeaponDamage3Type(int ID);
	void SetWeaponMaxDamage3(int ID,int Damage);
	int GetWeaponMaxDamage3(int ID);
	void SetWeaponMinDamage3(int ID,int Damage);
	int GetWeaponMinDamage3(int ID);
	int GetWeaponNeedsEnergy(int ID);
	void SetWeaponNeedEnergy(int ID, int Param);
	int GetWeaponEnergyPerUse(int ID);
	void SetWeaponEnergyPerUse(int ID, int Energy);
	int GetWeaponFaccultativeEnergy(int ID);
	void SetWeaponFacultativeEnergy(int ID, int Param);
	string GetDescription(int ID);
	void SaveItems();
	void SaveWeapon(ofstream &MyStream);
	void SaveArmour(ofstream &MyStream);
	void SaveStuff(ofstream &MyStream);
	void LoadItems();
	void LoadWeapons(ifstream &MyStream);
	void LoadArmour(ifstream &MyStream);
	void LoadStuff(ifstream &MyStream);
};

