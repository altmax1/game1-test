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
	cout << Temp.size()<<endl;

	return;

}
