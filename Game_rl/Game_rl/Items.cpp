#include "StdAfx.h"
#include "Items.h"
#include "X_File.h"

using namespace std;
Items::Items(void)
{
	GetUniqueWeaponsFromFile ();
	GetCommonWeaponsFromFile ();
	GetUniqueArmourFromFile();
	GetCommonArmourFromFile();
}


Items::~Items(void)
{
}


bool Items::GetStackable (int ID)
{

	if (ID<900000)
		return WeaponFromLevel[ID].Stackable;
	if (ID >=900000 && ID < 1000000)
		return CommonWeapon[ID-900000].Stackable;
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Stackable;
	if (ID >= 1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Stackable;
	return 0;
}


void Items::GetUniqueWeaponsFromFile ()
{
	vector <map<string,string>> Temp;
	FileContent Content;
	X_File::X_ReadFile ( (LPCTSTR)L".\\Files\\UniqueWeapon.ini", Content);
	X_File::X_ParseIniFile (Content, Temp);
	InsertUniqueWeaponsInStorage (Temp);
	return;
}

void Items::InsertUniqueWeaponsInStorage (vector <map<string,string>> Temp)
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
		MapPtr = p->find("Unique");
		TempWeapon.Unique = atoi (MapPtr->second.c_str());
		MapPtr = p->find("NeedsAmmo");
		TempWeapon.NeedsAmmo = atoi (MapPtr->second.c_str());
		MapPtr = p->find("IsAmmo");
		TempWeapon.IsAmmo = atoi (MapPtr->second.c_str());
		MapPtr = p->find("Caliber");
		TempWeapon.Caliber = atoi (MapPtr->second.c_str());
		MapPtr = p->find("AmmoQuantity");
		TempWeapon.AmmoQuantity = atoi (MapPtr->second.c_str());
		MapPtr = p->find("Destroyed");
		TempWeapon.Destroyed = atoi (MapPtr->second.c_str());
		MapPtr = p->find("Range");
		TempWeapon.Range = atoi (MapPtr->second.c_str());
		MapPtr = p->find("BlastRadius");
		TempWeapon.BlastRadius = atoi (MapPtr->second.c_str());
		try{
		if (TempWeapon.ID != UniqueWeapon.size())
			throw "BAD_ID_IN_UniqueWeapon";}
		catch(char *str)//сюда передастся строка
		{
		    cout << str << endl;
		}
		UniqueWeapon.push_back (TempWeapon);
		p++;

	}
}

void Items::GetCommonWeaponsFromFile ()
{
	vector <map<string,string>> Temp;
	FileContent Content;
	X_File::X_ReadFile ( (LPCTSTR)L".\\Files\\CommonWeapon.ini", Content);
	X_File::X_ParseIniFile (Content, Temp);
	InsertCommonWeaponsInStorage (Temp);
	return;
}

void Items::InsertCommonWeaponsInStorage (vector <map<string,string>> Temp)
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
		MapPtr = p->find("Unique");
		TempWeapon.Unique = atoi (MapPtr->second.c_str());
		MapPtr = p->find("NeedsAmmo");
		TempWeapon.NeedsAmmo = atoi (MapPtr->second.c_str());
		MapPtr = p->find("IsAmmo");
		TempWeapon.IsAmmo = atoi (MapPtr->second.c_str());
		MapPtr = p->find("Caliber");
		TempWeapon.Caliber = atoi (MapPtr->second.c_str());
		MapPtr = p->find("AmmoQuantity");
		TempWeapon.AmmoQuantity = atoi (MapPtr->second.c_str());
		MapPtr = p->find("Destroyed");
		TempWeapon.Destroyed = atoi (MapPtr->second.c_str());
		MapPtr = p->find("Range");
		TempWeapon.Range = atoi (MapPtr->second.c_str());
		MapPtr = p->find("BlastRadius");
		TempWeapon.BlastRadius = atoi (MapPtr->second.c_str());
		try{
		if (TempWeapon.ID-900000 != CommonWeapon.size())
			throw "BAD_ID_IN_CommonWeapon";}
		catch(char *str)//сюда передастся строка
		{
		    cout << str << endl;
		}
		CommonWeapon.push_back (TempWeapon);
		p++;

	}
}

void Items::GetCommonArmourFromFile ()
{
	vector <map<string,string>> Temp;
	FileContent Content;
	X_File::X_ReadFile ( (LPCTSTR)L".\\Files\\CommonArmour.ini", Content);
	X_File::X_ParseIniFile (Content, Temp);
	InsertCommonArmourInStorage (Temp);
	return;
}

