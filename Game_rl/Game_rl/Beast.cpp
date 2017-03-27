#include "StdAfx.h"
#include "Beast.h"
#include "LuaAdapter.h"

using namespace std;

using namespace luabridge;



Beast::Beast(void)
{
	IsDead = 0;
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
	int Beast::GetCoordX () const 
	{
		return CoordX;
	}
	int Beast::GetCoordY () const
	{
		return CoordY;
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
		Defense = a;
		return;
	}
	int Beast::GetDefence () const
	{
		return Defense;
	}

	void Beast::SetMaxAttack (int a)
	{
		MaxAttack = a;
		return;
	}
	int Beast::GetMaxAttack () const
	{
		return MaxAttack;
	}
	void Beast::SetMinAttack (int a)
	{
		MinAttack = a;
		return;
	}
	int Beast::GetMinAttack () const 
	{
		return MinAttack;
	}
	void Beast::SetAttackType (int a)
	{
		AttackType = a;
		return;
	}
	int Beast::GetAttackType () const
	{
		return AttackType;
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
