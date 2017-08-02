#include "StdAfx.h"
#include "Beast.h"
#include "LuaAdapter.h"

using namespace std;

using namespace luabridge;



Beast::Beast(void)
{
	IsDead = 0;
	MovePoints = 10;
	
}


Beast::~Beast(void)
{
}

void Beast::LuaReg (lua_State* L)
{
	getGlobalNamespace(L)
		.beginClass <Beast>("Beast")
		.addProperty ("ID", &Beast::GetID, &Beast::SetID)
		.addProperty ("CoordX", &Beast::GetCoordX, &Beast::SetCoordX)
		.addProperty ("CoordY", &Beast::GetCoordY, &Beast::SetCoordY)
		.addProperty ("Name", &Beast::GetName)
		.addProperty ("HP", &Beast::GetHP, &Beast::SetHP)
		.addProperty ("Energy", &Beast::GetEnergy, &Beast::SetEnergy)
		.addProperty ("Speed", &Beast::GetSpeed, &Beast::SetSpeed)
		.addProperty ("RegenHP", &Beast::GetRegenHp, &Beast::SetRegenHP)
		.addProperty ("RangeOfSight", &Beast::GetRangeOfSight, &Beast::SetRangeOfSight)
		.addProperty ("RegenEnergy", &Beast::GetRegenEnergy, &Beast::SetRegenEnergy)
		.addProperty ("LevelOfBeast", &Beast::GetLevelOfBeast)
		.addProperty ("Def", &Beast::GetDefence, &Beast::SetDefense)
		.addProperty ("Dex", &Beast::GetDex, &Beast::SetDex)
		.addProperty ("Str", &Beast::GetStr, &Beast::SetStr)
		.addProperty ("FlyAble", &Beast::GetFlyAble, &Beast::SetFlyAble)
		.addProperty ("IsFlying", &Beast::GetFly, &Beast::SetFly)
		.addProperty ("IsSleaping", &Beast::GetSleep, &Beast::SetSleep)
		.addProperty ("IsActive", &Beast::GetActive, &Beast::SetActive)
		.addProperty ("Behavior", &Beast::GetBehavior, &Beast::SetBehavior)
		.addProperty ("IsMagic", &Beast::GetMagic, &Beast::SetMagic)
		.addProperty ("NumOfEffects", &Beast::GetNumEffects)
		.addProperty ("CharCode", &Beast::GetCharCode, &Beast::SetCharCode)
		.addProperty ("MovePoints", &Beast::GetMovePoints, &Beast::SetMovePoints)
		.addFunction ("EffectByNum", &Beast::GetEffectByNum)
		.addFunction ("FindEffectByID", &Beast::FindEffectById)
		.addFunction ("AffEffect", &Beast::SetEffects)
		.addFunction ("GetNextStep", &Beast::GetNextStep)
		.addFunction ("SetNextStep", &Beast::SetNextStep)
		.addFunction ("ClearAllSteps", &Beast::ClearAllSteps)
		.endClass();

}

