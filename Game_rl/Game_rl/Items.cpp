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
		ExistingID.insert (TempWeapon.ID);
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
		MapPtr = p->find ("ShotsPerStep");
		TempWeapon.ShotsPerStep = atoi (MapPtr->second.c_str());
		MapPtr = p->find ("CharCode");
		TempWeapon.CharCode = atoi (MapPtr->second.c_str());
		MapPtr = p->find ("ColorVisible");
		TempWeapon.ColorVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
		MapPtr = p->find ("ColorNotVisible");
		TempWeapon.ColorNotVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
		if (p->count ("AfterEffectType")>0)
		{
			MapPtr = p->find ("AfterEffectType");
			TempWeapon.AfterEffectType = atoi (MapPtr->second.c_str());
		}
		else
			TempWeapon.AfterEffectType = 0;
		if (p->count ("AfterEffectTime")>0)
		{
			MapPtr = p->find ("AfterEffectTime");
			TempWeapon.AfterEffectTime = atoi (MapPtr->second.c_str());
		}
		else
			TempWeapon.AfterEffectTime = 0;
		if (p->count ("AfterEffectPower")>0)
		{
			MapPtr = p->find ("AfterEffectPower");
			TempWeapon.AfterEffectPower = atoi (MapPtr->second.c_str());
		}
		else
			TempWeapon.AfterEffectPower = 0;

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
		ExistingID.insert (TempWeapon.ID);
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
		MapPtr = p->find ("ShotsPerStep");
		TempWeapon.ShotsPerStep = atoi (MapPtr->second.c_str());
		MapPtr = p->find ("CharCode");
		TempWeapon.CharCode = atoi (MapPtr->second.c_str());
		MapPtr = p->find ("ColorVisible");
		TempWeapon.ColorVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
		MapPtr = p->find ("ColorNotVisible");
		TempWeapon.ColorNotVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
		if (p->count ("AfterEffectType")>0)
		{
			MapPtr = p->find ("AfterEffectType");
			TempWeapon.AfterEffectType = atoi (MapPtr->second.c_str());
		}
		else
			TempWeapon.AfterEffectType = 0;
		if (p->count ("AfterEffectTime")>0)
		{
			MapPtr = p->find ("AfterEffectTime");
			TempWeapon.AfterEffectTime = atoi (MapPtr->second.c_str());
		}
		else
			TempWeapon.AfterEffectTime = 0;
		if (p->count ("AfterEffectPower")>0)
		{
			MapPtr = p->find ("AfterEffectPower");
			TempWeapon.AfterEffectPower = atoi (MapPtr->second.c_str());
		}
		else
			TempWeapon.AfterEffectPower = 0;
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
	char *temp = new char [3];
	vector <map<string,string>>::iterator p;
	p = Temp.begin();
	while (p!= Temp.end())
	{
		map <string,string>::iterator MapPtr;
		Armour TempArmour;
		MapPtr = p->find("ID");
		TempArmour.ID = atoi(MapPtr->second.c_str());
		ExistingID.insert (TempArmour.ID);
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
		TempArmour.Defense[0] = atoi(MapPtr->second.c_str());
		
		for (int i = 1; i <=10; i++)
		{
			int NumInVector = i-1;
			_itoa (i, temp, 10);
			string name2 = temp;
			string name = "Defense"+name2;
			if (p->count (name)>0)
			{
				MapPtr = p->find (name);
				TempArmour.Defense[NumInVector] = atoi (MapPtr->second.c_str());
			}
		
		}
		
		MapPtr = p->find("CanBuiltedIn");
		TempArmour.CanBuiltedIn = atoi(MapPtr->second.c_str());
		MapPtr = p->find("NumOfBuiltedInSlots");
		TempArmour.NumOfBuiltedInSlots = atoi(MapPtr->second.c_str());
		MapPtr = p->find("BuiltInType");
		TempArmour.BuiltInType = atoi(MapPtr->second.c_str());
		MapPtr = p->find ("CharCode");
		TempArmour.CharCode = atoi (MapPtr->second.c_str());
		MapPtr = p->find ("ColorVisible");
		TempArmour.ColorVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
		MapPtr = p->find ("ColorNotVisible");
		TempArmour.ColorNotVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
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

void Items::InsertUniqueArmourInStorage (vector <map<string,string>> Temp)
{
	char *temp = new char [3];
	vector <map<string,string>>::iterator p;
	p = Temp.begin();
	while (p!= Temp.end())
	{
		map <string,string>::iterator MapPtr;
		Armour TempArmour;
		MapPtr = p->find("ID");
		TempArmour.ID = atoi(MapPtr->second.c_str());
		ExistingID.insert (TempArmour.ID);
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
		TempArmour.Defense[0] = atoi(MapPtr->second.c_str());
		
		for (int i = 1; i <=10; i++)
		{
			int NumInVector = i-1;
			_itoa (i, temp, 10);
			string name2 = temp;
			string name = "Defense"+name2;
			if (p->count (name)>0)
			{
			
				MapPtr = p->find (name);
				TempArmour.Defense[NumInVector] = atoi (MapPtr->second.c_str());
			}
		
		}
		
		MapPtr = p->find("CanBuiltedIn");
		TempArmour.CanBuiltedIn = atoi(MapPtr->second.c_str());
		MapPtr = p->find("NumOfBuiltedInSlots");
		TempArmour.NumOfBuiltedInSlots = atoi(MapPtr->second.c_str());
		MapPtr = p->find("BuiltInType");
		TempArmour.BuiltInType = atoi(MapPtr->second.c_str());
		MapPtr = p->find ("CharCode");
		TempArmour.CharCode = atoi (MapPtr->second.c_str());
		MapPtr = p->find ("ColorVisible");
		TempArmour.ColorVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
		MapPtr = p->find ("ColorNotVisible");
		TempArmour.ColorNotVisible = strtoul (MapPtr->second.c_str(), NULL, 16);
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
	if (WeaponFromLevel[Id].Ammo.size() >0)
		WeaponFromLevel[Id].Ammo.pop_back();
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