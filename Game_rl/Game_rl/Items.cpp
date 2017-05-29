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
	if (ID<1000000)
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

string Items::GetNameOfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!=Armours.end ())
	{
		if (p->ID == ID)
			return p->RName;
		p++;
	
	}
	return "Not found in Armour";
}

int Items::GetTypeOfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!=Armours.end ())
	{
		if (p->ID == ID)
			return p->Type;
		p++;
	
	}
	return -1;

}

int Items::GetType2OfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->Type2;
		p++;
	}
	return -1;
}

int Items::GetDefenseOfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->Defense;
		p++;
	}
	return -1;
}

int Items::GetDefense2OfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->Defense2;
		p++;
	}
	return -1;
}

int Items::GetDefense3OfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->Defense3;
		p++;
	}
	return -1;
}

int Items::GetDefense4OfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->Defense4;
		p++;
	}
	return -1;
}

int Items::GetDefense5OfArmour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->Defense5;
		p++;
	}
	return -1;
}

int Items::GetTypeOfDef2Armour (int ID)
{
	vector <Armour>::iterator p;
	p = Armours.begin();
	while (p!= Armours.end())
	{
		if (p->ID == ID)
			return p->TypeOfDefense2;
		p++;
	}
	return -1;

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
		TempArmour.Type2 = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Weight");
		TempArmour.Weight = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense");
		TempArmour.Defense = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense2");
		TempArmour.Defense2 = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense3");
		TempArmour.Defense3 = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense4");
		TempArmour.Defense4 = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Defense5");
		TempArmour.Defense5 = atoi(MapPtr->second.c_str());
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

string Items::GetNameById (int ID)
{
	if (ID>=0 && ID <1000000)
		return GetNameOfWeapon (ID);
	if (ID >= 1000000 && ID < 2000000)
		return GetNameOfArmour (ID);
	return "NOT FOUND";

}

int Items::GetTypeById (int ID)
{
	if (ID>=0 && ID <1000000)
		return GetTypeOfWeapon (ID);
	if (ID >= 1000000 && ID < 2000000)
		return GetTypeOfArmour (ID);
	return -1;

}

int Items::GetType2ById (int ID)
{
	if (ID >=1000000 && ID < 2000000)
		return GetType2OfArmour (ID);
	return -1;
}

int Items::GetDefenseById (int ID)
{
	if (ID>=1000000 && ID < 2000000)
		return GetDefenseOfArmour (ID);
	return 0;
}

int Items::GetDefense2ById (int ID)
{
	if (ID>=1000000 && ID < 2000000)
		return GetDefense2OfArmour (ID);
	return 0;
}

int Items::GetDefense3ById (int ID)
{
	if (ID>=1000000 && ID < 2000000)
		return GetDefense3OfArmour (ID);
	return 0;
}

int Items::GetDefense4ById (int ID)
{
	if (ID>=1000000 && ID < 2000000)
		return GetDefense4OfArmour (ID);
	return 0;
}

int Items::GetDefense5ById (int ID)
{
	if (ID>=1000000 && ID < 2000000)
		return GetDefense5OfArmour (ID);
	return 0;
}


int Items::GetTypeOfDefense2 (int ID)
{
	if (ID >=1000000 && ID < 2000000)
		return GetTypeOfDef2Armour (ID);
	return -1;
}

int Items::GetGlobalType (int ID)
{
	if (ID >=0 && ID < 1000000)
		return 0; // 0 - оружие
	if (ID >= 1000000 && ID < 2000000)
		return 1; // 1 - броня и одежда
	return -1;
}