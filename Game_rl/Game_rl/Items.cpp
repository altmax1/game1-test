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
		Weapon TempWeapon;
		ReadWeaponFromMap(*p, TempWeapon);
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
		Weapon TempWeapon;
		ReadWeaponFromMap(*p, TempWeapon);
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

void Items::ReadWeaponFromMap(map<string, string>& MyMap, Weapon & TempWeapon)
{
	map <string, string>::iterator MapPtr;
	MapPtr = MyMap.find("ID");
	TempWeapon.ID = atoi(MapPtr->second.c_str());
	ExistingID.insert(TempWeapon.ID);
	MapPtr = MyMap.find("Name");
	TempWeapon.Name = MapPtr->second;
	MapPtr = MyMap.find("RName");
	TempWeapon.RName = MapPtr->second;
	MapPtr = MyMap.find("Type");
	TempWeapon.Type = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Quality");
	TempWeapon.Quality = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Weight");
	TempWeapon.Weight = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("MinDamage");
	TempWeapon.MinDamage = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("MaxDamage");
	TempWeapon.MaxDamage = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Stackable");
	TempWeapon.Stackable = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Unique");
	TempWeapon.Unique = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("NeedsAmmo");
	TempWeapon.NeedsAmmo = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("IsAmmo");
	TempWeapon.IsAmmo = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Caliber");
	TempWeapon.Caliber = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("AmmoQuantity");
	TempWeapon.AmmoQuantity = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Destroyed");
	TempWeapon.Destroyed = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Range");
	TempWeapon.Range = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("BlastRadius");
	TempWeapon.BlastRadius = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("ShotsPerStep");
	TempWeapon.ShotsPerStep = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("CharCode");
	TempWeapon.CharCode = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("ColorVisible");
	TempWeapon.ColorVisible = strtoul(MapPtr->second.c_str(), NULL, 16);
	MapPtr = MyMap.find("ColorNotVisible");
	TempWeapon.ColorNotVisible = strtoul(MapPtr->second.c_str(), NULL, 16);
	if (MyMap.count("AfterEffectType")>0)
	{
		MapPtr = MyMap.find("AfterEffectType");
		TempWeapon.AfterEffectType = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.AfterEffectType = 0;
	if (MyMap.count("AfterEffectTime")>0)
	{
		MapPtr = MyMap.find("AfterEffectTime");
		TempWeapon.AfterEffectTime = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.AfterEffectTime = 0;
	if (MyMap.count("AfterEffectPower")>0)
	{
		MapPtr = MyMap.find("AfterEffectPower");
		TempWeapon.AfterEffectPower = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.AfterEffectPower = 0;
	if (MyMap.count("MaxDamage2") > 0)
	{
		MapPtr = MyMap.find("MaxDamage2");
		TempWeapon.MaxDamage2 = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.MaxDamage2 = 0;
	if (MyMap.count("MaxDamage3") > 0)
	{
		MapPtr = MyMap.find("MaxDamage3");
		TempWeapon.MaxDamage3 = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.MaxDamage3 = 0;
	if (MyMap.count("MinDamage2") > 0)
	{
		MapPtr = MyMap.find("MinDamage2");
		TempWeapon.MinDamage2 = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.MinDamage2 = 0;
	if (MyMap.count("MinDamage3") > 0)
	{
		MapPtr = MyMap.find("MinDamage3");
		TempWeapon.MinDamage3 = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.MinDamage3 = 0;
	if (MyMap.count("Damage2Type") > 0)
	{
		MapPtr = MyMap.find("Damage2Type");
		TempWeapon.Damage2Type = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.Damage2Type = 0;
	if (MyMap.count("Damage3Type") > 0)
	{
		MapPtr = MyMap.find("Damage3Type");
		TempWeapon.Damage3Type = atoi(MapPtr->second.c_str());
	}
	else
		TempWeapon.Damage3Type = 0;
	if (MyMap.count("NeedsEnergy") > 0)
	{
		MapPtr = MyMap.find("NeedsEnergy");
		TempWeapon.NeedsEnergy = atoi(MapPtr->second.c_str());
	}
	else TempWeapon.NeedsEnergy = 0;
	if (MyMap.count("FacultativeEnergy") > 0)
	{
		MapPtr = MyMap.find("FacultativeEnergy");
		TempWeapon.FacultativeEnergy = atoi(MapPtr->second.c_str());
	}
	else TempWeapon.FacultativeEnergy = 0;
	if (MyMap.count("EnergyPerUse") > 0)
	{
		MapPtr = MyMap.find("EnergyPerUse");
		TempWeapon.EnergyPerUse = atoi(MapPtr->second.c_str());
	}
	else TempWeapon.EnergyPerUse = 0;
	if (MyMap.count("Desccription") > 0)
	{
		MapPtr = MyMap.find("Desccription");
		TempWeapon.Description = MapPtr->second;
	}
	else TempWeapon.Description = "None";

	return;

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
	char *temp = new char [3];
	vector <map<string,string>>::iterator p;
	p = Temp.begin();
	while (p!= Temp.end())
	{
		map <string,string>::iterator MapPtr;
		Armour TempArmour;
		ReadArmourFromMap(*p, TempArmour);
		
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
	delete [] temp;
}

void Items::ReadArmourFromMap(map<string, string>& MyMap, Armour & TempArmour)
{
	char *temp;
	temp = new char[4];
	map <string, string>::iterator MapPtr;
	MapPtr = MyMap.find("ID");
	TempArmour.ID = atoi(MapPtr->second.c_str());
	ExistingID.insert(TempArmour.ID);
	MapPtr = MyMap.find("Name");
	TempArmour.Name = MapPtr->second;
	MapPtr = MyMap.find("RName");
	TempArmour.RName = MapPtr->second;
	MapPtr = MyMap.find("Type");
	TempArmour.Type = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Weight");
	TempArmour.Weight = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Unique");
	TempArmour.Unique = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Stackable");
	TempArmour.Stackable = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Type2");
	TempArmour.Type2 = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("Defense");
	TempArmour.Defense[0] = atoi(MapPtr->second.c_str());

	for (int i = 1; i <= 10; i++)
	{
		int NumInVector = i - 1;
		_itoa(i, temp, 10);
		string name2 = temp;
		string name = "Defense" + name2;
		if (MyMap.count(name)>0)
		{

			MapPtr = MyMap.find(name);
			TempArmour.Defense[NumInVector] = atoi(MapPtr->second.c_str());
		}

	}

	MapPtr = MyMap.find("CanBuiltedIn");
	TempArmour.CanBuiltedIn = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("NumOfBuiltedInSlots");
	TempArmour.NumOfBuiltedInSlots = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("BuiltInType");
	TempArmour.BuiltInType = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("CharCode");
	TempArmour.CharCode = atoi(MapPtr->second.c_str());
	MapPtr = MyMap.find("ColorVisible");
	TempArmour.ColorVisible = strtoul(MapPtr->second.c_str(), NULL, 16);
	MapPtr = MyMap.find("ColorNotVisible");
	TempArmour.ColorNotVisible = strtoul(MapPtr->second.c_str(), NULL, 16);
	delete[] temp;
	return;
}

void Items::InsertUniqueArmourInStorage (vector <map<string,string>> Temp)
{
	char *temp = new char [3];
	vector <map<string,string>>::iterator p;
	p = Temp.begin();
	while (p!= Temp.end())
	{
		map <string,string>::iterator MapPtr;
		Armour TempArmour;
		ReadArmourFromMap(*p, TempArmour);
		
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
	delete [] temp;
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
	if (ID>=0 && ID <900000)
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
		return ArmourFromLevel[ID-1000000].Defense[0];
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense[0];
	return 0;
}

int Items::GetDefenseByIdAdvanced (int ID, int NumOfDefense)
{
	if (NumOfDefense >10 || NumOfDefense <1)
		return 0;
	if (ID>=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Defense[NumOfDefense-1];
	if (ID>=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Defense[NumOfDefense-1];
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

int Items::GetWeightById (int ID)
{
	if (ID>=0 && ID <900000)
		return WeaponFromLevel[ID].Weight;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID-900000].Weight;
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].Weight;
	if (ID >=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].Weight;
	return 0;
}

int Items::GetWeaponMaxDamage (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].MaxDamage;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].MaxDamage;
	return 0;
}

void Items::SetWeaponMaxDamage (int Id, int MaxDamage)
{
	if (Id>=0 && Id<900000)
		WeaponFromLevel[Id].MaxDamage = MaxDamage;
	if (Id>=900000 && Id < 1000000)
		CommonWeapon[Id-900000].MaxDamage = MaxDamage;
}

int Items::GetWeaponMinDamage (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].MinDamage;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].MinDamage;
	return 0;
}

void Items::SetWeaponMinDamage (int Id, int MinDamage)
{
	if (Id>=0 && Id<900000)
		WeaponFromLevel[Id].MinDamage = MinDamage;
	if (Id>=900000 && Id < 1000000)
		CommonWeapon[Id-900000].MinDamage = MinDamage;
}

int Items::GetWeaponNeedsAmmo (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].NeedsAmmo;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].NeedsAmmo;
	return 0;
}

int Items::GetWeaponIsAmmo (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].IsAmmo;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].IsAmmo;
	return 0;
}

int Items::GetWeaponCaliber (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].Caliber;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].Caliber;
	return 0;
}

int Items::GetWeaponAmmoQuantity (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].AmmoQuantity;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].AmmoQuantity;
	return 0;
}