void Beast::MakeMove()
{
	if (IsDead == 1)
		return;
	if (HP <= 0)
		{
			Game *MyGame;
			MyGame= Game::GetGameInstance();
			level *MyLevel;
			MyLevel = MyGame->GetLevel ();
			IsDead = 1;
			MyLevel->RemoveCreature (CoordX,CoordY);
			Bestiary *MyBestiary;
			MyBestiary = MyGame->GetBestiary();
			MyBestiary->SetDeadBeast (NumInVector);
			return;
		}
	using namespace luabridge;

	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\BeastMove.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef BeastMove = getGlobal(L, "BeastMove");
	  //
	try {
            BeastMove (Luaad, this);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
	return;
}

int Beast::MoveCreature (int x, int y, int MyMode)
{
	if (IsDead == 1)
		return 0;
	Game *MyGame;
	MyGame= Game::GetGameInstance();
	level *MyLevel;
	MyLevel = MyGame->GetLevel ();
	int NumOfCreature = MyLevel->GetCreature (CoordX,CoordY);

	if (MyMode == 0)
	{
		const int Passable = MyLevel->GetPassable (x,y);
		if (Passable == 1)
		{
			MyLevel->RemoveCreature (CoordX,CoordY);
			CoordX = x;
			CoordY = y;
			MyLevel->SetCreature (NumOfCreature, CoordX, CoordY);
			return 1;
		}
	
	}

	if (MyMode == 1)
	{
		int NextX = CoordX+x;
		int NextY = CoordY+y;
		if ((NextX<0)||(NextY<0)||(NextX > (MyLevel->GetLevelWidth())-1)||(NextY > (MyLevel->GetLevelHeight())-1))
			return 0;
		const int Passable = MyLevel->GetPassable(x,y);
		if (Passable == 1)
		{
			MyLevel->RemoveCreature (CoordX,CoordY);
			CoordX = NextX;
			CoordY = NextY;
			MyLevel->SetCreature (NumOfCreature, CoordX, CoordY);
			return 1;
		}

	}
	
	return 0;
}

void Beast::SaveCreature(ofstream & MyStream)
{
	MyStream.write((char*)&IsDead, sizeof IsDead);
	MyStream.write((char*)&ID, sizeof ID);
	MyStream.write((char*)&NumInVector, sizeof NumInVector);
	MyStream.write((char*)&CoordX, sizeof CoordX);
	MyStream.write((char*)&CoordY, sizeof CoordY);
	MyStream.write((char*)&CoordZ, sizeof CoordZ);
	int size;
	size = Name.size();
	MyStream.write((char*)&size, sizeof size);
	MyStream.write(Name.c_str(), size);
	size = RName.size();
	MyStream.write((char*)&size, sizeof size);
	MyStream.write(RName.c_str(), size);
	size = RDesc.size();
	MyStream.write((char*)&size, sizeof size);
	MyStream.write(RDesc.c_str(), size);
	MyStream.write((char*)&HP, sizeof HP);
	MyStream.write((char*)&MaxHP, sizeof MaxHP);
	MyStream.write((char*)&Energy, sizeof Energy);
	MyStream.write((char*)&RangeOfSight, sizeof RangeOfSight);
	MyStream.write((char*)&Speed, sizeof Speed);
	MyStream.write((char*)&RegenHP, sizeof RegenHP);
	MyStream.write((char*)&RegenEnergy, sizeof RegenEnergy);
	MyStream.write((char*)&LevelOfBeast, sizeof LevelOfBeast);
	MyStream.write((char*)Defense, (sizeof Defense[0]) * 10);
	MyStream.write((char*)MaxAttack, (sizeof MaxAttack[0]) * 3);
	MyStream.write((char*)MinAttack, (sizeof MinAttack[0]) * 3);
	MyStream.write((char*)AttackType, (sizeof AttackType[0]) * 3);
	MyStream.write((char*)AttackRange, (sizeof AttackRange[0]) * 3);
	MyStream.write((char*)&Dex, sizeof Dex);
	MyStream.write((char*)&Str, sizeof Str);
	char TempChar = 0;
	if (FlyAble)
		TempChar | 0b00000001;
	if (Fly)
		TempChar | 0b00000010;
	if (Sleep)
		TempChar | 0b00000100;
	if (Active)
		TempChar | 0b00001000;
	if (Magic)
		TempChar | 0b00010000;
	MyStream.write((char*)&TempChar, sizeof TempChar);
	MyStream.write((char*)&Behavior, sizeof Behavior);
	size = Effects.size();
	MyStream.write((char*)&size, sizeof size);
	int temp;
	for (int i = 0; i < size; i++)
	{
		temp = Effects[i];
		MyStream.write((char*)&temp, sizeof temp);
		temp = EffectsTime[i];
		MyStream.write((char*)&temp, sizeof temp);
	}
	size = NextStep.size();
	MyStream.write((char*)&size, sizeof size);
	auto p = NextStep.begin();
	while (p != NextStep.end())
	{
		temp = *p;
		MyStream.write((char*)&temp, sizeof temp);
		p++;
	}
	MyStream.write((char*)&CharCode, sizeof CharCode);
	MyStream.write((char*)&ColorVisible, sizeof ColorVisible);
	MyStream.write((char*)&ColorNotVisible, sizeof ColorNotVisible);
	MyStream.write((char*)&MovePoints, sizeof MovePoints);
}

void Beast::LoadCreature(std::ifstream & MyStream)
{
	MyStream.read((char*)&IsDead, sizeof IsDead);
	MyStream.read((char*)&ID, sizeof ID);
	MyStream.read((char*)&NumInVector, sizeof NumInVector);
	MyStream.read((char*)&CoordX, sizeof CoordX);
	MyStream.read((char*)&CoordY, sizeof CoordY);
	MyStream.read((char*)&CoordZ, sizeof CoordZ);
	int size;
	char *tempchar;
	MyStream.read((char*)&size, sizeof size);
	tempchar = new char(size + 1);
	MyStream.read(tempchar, size);
	Name = tempchar;
	delete[] tempchar;
	MyStream.read((char*)&size, sizeof size);
	tempchar = new char(size + 1);
	MyStream.read(tempchar, size);
	RName = tempchar;
	delete[] tempchar;
	MyStream.read((char*)&size, sizeof size);
	tempchar = new char(size + 1);
	MyStream.read(tempchar, size);
	RDesc = tempchar;
	delete[] tempchar;
	MyStream.read((char*)&HP, sizeof HP);
	MyStream.read((char*)&MaxHP, sizeof MaxHP);
	MyStream.read((char*)&Energy, sizeof Energy);
	MyStream.read((char*)&RangeOfSight, sizeof RangeOfSight);
	MyStream.read((char*)&Speed, sizeof Speed);
	MyStream.read((char*)&RegenHP, sizeof RegenHP);
	MyStream.read((char*)&RegenEnergy, sizeof RegenEnergy);
	MyStream.read((char*)&LevelOfBeast, sizeof LevelOfBeast);
	MyStream.read((char*)Defense, (sizeof Defense[0]) * 10);
	MyStream.read((char*)MaxAttack, (sizeof MaxAttack[0]) * 3);
	MyStream.read((char*)MinAttack, (sizeof MinAttack[0]) * 3);
	MyStream.read((char*)AttackType, (sizeof AttackType[0]) * 3);
	MyStream.read((char*)AttackRange, (sizeof AttackRange[0]) * 3);
	MyStream.read((char*)&Dex, sizeof Dex);
	MyStream.read((char*)&Str, sizeof Str);
	char TempChar;
	MyStream.read((char*)&TempChar, sizeof TempChar);
	if (TempChar & 0b00000001)
		FlyAble = 1;
	else
		FlyAble = 0;
	if (TempChar & 0b00000010)
		Fly = 1;
	else
		Fly = 0;
	if (TempChar & 0b00000100)
		Sleep = 1;
	else
		Sleep = 0;
	if (TempChar & 0b00001000)
		Active = 1;
	else
		Active = 0;
	if (TempChar & 0b00010000)
		Magic = 1;
	else
		Magic = 0;
	MyStream.read((char*)&Behavior, sizeof Behavior);
	MyStream.read((char*)&size, sizeof size);
	int temp;
	for (int i = 0; i < size; i++)
	{
		MyStream.read((char*)&temp, sizeof temp);
		Effects[i] = temp;
		MyStream.read((char*)&temp, sizeof temp);
		EffectsTime[i] = temp;
	}
	MyStream.read((char*)&size, sizeof size);
	for (int i = 0; i < size; i++)
	{
		MyStream.read((char*)&temp, sizeof temp);
		NextStep.push_back(temp);
	}
	MyStream.read((char*)&CharCode, sizeof CharCode);
	MyStream.read((char*)&ColorVisible, sizeof ColorVisible);
	MyStream.read((char*)&ColorNotVisible, sizeof ColorNotVisible);
	MyStream.read((char*)&MovePoints, sizeof MovePoints);
}

// ------------------------------ Getters and Setters -----------------------

void Beast::SetIsDead (int a)
{
	if (a==0)
		IsDead = 0;
	if (a>0)
		IsDead = 1;
}

int Beast::GetIsDead () const
{
	return IsDead;
}
void Beast::SetID (int a)
{
	ID = a;
	return;
}

int Beast::GetID () const
{
	return ID;
}

	void Beast::SetCoordX (int a) 
	{
		CoordX = a;
		return;
	}
	void Beast::SetCoordY (int a)
	{
		CoordY = a;
		return;
	}
	void Beast::SetCoordZ(int a)
	{
		CoordZ = a;
		return;
	}
	int Beast::GetCoordX () const 
	{
		return CoordX;
	}
	int Beast::GetCoordY () const
	{
		return CoordY;
	}
	int Beast::GetCoordZ() const
	{
		return CoordZ;
	}
	void Beast::SetName (std::string S)
	{
		Name = S;
		return;
	}
	std::string Beast::GetName () const
	{
		return Name;
	}
	void Beast::SetRName (std::string S)
	{
		RName = S;
		return;
	}
	std::string Beast::GetRName () const
	{
		return RName;
	}
	void Beast::SetRDesc (std::string S)
	{
		RDesc = S;
		return;
	}
	std::string Beast::GetRDesc () const
	{
		return RDesc;

	}
	void Beast::SetHP (int a)
{
	HP = a;
	return;
}
	int Beast::GetHP () const
	{
		return HP;
	}
	void Beast::SetEnergy (int a)
	{
		Energy = a;
		return;
	}
	int Beast::GetEnergy () const
	{
		return Energy;
	}

	void Beast::SetRangeOfSight (int a)
	{
		RangeOfSight = a;
		return;
	}

	int Beast::GetRangeOfSight () const
	{
		return RangeOfSight;
	}

	void Beast::SetSpeed (int a)
	{
		Speed = a;
		return;
	}
	int Beast::GetSpeed () const
	{
		return Speed;
	}
	void Beast::SetRegenHP (int a)
	{
		RegenHP = a;
		return;
	}
	int Beast::GetRegenHp () const
	{
		return RegenHP;
	}
	void Beast::SetRegenEnergy (int a)
	{
		RegenEnergy = a;
		return;
	}
	int Beast::GetRegenEnergy () const
	{
		return RegenEnergy;
	}
	void Beast::SetLevelOfBeast (int a)
	{
		LevelOfBeast = a;
		return;
	}
	int Beast::GetLevelOfBeast () const
	{
		return LevelOfBeast;
	}
	void Beast::SetDefense (int a)
	{
		Defense[0] = a;
		return;
	}
	int Beast::GetDefence () const
	{
		return Defense[0];
	}

	void Beast::SetDefenseAdvansed (int Def, int NumOfDef)
	{
		if (NumOfDef>=1 && NumOfDef <=10)
			Defense[NumOfDef-1] = Def;
		return;
	}

	int Beast::GetDefenseAdvansed (int NumOfDef)
	{
		if (NumOfDef>=1 && NumOfDef <=10)
			return Defense[NumOfDef-1];
		return 0;
	}

	void Beast::SetMaxAttack (int NumOfAttack,int a)
	{
		if (NumOfAttack>=1 && NumOfAttack <=3)
			MaxAttack[NumOfAttack-1] = a;
		return;
	}
	int Beast::GetMaxAttack (int NumOfAttack) const
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			return MaxAttack[NumOfAttack-1];
	}
	void Beast::SetMinAttack (int NumOfAttack, int a)
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			MinAttack[NumOfAttack-1] = a;
		return;
	}
	int Beast::GetMinAttack (int NumOfAttack) const
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			return MinAttack[NumOfAttack-1];
	}
	void Beast::SetAttackType (int NumOfAttack,int a)
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			AttackType[NumOfAttack-1] = a;
		return;
	}
	int Beast::GetAttackType (int NumOfAttack) const
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			return AttackType[NumOfAttack-1];
	}
	void Beast::SetAttackRange(int NumOfAttack, int Range)
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			AttackRange[NumOfAttack-1] = Range;
		return;
	}
	int Beast::GetAttackRange(int NumOfAttack) const
	{
		if (NumOfAttack >= 1 && NumOfAttack <= 3)
			return AttackRange[NumOfAttack-1];
	}
	void Beast::SetDex (int a)
	{
		Dex = a;
		return;
	}
	int Beast::GetDex () const
	{
		return Dex;
	}
	void Beast::SetStr (int a)
	{
		Str = a;
		return;
	}
	int Beast::GetStr () const
	{
		return Str;
	}
	void Beast::SetFlyAble (int a)
	{
		FlyAble = a;
		return;
	}
	int Beast::GetFlyAble () const
	{
		return FlyAble;
	}
	void Beast::SetFly (int a)
	{
		Fly = a;
		return;
	}
	int Beast::GetFly () const
	{
		return Fly;
	}
	void Beast::SetSleep (int a)
	{
		Sleep = a;
		return;
	}
	int Beast::GetSleep () const
	{
		return Sleep;
	}
	void Beast::SetActive (int a)
	{
		Active = a;
		return;
	}
	int Beast::GetActive () const
	{
		return Active;
	}
	void Beast::SetMagic (int a)
	{
		Magic = a;
		return;	
	}
	int Beast::GetMagic () const
	{
		return Magic;
	}
	void Beast::SetBehavior (int a)
	{
		Behavior = a;
		return;
	}
	int Beast::GetBehavior () const
	{
		return Behavior;
	}
	void Beast::SetEffects (int a)
	{
		Effects.push_back (a);
		return;
	}
	int Beast::GetNumEffects () const
	{
		return Effects.size();
	}
	int Beast::GetEffectByNum (int a) const
	{
		return Effects.at (a);
	}
	int Beast::FindEffectById (int ID) const
	{
		for (int i=0; i< Effects.size(); i++)
		{
			if (Effects[i] == ID)
				return i;
		}
		return 1000000;
	}
	void Beast::SetEffectsTime (int time, int NumOfEffect)
	{
		EffectsTime[NumOfEffect] = time;
		return;
	}
	int Beast::GetEffectsTime (int NumOfEffect)
	{
		return EffectsTime [NumOfEffect];
	}
	void Beast::SetNextStep (int step)
	{
		NextStep.push_back (step);
		return;
	}
	void Beast::ClearAllSteps ()
	{
		NextStep.clear();
		return;
	}
	int Beast::GetNextStep ()
	{
		list <int>::iterator p;
		p = NextStep.begin();
		int a = *p;
		//NextStep.pop_front();
		return a;
	}

	void Beast::RemoveFirstStep ()
	{
		if (NextStep.size()>0)
			NextStep.pop_front();
		return;
	}

	int Beast::GetNextStepSize ()
	{
		return NextStep.size();
	}

	int Beast::GetCharCode () const
	{
		return CharCode;
	}

	void Beast::SetCharCode (int Code)
	{
		CharCode = Code;
		return;
	}

	int Beast::GetColorVisible () const
	{
		return ColorVisible;
	}

	void Beast::SetColorVisible (int Color)
	{
		ColorVisible = Color;
		return;
	}

	int Beast::GetColorNotVisible () const
	{
		return ColorNotVisible;
	}

	void Beast::SetColorNotVisible (int Color)
	{
		ColorNotVisible = Color;
		return;
	}

	int Beast::GetMovePoints () const
	{
		return MovePoints;
	}

	void Beast::SetMovePoints (int Points)
	{
		MovePoints = Points;
		return;
	}
