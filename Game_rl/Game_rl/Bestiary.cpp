#include "StdAfx.h"
#include "Bestiary.h"
#include "Game.h"
#include "LuaAdapter.h"

using namespace std;
Bestiary::Bestiary(void)
{
	FillCreatures ();
}


Bestiary::~Bestiary(void)
{
}

void Bestiary::FillCreatures ()
{
	vector <map<string, string>> MyCreatures;
	FileContent MyFile;
	X_File::X_ReadFile ((LPCTSTR) L".\\Files\\Beasts.ini", MyFile);
	X_File::X_ParseIniFile (MyFile, MyCreatures);
	for (int i = 0; i < MyCreatures.size(); i++)
	{
		Beast MyBeast;
		map<string,string>::iterator MapPtr;
		MapPtr = MyCreatures[i].find ("Name");
		MyBeast.SetName (MapPtr->second);
		MapPtr = MyCreatures[i].find ("RName");
		MyBeast.SetRName(MapPtr->second);
		MapPtr = MyCreatures[i].find ("RDesc");
		MyBeast.SetRDesc(MapPtr->second);
		MapPtr = MyCreatures[i].find ("HP");
		MyBeast.SetHP(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Energy");
		MyBeast.SetEnergy(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Speed");
		MyBeast.SetSpeed(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("RegenHP");
		MyBeast.SetRegenHP(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("RegenEnergy");
		MyBeast.SetRegenEnergy(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("LevelOfBeast");
		MyBeast.SetLevelOfBeast(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Defense");
		MyBeast.SetDefense(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Str");
		MyBeast.SetStr(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Dex");
		MyBeast.SetDex(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Fly");
		MyBeast.SetFly(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("FlyAble");
		MyBeast.SetFlyAble(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Sleep");
		MyBeast.SetSleep(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Active");
		MyBeast.SetActive(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Magic");
		MyBeast.SetMagic(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("Behavior");
		MyBeast.SetBehavior(atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("ID");
		int ID = (atoi (MapPtr->second.c_str()));

		Creatures.resize (ID+1);
		Creatures[i] = MyBeast;
	}
}

void Bestiary::PutCreatureInBOL (int ID)

{
	BeastsOfLevel.push_back(Creatures[ID]);
	return;
}

void Bestiary::MakeCreatures ()
{


}