void Items::SetWeaponAmmoQuantity (int Id, int Quantity)
{
	if (Id>=0 && Id<900000)
		WeaponFromLevel[Id].AmmoQuantity = Quantity;
	if (Id>=900000 && Id < 1000000)
		CommonWeapon[Id-900000].AmmoQuantity = Quantity;
}

int  Items::GetWeaponCurrentAmmoQuantity (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].Ammo.size();
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].Ammo.size();
	return 0;
}

int Items::GetQuality (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].Quality;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].Quality;
	return 0;
}

void Items::SetQuality (int Id, int Quality)
{
	if (Id>=0 && Id<900000)
		WeaponFromLevel[Id].Quality = Quality;
	if (Id>=900000 && Id < 1000000)
		CommonWeapon[Id-900000].Quality = Quality;
}

//void Items::SetWeaponAmmoQuantity (int Id, int Quality)
//{
//	if (Id>=0 && Id<900000)
//		WeaponFromLevel[Id].Quality = Quality;
//	if (Id>=900000 && Id < 1000000)
//		CommonWeapon[Id-900000].Quality = Quality;
//}

int Items::GetIsDestroyed (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].Destroyed;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].Destroyed;
	return 0;
}

void Items::SetIsDestroyed (int Id, int a)
{
	if (Id>=0 && Id<900000)
	{	
		if (a==0)
			WeaponFromLevel[Id].Destroyed = 0;
		else 
			WeaponFromLevel[Id].Destroyed = 1;
	}
	if (Id>=900000 && Id < 1000000)
	{
		if (a==0)
			CommonWeapon[Id-900000].Destroyed = 0;
		else
			CommonWeapon[Id-900000].Destroyed = 1;
	}
}

