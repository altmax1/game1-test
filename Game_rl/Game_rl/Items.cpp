#include "StdAfx.h"
#include "Items.h"
#include "X_File.h"

using namespace std;
Items::Items(void)
{
}


Items::~Items(void)
{
}
int Items::GetTypeOfWeapon ( int ID)
{
	return Weapons[ID].Type;
}

bool Items::GetStackable (int ID)
{

	return Weapons[ID].Stackable;
}

string Items::GetNameOfWeapon (int ID)
{
	return Weapons[ID].RName;
}

int Items::QuantityWeaponItems()
{
	return Weapons.size();
}

void Items::InsertWeaponsInStorage (vector <map<string,string>> Temp)
{

	vector <map<string,string>>::iterator p;
	p = Temp.begin();
	while (p!= Temp.end())
	{
		map <string,string>::iterator MapPtr;
		Weapon TempWeapon;
		MapPtr = p->find("ID");
		TempWeapon.ID = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Name");
		TempWeapon.Name = MapPtr->second;
		MapPtr = p->find("RName");
		TempWeapon.RName = MapPtr->second;
		MapPtr = p->find("Type");
		TempWeapon.Type = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Weight");
		TempWeapon.Weight = atoi(MapPtr->second.c_str());
		MapPtr = p->find("MinDamage");
		TempWeapon.MinDamage = atoi(MapPtr->second.c_str());
		MapPtr = p->find("MaxDamage");
		TempWeapon.MaxDamage = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Stackable");
		TempWeapon.Stackable = atoi(MapPtr->second.c_str());
		Weapons.push_back (TempWeapon);
		p++;

	}

}

void Items::GetWeaponsFromFile()
{
	vector <map<string,string>> Temp;
	FileContent Content;
	X_File::X_ReadFile ( (LPCTSTR)L".\\Files\\Weapons.ini", Content);
	X_File::X_ParseIniFile (Content, Temp);
	InsertWeaponsInStorage (Temp);
	
	return;

}

void Items::InsertArmoursInStorage ( vector <map<string,string>> Temp)
{
	vector <map<string,string>>::iterator p;
	p = Temp.begin();
	while (p!= Temp.end())
	{
		map <string,string>::iterator MapPtr;
		Armour TempArmour;
		MapPtr = p->find("ID");
		TempArmour.ID = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Name");
		TempArmour.Name = MapPtr->second;
		MapPtr = p->find("RName");
		TempArmour.RName = MapPtr->second;
		MapPtr = p->find("Type");
		TempArmour.Type = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Type2");
		TempArmour.Type = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Weight");
		TempArmour.Weight = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense");
		TempArmour.Defense = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense2");
		TempArmour.Defense = atoi(MapPtr->second.c_str());
		MapPtr = p->find("TypeOfDefense2");
		TempArmour.TypeOfDefense2 = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Stackable");
		TempArmour.Stackable = atoi(MapPtr->second.c_str());
		Armours.push_back (TempArmour);
		p++;

	}
	return;
}

void Items::GetArmoursFromFile ()
{
	vector <map<string,string>> Temp;
	FileContent Content;
	X_File::X_ReadFile ( (LPCTSTR)L".\\Files\\Armours.ini", Content);
	X_File::X_ParseIniFile (Content, Temp);
	InsertArmoursInStorage (Temp);
	return;
}
