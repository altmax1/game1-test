#include "StdAfx.h"
#include "Beast.h"

using namespace std;

using namespace luabridge;



Beast::Beast(void)
{
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


// ------------------------------ Getters and Setters -----------------------

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
		NextStep.pop_front();
		return a;
	}