int Items::GetWeaponRange (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].Range;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].Range;
	return 0;
}

void Items::SetWeaponRange (int Id, int Range)
{
	if (Id>=0 && Id<900000)
		WeaponFromLevel[Id].Range = Range;
	if (Id>=900000 && Id < 1000000)
		CommonWeapon[Id-900000].Range = Range;
}

int Items::GetWeaponBlastRadius (int Id)
{
	if (Id>=0 && Id<900000)
		return WeaponFromLevel[Id].BlastRadius;
	if (Id>=900000 && Id<1000000)
		return CommonWeapon[Id-900000].BlastRadius;
	return 0;
}

void Items::SetWeaponBlastRadius (int Id, int Radius)
{
	if (Id>=0 && Id<900000)
		WeaponFromLevel[Id].BlastRadius = Radius;
	if (Id>=900000 && Id < 1000000)
		CommonWeapon[Id-900000].BlastRadius = Radius;
}

int Items::GetWeaponNextAmmo (int Id)
{
	if (Id>=0 && Id<900000)
		if (WeaponFromLevel[Id].Ammo.size()>0)
			return WeaponFromLevel[Id].Ammo.back();
		else return -1;
	if (Id>=900000 && Id<1000000)
		if (CommonWeapon[Id-900000].Ammo.size()>0)
			return CommonWeapon[Id-900000].Ammo.back();
		else return -1;
	return 0;
}

