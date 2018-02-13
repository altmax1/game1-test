#include "StdAfx.h"
#include "Bestiary.h"
#include "Game.h"
#include "LuaAdapter.h"

using namespace std;
using namespace luabridge;

Bestiary::Bestiary(void)
{
	FillCreatures ();
}


Bestiary::~Bestiary(void)
{
}

void Bestiary::FillCreatures ()
{
	char *temp = new char [4];
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
		MapPtr = MyCreatures[i].find ("MaxHP");
		MyBeast.SetMaxHP(atoi (MapPtr->second.c_str()));
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
		
		for (int a = 2; a <=10; a++)
		{
			int NumInVector = a-1;
			_itoa (a, temp, 10);
			string name2 = temp;
			string name3 = "Defense";
			string name = name3+name2;
			if (MyCreatures[i].count(name.c_str()) > 0)
			{
				MapPtr = MyCreatures[i].find(name.c_str());
				MyBeast.SetDefenseAdvansed(atoi(MapPtr->second.c_str()), a);

			}
			else
				MyBeast.SetDefenseAdvansed(0, a);
					
		}

		for (int a = 1; a <= 10; a++)
		{
			int MyID, MyChance, MyMaxCount, MyMinCount;
			_itoa(a, temp, 10);
			string name2 = temp;
			string name3 = "ItemID";
			string name = name3 + name2;
			if (MyCreatures[i].count(name.c_str()) > 0)
			{
				MapPtr = MyCreatures[i].find(name.c_str());
				MyID = atoi(MapPtr->second.c_str());

				name3 = "ItemChance";
				name = name3 + name2;
				if (MyCreatures[i].count(name.c_str()) > 0)
				{
					MapPtr = MyCreatures[i].find(name.c_str());
					MyChance = atoi(MapPtr->second.c_str());
				}
				else
					MyChance = 100;

				name3 = "ItemMaxCount";
				name = name3 + name2;
				if (MyCreatures[i].count(name.c_str()) > 0)
				{
					MapPtr = MyCreatures[i].find(name.c_str());
					MyMaxCount = atoi(MapPtr->second.c_str());
				}
				else
					MyMaxCount = 100;

				name3 = "ItemMinCount";
				name = name3 + name2;
				if (MyCreatures[i].count(name.c_str()) > 0)
				{
					MapPtr = MyCreatures[i].find(name.c_str());
					MyMinCount = atoi(MapPtr->second.c_str());
				}
				else
					MyMinCount = 100;

				MyBeast.SetItemAfterDeath(MyChance, MyID, MyMaxCount, MyMinCount);

			}
			

		}
		

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
		MapPtr = MyCreatures[i].find ("MaxAttack");
		MyBeast.SetMaxAttack (1,atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("MinAttack");
		MyBeast.SetMinAttack (1,atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("AttackType");
		MyBeast.SetAttackType (1,atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find("AttackRange");
		MyBeast.SetAttackRange(1, atoi(MapPtr->second.c_str()));

		if (MyCreatures[i].count("MaxAttack2") > 0)
		{
			MapPtr = MyCreatures[i].find("MaxAttack2");
			MyBeast.SetMaxAttack(2, atoi(MapPtr->second.c_str()));
		}
		else 
			MyBeast.SetMaxAttack(2, 0);
		if (MyCreatures[i].count("MinAttack2") > 0)
		{
			MapPtr = MyCreatures[i].find("MinAttack2");
			MyBeast.SetMinAttack(2, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetMinAttack(2, 0);
		if (MyCreatures[i].count("AttackType2") > 0)
		{
			MapPtr = MyCreatures[i].find("AttackType2");
			MyBeast.SetAttackType(2, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetAttackType(2, 0);
		if (MyCreatures[i].count("AttackRange2") > 0)
		{
			MapPtr = MyCreatures[i].find("AttackRange2");
			MyBeast.SetAttackRange(2, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetAttackRange(2, 0);

		if (MyCreatures[i].count("MaxAttack3") > 0)
		{
			MapPtr = MyCreatures[i].find("MaxAttack3");
			MyBeast.SetMaxAttack(3, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetMaxAttack(3, 0);
		if (MyCreatures[i].count("MinAttack3") > 0)
		{
			MapPtr = MyCreatures[i].find("MinAttack3");
			MyBeast.SetMinAttack(3, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetMinAttack(3, 0);
		if (MyCreatures[i].count("AttackType3") > 0)
		{
			MapPtr = MyCreatures[i].find("AttackType3");
			MyBeast.SetAttackType(3, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetAttackType(3, 0);
		if (MyCreatures[i].count("AttackRange3") > 0)
		{
			MapPtr = MyCreatures[i].find("AttackRange3");
			MyBeast.SetAttackRange(3, atoi(MapPtr->second.c_str()));
		}
		else
			MyBeast.SetAttackRange(3, 0);
		MapPtr = MyCreatures[i].find ("RangeOfSight");
		MyBeast.SetRangeOfSight (atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("ID");
		MyBeast.SetID(atoi (MapPtr->second.c_str()));
		ExistingBeastID.insert (MyBeast.GetID());
		MapPtr = MyCreatures[i].find ("CharCode");
		MyBeast.SetCharCode ( atoi (MapPtr->second.c_str()));
		MapPtr = MyCreatures[i].find ("ColorVisible");
		MyBeast.SetColorVisible (strtoul (MapPtr->second.c_str(), NULL, 16));
		MapPtr = MyCreatures[i].find ("ColorNotVisible");
		MyBeast.SetColorNotVisible (strtoul (MapPtr->second.c_str(), NULL, 16));
		MapPtr = MyCreatures[i].find ("Speed");
		MyBeast.SetSpeed (atoi (MapPtr->second.c_str()));
		Creatures.resize (MyBeast.GetID()+1);
		Creatures[i] = MyBeast;
	}
delete [] temp;
}

void Bestiary::MakeCreature (int ID, int x, int y)

{	
	if (CheckBeastID (ID) == 0)
		return;
	int NumOfBeast;
	if (DeadBeasts.empty())
	{
		BeastsOfLevel.push_back(Creatures[ID]);
		NumOfBeast = BeastsOfLevel.size()-1;
	}
	else if (DeadBeasts.size()>0)
	{
		set<int>::iterator p;
		p = DeadBeasts.begin();
		NumOfBeast = *p;
		DeadBeasts.erase (p);
		BeastsOfLevel[NumOfBeast] = Creatures[ID];

	}
	int size = BeastsOfLevel.size();
	BeastsOfLevel[NumOfBeast].SetCoordX (x);
	BeastsOfLevel[NumOfBeast].SetCoordY (y);
	BeastsOfLevel[NumOfBeast].SetID (ID);
	BeastsOfLevel[NumOfBeast].SetNumInVector(NumOfBeast);
	Game * MyGame;
	MyGame = Game::GetGameInstance();
	level *MyLevel;
	MyLevel = MyGame->GetLevel();
	int LevelNum = MyLevel->GetLevelNum();
	BeastsOfLevel[NumOfBeast].SetCoordZ(LevelNum);
	MyLevel->SetCreature (NumOfBeast, x, y);
	
	return;
}

void Bestiary::MakeCreatures ()
{
	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\MakeCreatures.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef MakeCrs = getGlobal(L, "MakeCreatures");
    //
	try {
            MakeCrs (Luaad);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
}

void Bestiary::RemoveCreature (int Num)
{
	int x = BeastsOfLevel[Num].GetCoordX();
	int y = BeastsOfLevel[Num].GetCoordY();
	//BeastsOfLevel.erase (BeastsOfLevel.begin()+Num);
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	level *MyLevel;
	MyLevel = MyGame->GetLevel();
	MyLevel->RemoveCreature (x,y);
	
	return;

}

Beast* Bestiary::GetCreatureFromLevel (int Num)
{
	return &BeastsOfLevel[Num];
}

void Bestiary::MakeBeastsMove ()
{
	int size = BeastsOfLevel.size();
	for (int i = 0; i < size; i++)
	{
		BeastsOfLevel[i].MakeMove();	
	}
	return;
}

void Bestiary::SaveBestiary()
{
	ofstream Out(".\\Files\\save\\bestiary.sav", ios::binary | ios::out);
	int Size;
	Size = DeadBeasts.size();
	Out.write((char*)&Size, sizeof Size);
	for (auto a : DeadBeasts)
	{
		Out.write((char*)&a, sizeof a);
	}
	Size = ExistingBeastID.size();
	Out.write((char*)&Size, sizeof Size);
	for (auto a : ExistingBeastID)
	{
		Out.write((char*)&a, sizeof a);
	}
	Size = BeastsOfLevel.size();
	Out.write((char*)&Size, sizeof Size);
	for (auto &a : BeastsOfLevel)
	{
		a.SaveCreature(Out);
	}
	

}

void Bestiary::LoadBestiary()
{
	ifstream in(".\\Files\\Save\\bestiary.sav", ios::binary | ios::in);
	int Size;
	int tempint;
	DeadBeasts.clear();
	ExistingBeastID.clear();
	BeastsOfLevel.clear();
	in.read((char*)&Size, sizeof Size);
	for (int i = 0; i < Size; i++)
	{
		in.read((char*)&tempint, sizeof tempint);
		DeadBeasts.insert(tempint);
	}
	in.read((char*)&Size, sizeof Size);
	for (int i = 0; i < Size; i++)
	{
		in.read((char*)&tempint, sizeof tempint);
		ExistingBeastID.insert(tempint);
	}
	in.read((char*)&Size, sizeof Size);
	for (int i = 0; i < Size; i++)
	{
		Beast tempbeast;
		tempbeast.LoadCreature(in);
		BeastsOfLevel.push_back(tempbeast);
	}
}

void Bestiary::SetIsDead (int Num, int a)
{
	BeastsOfLevel[Num].SetIsDead (a);
	return;
}

int Bestiary::GetIsDead (int Num)
{
	return BeastsOfLevel[Num].GetIsDead ();
}

void Bestiary::SetID (int Num, int ID)
{
	BeastsOfLevel[Num].SetID (ID);
	return;
}

int Bestiary::GetID (int Num)
{
	return BeastsOfLevel[Num].GetID ();
}

void Bestiary::SetCoordX (int Num, int x)
{
	BeastsOfLevel[Num].SetCoordX (x);
	return;
}

int Bestiary::GetCoordX (int Num)
{
	return BeastsOfLevel[Num].GetCoordX ();
}

void Bestiary::SetCoordY (int Num, int y)
{
	BeastsOfLevel[Num].SetCoordY (y);
	return;
}

int Bestiary::GetCoordZ(int Num)
{
	return BeastsOfLevel[Num].GetCoordZ();
}

void Bestiary::SetCoordZ(int Num, int Z)
{
	BeastsOfLevel[Num].SetCoordZ(Z);
}

int Bestiary::GetCoordY (int Num)
{
	return BeastsOfLevel[Num].GetCoordY();
}

void Bestiary::SetHP (int Num, int HP)
{
	BeastsOfLevel[Num].SetHP (HP);
	return;
}

int Bestiary::GetHP (int Num)
{
	return BeastsOfLevel[Num].GetHP();
}

void Bestiary::SetMaxHP (int Num, int HP)
{
	BeastsOfLevel[Num].SetMaxHP (HP);
	return;
}

int Bestiary::GetMaxHP (int Num)
{
	return BeastsOfLevel[Num].GetMaxHP();
}

void Bestiary::SetDefense (int Num, int Def)
{
	BeastsOfLevel[Num].SetDefense (Def);
	return;
}

int Bestiary::GetDefense (int Num)
{
	return BeastsOfLevel[Num].GetDefence();
}

int Bestiary::GetDefenseAdvansed (int Num, int TypeOfDef)
{
	return BeastsOfLevel[Num].GetDefenseAdvansed (TypeOfDef);
}

void Bestiary::SetDefenseAdvansed (int Num, int TypeOfDef, int Def)
{
	BeastsOfLevel[Num].SetDefenseAdvansed (Def, TypeOfDef);
}

void Bestiary::SetDex (int Num, int Dex)
{
	BeastsOfLevel[Num].SetDex (Dex);
	return;
}

int Bestiary::GetDex (int Num)
{
	return BeastsOfLevel[Num].GetDex();
}

void Bestiary::SetStr (int Num, int Str)
{
	BeastsOfLevel[Num].SetStr (Str);
	return;
}

int Bestiary::GetStr (int Num)
{
	return BeastsOfLevel[Num].GetStr();
}

int Bestiary::GetCharCode (int Num)
{
	return BeastsOfLevel[Num].GetCharCode ();
}

void Bestiary::SetCharCode (int Num, int Code)
{
	BeastsOfLevel[Num].SetCharCode(Code);
	return;
}

int Bestiary::GetColorVisible (int Num)
{
	return BeastsOfLevel[Num].GetColorVisible ();
}

void Bestiary::SetColorVisible (int Num, int Color)
{
	BeastsOfLevel[Num].SetColorVisible (Color);
	return;
}

int Bestiary::GetColorNotVisible (int Num)
{
	return BeastsOfLevel[Num].GetColorNotVisible ();
}

void Bestiary::SetColorNotVisible (int Num, int Color)
{
	BeastsOfLevel[Num].SetColorNotVisible (Color);
	return;
}

int Bestiary::GetSpeed (int Num)
{
	return BeastsOfLevel[Num].GetSpeed();
}

void Bestiary::SetSpeed (int Num, int Speed)
{
	BeastsOfLevel[Num].SetSpeed (Speed);
	return;
}

int Bestiary::CheckBeastID (int ID)
{
	set <int>::iterator p;
	p = ExistingBeastID.find (ID);
	if (p == ExistingBeastID.end())
		return 0;
	else
		return 1;
}