void Items::GetUniqueArmourFromFile ()
{
	vector <map<string,string>> Temp;
	FileContent Content;
	X_File::X_ReadFile ( (LPCTSTR)L".\\Files\\UniqueArmour.ini", Content);
	X_File::X_ParseIniFile (Content, Temp);
	InsertUniqueArmourInStorage (Temp);
	return;
}

void Items::InsertCommonArmourInStorage (vector <map<string,string>> Temp)
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
		MapPtr = p->find("Weight");
		TempArmour.Weight = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Unique");
		TempArmour.Unique = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Stackable");
		TempArmour.Stackable = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Type2");
		TempArmour.Type2 = atoi(MapPtr->second.c_str());
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
		MapPtr = p->find("CanBuiltedIn");
		TempArmour.CanBuiltedIn = atoi(MapPtr->second.c_str());
		MapPtr = p->find("NumOfBuiltedInSlots");
		TempArmour.NumOfBuiltedInSlots = atoi(MapPtr->second.c_str());
		MapPtr = p->find("BuiltInType");
		TempArmour.BuiltInType = atoi(MapPtr->second.c_str());
		try{
		if (TempArmour.ID-1900000 != CommonArmour.size())
			throw "BAD_ID_IN_ComonArmour";}
		catch(char *str)//сюда передастся строка
		{
		    cout << str << endl;
		}
		CommonArmour.push_back (TempArmour);
		p++;
	}
}

void Items::InsertUniqueArmourInStorage (vector <map<string,string>> Temp)
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
		MapPtr = p->find("Weight");
		TempArmour.Weight = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Unique");
		TempArmour.Unique = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Stackable");
		TempArmour.Stackable = atoi(MapPtr->second.c_str());
		MapPtr = p->find("Type2");
		TempArmour.Type2 = atoi(MapPtr->second.c_str());
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
		MapPtr = p->find("CanBuiltedIn");
		TempArmour.CanBuiltedIn = atoi(MapPtr->second.c_str());
		MapPtr = p->find("NumOfBuiltedInSlots");
		TempArmour.NumOfBuiltedInSlots = atoi(MapPtr->second.c_str());
		MapPtr = p->find("BuiltInType");
		TempArmour.BuiltInType = atoi(MapPtr->second.c_str());
		try{
		if (TempArmour.ID-1000000 != UniqueArmour.size())
			throw "BAD_ID_IN_UniqueArmour";}
		catch(char *str)//сюда передастся строка
		{
		    cout << str << endl;
		}
		UniqueArmour.push_back (TempArmour);
		p++;
	}
}



int Items::QuantityUniqueWeapon ()
{
	return UniqueWeapon.size();
}

int Items::QuantityCommonWeapon ()
{
	return CommonWeapon.size();
}

int Items::GetIdForCreation (int Id)
{
	if (Id>=900000 && Id<1000000)
		return Id;
	if (Id>=0 && Id<900000)
	{
		int size = WeaponFromLevel.size();
		WeaponFromLevel.push_back (UniqueWeapon[Id]);
		return size;
	}
	if (Id>=1900000 && Id<2000000)
		return Id;
	if (Id>=1000000 && Id< 1900000)
	{
		int size = ArmourFromLevel.size();
		ArmourFromLevel.push_back (UniqueArmour[Id-1000000]);
		return size+1000000;
	}
}




int Items::GetType2OfArmour (int ID)
{
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Type2;
	if (ID >=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Type2;
	return -1;
}


string Items::GetNameById (int ID)
{
	if (ID>=0 && ID <900000)
		return WeaponFromLevel[ID].RName;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID-900000].RName;
	if (ID >= 1000000 && ID <1900000)
		return ArmourFromLevel[ID-1000000].RName;
	if (ID >= 1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].RName;
	return "NOT FOUND";

}

int Items::GetTypeById (int ID)
{
	if (ID>=0 && ID <1000000)
		return WeaponFromLevel[ID].Type;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID-900000].Type;
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Type;
	if (ID >=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Type;
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
	if (ID>=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Defense;
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense;
	return 0;
}

int Items::GetDefense2ById (int ID)
{
	if (ID>=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Defense2;
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense2;
	return 0;
}

int Items::GetDefense3ById (int ID)
{
	if (ID>=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Defense3;
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense3;
	return 0;
}

int Items::GetDefense4ById (int ID)
{
	if (ID>=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Defense4;
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense4;
	return 0;
}

int Items::GetDefense5ById (int ID)
{
	if (ID>=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Defense5;
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense5;
	return 0;
}



int Items::GetGlobalType (int ID)
{
	if (ID >=0 && ID < 1000000)
		return 0; // 0 - оружие
	if (ID >= 1000000 && ID < 2000000)
		return 1; // 1 - броня и одежда
	return -1;
}