void Items::UnloadWeapon (int Id)
{
	if (WeaponFromLevel[Id].Ammo.size()>0)
		WeaponFromLevel[Id].Ammo.pop_back();
	return;
}

void Items::LoadWeapon (int Id, int AmmoId, int AmmoQuantity)
{
	for (int i=0;i<AmmoQuantity; i++)
		WeaponFromLevel[Id].Ammo.push_back (AmmoId);
	return;
}

void Items::WeaponMakeOneShot (int Id)

{
	if (WeaponFromLevel[Id].NeedsAmmo == 1)
	{
		if (WeaponFromLevel[Id].Ammo.size() > 0)
			WeaponFromLevel[Id].Ammo.pop_back();
		return;
	}
	if (WeaponFromLevel[Id].NeedsEnergy == 1 && WeaponFromLevel[Id].Type == 11)
	{
		int AmmoID = WeaponFromLevel[Id].Ammo.back();
		int AmmoQuality = WeaponFromLevel[AmmoID].Quality;
		int EnPerUse = WeaponFromLevel[Id].EnergyPerUse;
		if (EnPerUse <= AmmoQuality)
		{
			AmmoQuality -=  EnPerUse;
			WeaponFromLevel[AmmoID].Quality = AmmoQuality;
		}
	}
		
}

void Items::SetWeaponShotPerStep (int Id, int Shots)
{
	if (Id>=0 && Id < 900000)
		WeaponFromLevel[Id].ShotsPerStep = Shots;
	if (Id >= 9000000 && Id < 1000000)
		CommonWeapon[Id-900000].ShotsPerStep = Shots;
	return;
}

int Items::GetWeaponShotPerStep (int Id)
{
	if (Id>=0 && Id < 900000)
		return WeaponFromLevel[Id].ShotsPerStep;
	else if (Id >= 9000000 && Id < 1000000)
		return CommonWeapon[Id-900000].ShotsPerStep;
	else return 0;
}

int Items::GetCharCode (int ID)
{
	if (ID>=0 && ID <900000)
		return WeaponFromLevel[ID].CharCode;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID-900000].CharCode;
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].CharCode;
	if (ID >=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].CharCode;
	return 0;
}

int Items::GetColorVisible (int ID)
{
	if (ID>=0 && ID <900000)
		return WeaponFromLevel[ID].ColorVisible;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID-900000].ColorVisible;
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].ColorVisible;
	if (ID >=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].ColorVisible;
	return 0xFFFFFFFF;
}

int Items::GetColorNotVisible (int ID)
{
	if (ID>=0 && ID <900000)
		return WeaponFromLevel[ID].ColorNotVisible;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID-900000].ColorNotVisible;
	if (ID >=1000000 && ID < 1900000)
		return ArmourFromLevel[ID-1000000].ColorNotVisible;
	if (ID >=1900000 && ID < 2000000)
		return CommonArmour[ID-1900000].ColorNotVisible;
	return 0;
}

