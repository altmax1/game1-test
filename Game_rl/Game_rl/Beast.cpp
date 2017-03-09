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

void Beast::LuaReg ()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
    getGlobalNamespace(L).addFunction("SetHP", &Beast::SetHP);
	getGlobalNamespace(L).addFunction("SetCoordX", &Beast::SetCoordX);
	getGlobalNamespace(L).addFunction("SetCoordY", &Beast::SetCoordY);
}


// ------------------------------ Getters and Setters -----------------------
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
	int Beast::GetCoordX ()
	{
		return CoordX;
	}
	int Beast::GetCoordY ()
	{
		return CoordY;
	}
	void Beast::SetHP (int a)
{
	HP = a;
	return;
}
	int Beast::GetHP ()
	{
		return HP;
	}
	void Beast::SetEnergy (int a)
	{
		Energy = a;
		return;
	}
	int Beast::GetEnergy ()
	{
		return Energy;
	}
	void Beast::SetSpeed (int a)
	{
		Speed = a;
		return;
	}
	int Beast::GetSpeed ()
	{
		return Speed;
	}
	void Beast::SetRegenHP (int a)
	{
		RegenHP = a;
		return;
	}
	int Beast::GetRegenHp ()
	{
		return RegenHP;
	}
	void Beast::SetRegenEnergy (int a)
	{
		RegenEnergy = a;
		return;
	}
	int Beast::GetRegenEnergy ()
	{
		return RegenEnergy;
	}
	void Beast::SetLevelOfBeast (int a)
	{
		LevelOfBeast = a;
		return;
	}
	int Beast::GetLevelOfBeast ()
	{
		return LevelOfBeast;
	}
	void Beast::SetDefense (int a)
	{
		Defense = a;
		return;
	}
	int Beast::GetDefence ()
	{
		return Defense;
	}
	void Beast::SetDex (int a)
	{
		Dex = a;
		return;
	}
	int Beast::GetDex ()
	{
		return Dex;
	}
	void Beast::SetStr (int a)
	{
		Str = a;
		return;
	}
	int Beast::GetStr ()
	{
		return Str;
	}
	void Beast::SetFlyAble (int a)
	{
		FlyAble = a;
		return;
	}
	int Beast::GetFlyAble ()
	{
		return FlyAble;
	}
	void Beast::SetFly (int a)
	{
		Fly = a;
		return;
	}
	int Beast::GetFly ()
	{
		return Fly;
	}
	void Beast::SetSleep (int a)
	{
		Sleep = a;
		return;
	}
	int Beast::GetSleep ()
	{
		return Sleep;
	}
	void Beast::SetActive (int a)
	{
		Active = a;
		return;
	}
	int Beast::GetActive ()
	{
		return Active;
	}
	void Beast::SetMagic (int a)
	{
		Magic = a;
		return;	
	}
	int Beast::GetMagic ()
	{
		return Magic;
	}
	void Beast::SetBehavior (int a)
	{
		Behavior = a;
		return;
	}
	int Beast::GetBehavior ()
	{
		return Behavior;
	}
	void Beast::SetEffects (int a)
	{
		Effects.push_back (a);
		return;
	}
	int Beast::GetNumEffects ()
	{
		return Effects.size();
	}
	int Beast::GetEffectByNum (int a)
	{
		return Effects.at (a);
	}
	int Beast::FindEffectById (int ID)
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
		return NextStep.pop_front();
	}