void Items::SetCharCode (int ID, int Code) 
{
	if (ID>=0 && ID <900000)
		WeaponFromLevel[ID].CharCode = Code;
	if (ID>=1000000 && ID<1900000)
		ArmourFromLevel[ID-1000000].CharCode = Code;
	return;
}

void Items::SetColorVisible (int ID, int Color)
{
	if (ID>=0 && ID <900000)
		WeaponFromLevel[ID].ColorVisible = Color;
	if (ID>=1000000 && ID<1900000)
		ArmourFromLevel[ID-1000000].ColorVisible = Color;
	return;
}

void Items::SetColorNotVisible (int ID, int Color)
{
	if (ID>=0 && ID <900000)
		WeaponFromLevel[ID].ColorNotVisible = Color;
	if (ID>=1000000 && ID<1900000)
		ArmourFromLevel[ID-1000000].ColorNotVisible = Color;
	return;
}

int Items::GetWeaponAfterEffectType (int Id)
{
	if (Id>0 && Id < 900000)
		return WeaponFromLevel[Id].AfterEffectType;
	if (Id>=900000 && Id < 1000000)
		return CommonWeapon[Id-900000].AfterEffectType;
}
void Items::SetWeaponAfterEffectType (int Id, int Type)
{}

int Items::GetWeaponAfterEffectTime (int Id)
{
	if (Id>0 && Id < 900000)
		return WeaponFromLevel[Id].AfterEffectTime;
	if (Id>=900000 && Id < 1000000)
		return CommonWeapon[Id-900000].AfterEffectTime;
}
void Items::SetWeaponAfterEffectTime (int Id, int Time)
{}

int Items::GetWeaponAfterEffectPower (int Id)
{
	if (Id>0 && Id < 900000)
		return WeaponFromLevel[Id].AfterEffectPower;
	if (Id>=900000 && Id < 1000000)
		return CommonWeapon[Id-900000].AfterEffectPower;
}
void Items::SetWeaponAfterEffectPower (int Id, int Power)
{}

int Items::CheckID (int ID)
{
	set <int>::iterator p;
	p = ExistingID.find (ID);
	if (p == ExistingID.end())
		return 0;
	else
		return 1;
}

void Items::SetWeaponDamage2Type(int ID,int Type)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].Damage2Type = Type;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].Damage2Type = Type;

}
int Items::GetWeaponDamage2Type(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].Damage2Type;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].Damage2Type;
	return 0;
}


void Items::SetWeaponMaxDamage2(int ID, int Damage)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].MaxDamage2 = Damage;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].MaxDamage2 = Damage;

}
int Items::GetWeaponMaxDamage2(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].MaxDamage2;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].MaxDamage2;
	return 0;
}
void Items::SetWeaponMinDamage2(int ID, int Damage)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].MinDamage2 = Damage;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].MinDamage2 = Damage;
}
int Items::GetWeaponMinDamage2(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].MinDamage2;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].MinDamage2;
	return 0;
}
void Items::SetWeaponDamage3Type(int ID, int Type)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].Damage3Type = Type;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].Damage3Type = Type;
}
int Items::GetWeaponDamage3Type(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].Damage3Type;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].Damage3Type;
	return 0;
}
void Items::SetWeaponMaxDamage3(int ID, int Damage)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].MaxDamage3 = Damage;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].MaxDamage3 = Damage;
}
int Items::GetWeaponMaxDamage3(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].MaxDamage3;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].MaxDamage3;
	return 0;
}
void Items::SetWeaponMinDamage3(int ID, int Damage)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].MinDamage3 = Damage;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].MinDamage3 = Damage;
}
int Items::GetWeaponMinDamage3(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].MinDamage3;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].MinDamage3;
	return 0;
}

int Items::GetWeaponNeedsEnergy(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].NeedsEnergy;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].NeedsEnergy;
	return 0;
}

void Items::SetWeaponNeedEnergy(int ID, int Param)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].NeedsEnergy = Param;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].NeedsEnergy = Param;
	return;
}

int Items::GetWeaponEnergyPerUse(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].EnergyPerUse;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].EnergyPerUse;
	return 0;
}

void Items::SetWeaponEnergyPerUse(int ID, int Energy)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].EnergyPerUse = Energy;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].EnergyPerUse = Energy;
	return;
}

int Items::GetWeaponFaccultativeEnergy(int ID)
{
	if (ID >= 0 && ID < 900000)
		return WeaponFromLevel[ID].EnergyPerUse;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].EnergyPerUse;
	return 0;
}

void Items::SetWeaponFacultativeEnergy(int ID, int Param)
{
	if (ID >= 0 && ID < 900000)
		WeaponFromLevel[ID].FacultativeEnergy = Param;
	if (ID >= 900000 && ID < 1000000)
		CommonWeapon[ID - 900000].FacultativeEnergy = Param;
	return;
}

string Items::GetDescription(int ID)
{
	if (ID >= 0 && ID <900000)
		return WeaponFromLevel[ID].Description;
	if (ID >= 900000 && ID < 1000000)
		return CommonWeapon[ID - 900000].Description;
	if (ID >= 1000000 && ID < 1900000)
		return ArmourFromLevel[ID - 1000000].Description;
	if (ID >= 1900000 && ID < 2000000)
		return CommonArmour[ID - 1900000].Description;
	return "None description";
}

void Items::SaveItems()
{ 
	ofstream Out(".\\Files\\save\\items.sav", ios::binary | ios::out);
	int Size = ExistingID.size();
	Out.write((char*)&Size, sizeof Size);
	for (auto a : ExistingID)
	{
		Out.write((char*)&a, sizeof a);
	}
	SaveWeapon(Out);
	SaveArmour(Out);
}

void Items::SaveWeapon(ofstream & MyStream)
{
	int Size = WeaponFromLevel.size();
	MyStream.write((char*)&Size, sizeof Size);
	int temp;
	for (auto a : WeaponFromLevel)
	{
		MyStream.write((char*)&a.ID, sizeof a.ID);
		MyStream.write((char*)&a.Weight, sizeof a.Weight);
		MyStream.write((char*)&a.Unique, sizeof a.Unique);
		temp = a.Name.size();
		MyStream.write((char*)&temp, sizeof temp);
		MyStream.write(a.Name.c_str(), temp);
		temp = a.RName.size();
		MyStream.write((char*)&temp, sizeof temp);
		MyStream.write(a.RName.c_str(), temp);
		temp = a.Description.size();
		MyStream.write((char*)&temp, sizeof temp);
		MyStream.write(a.Description.c_str(), temp);
		MyStream.write((char*)&a.Stackable, sizeof a.Stackable);
		MyStream.write((char*)&a.Type, sizeof a.Type);
		MyStream.write((char*)&a.Quality, sizeof a.Quality);
		MyStream.write((char*)&a.Destroyed, sizeof a.Destroyed);
		MyStream.write((char*)&a.CharCode, sizeof a.CharCode);
		MyStream.write((char*)&a.ColorVisible, sizeof a.ColorVisible);
		MyStream.write((char*)&a.ColorNotVisible, sizeof a.ColorNotVisible);
		MyStream.write((char*)&a.MaxDamage, sizeof a.MaxDamage);
		MyStream.write((char*)&a.MinDamage, sizeof a.MinDamage);
		MyStream.write((char*)&a.NeedsAmmo, sizeof a.NeedsAmmo);
		MyStream.write((char*)&a.IsAmmo, sizeof a.IsAmmo);
		MyStream.write((char*)&a.Caliber, sizeof a.Caliber);
		MyStream.write((char*)&a.AmmoQuantity, sizeof a.AmmoQuantity);
		temp = a.Ammo.size();
		MyStream.write((char*)&temp, sizeof temp);
		for (auto b : a.Ammo)
		{
			temp = b;
			MyStream.write((char*)&temp, sizeof temp);
		}
		MyStream.write((char*)&a.Range, sizeof a.Range);
		MyStream.write((char*)&a.BlastRadius, sizeof a.BlastRadius);
		MyStream.write((char*)&a.ShotsPerStep, sizeof a.ShotsPerStep);
		MyStream.write((char*)&a.AfterEffectType, sizeof a.AfterEffectType);
		MyStream.write((char*)&a.AfterEffectTime, sizeof a.AfterEffectTime);
		MyStream.write((char*)&a.AfterEffectPower, sizeof a.AfterEffectPower);
		MyStream.write((char*)&a.MaxDamage2, sizeof a.MaxDamage2);
		MyStream.write((char*)&a.MinDamage2, sizeof a.MinDamage2);
		MyStream.write((char*)&a.Damage2Type, sizeof a.Damage2Type);
		MyStream.write((char*)&a.MaxDamage3, sizeof a.MaxDamage3);
		MyStream.write((char*)&a.MinDamage3, sizeof a.MinDamage3);
		MyStream.write((char*)&a.Damage3Type, sizeof a.Damage3Type);
		MyStream.write((char*)&a.NeedsEnergy, sizeof a.NeedsEnergy);
		MyStream.write((char*)&a.EnergyPerUse, sizeof a.EnergyPerUse);
		MyStream.write((char*)&a.FacultativeEnergy, sizeof a.FacultativeEnergy);

	}
}

void Items::SaveArmour(ofstream & MyStream)
{
	int Size = ArmourFromLevel.size();
	MyStream.write((char*)&Size, sizeof Size);
	int temp;
	for (auto a : ArmourFromLevel)
	{
		MyStream.write((char*)&a.ID, sizeof a.ID);
		MyStream.write((char*)&a.Weight, sizeof a.Weight);
		MyStream.write((char*)&a.Unique, sizeof a.Unique);
		temp = a.Name.size();
		MyStream.write((char*)&temp, sizeof temp);
		MyStream.write(a.Name.c_str(), temp);
		temp = a.RName.size();
		MyStream.write((char*)&temp, sizeof temp);
		MyStream.write(a.RName.c_str(), temp);
		temp = a.Description.size();
		MyStream.write((char*)&temp, sizeof temp);
		MyStream.write(a.Description.c_str(), temp);
		MyStream.write((char*)&a.Stackable, sizeof a.Stackable);
		MyStream.write((char*)&a.Type, sizeof a.Type);
		MyStream.write((char*)&a.Quality, sizeof a.Quality);
		MyStream.write((char*)&a.Destroyed, sizeof a.Destroyed);
		MyStream.write((char*)&a.CharCode, sizeof a.CharCode);
		MyStream.write((char*)&a.ColorVisible, sizeof a.ColorVisible);
		MyStream.write((char*)&a.ColorNotVisible, sizeof a.ColorNotVisible);
		MyStream.write((char*)&a.Type2, sizeof a.Type2);
		MyStream.write((char*)a.Defense, (sizeof a.Defense[0]) * 10);
		MyStream.write((char*)&a.CanBuiltedIn, sizeof a.CanBuiltedIn);
		MyStream.write((char*)&a.NumOfBuiltedInSlots, sizeof a.NumOfBuiltedInSlots);
		temp = a.SlotForBuiltIn.size();
		MyStream.write((char*)&temp, sizeof temp);
		for (auto b : a.SlotForBuiltIn)
		{
			temp = b;
			MyStream.write((char*)&temp, sizeof temp);
		}
		MyStream.write((char*)&a.BuiltInType, sizeof a.BuiltInType);

	}
}
