#include "StdAfx.h"
#include "LuaAdapter.h"

using namespace std;
using namespace luabridge;
LuaAdapter::LuaAdapter(void)
{
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyGamer = MyGame->GetGamer();
	MyBestiary = MyGame->GetBestiary();
	
}


LuaAdapter::~LuaAdapter(void)
{
}
void LuaAdapter::LuaDesc (lua_State *L)
{
	
	
	getGlobalNamespace(L)
			.beginClass <LuaAdapter> ("Game")
			.addFunction ("GetTileBaseType", &LuaAdapter::GetTileBaseType)
			.addFunction ("GetLevelWidth", &LuaAdapter::GetLevelWidth)
			.addFunction ("GetLevelHeight", &LuaAdapter::GetLevelHeight)
			.addFunction ("CreateTheBeast", &LuaAdapter::CreateTheBeast)
			.addFunction ("MyRandom", &LuaAdapter::GetRandom)
			.addFunction ("PathFind", &LuaAdapter::PathFind)
			.addFunction ("GetCellPassable", &LuaAdapter::GetCellPassable)
			.addFunction ("SetCellPassable", &LuaAdapter::SetPassable)
			.addFunction ("GetBeastNumber", &LuaAdapter::GetBeastNumber)
			.addFunction ("RemoveCreature", &LuaAdapter::RemoveCreature)
			.addFunction ("SetCreature", &LuaAdapter::SetCreature)
			.addFunction ("AttackBeastByNum", &LuaAdapter::AttackBeastByNum)
			.addFunction ("LOS", &LuaAdapter::LOS)
			.addFunction ("PathFind", &LuaAdapter::PathFind)
			.addFunction ("GetBeastHP", &LuaAdapter::GetBeastHP)
			.addFunction ("SetBeastHP", &LuaAdapter::SetBeastHP)
			.addFunction ("GetBeastCoordX", &LuaAdapter::GetBeastCoordX)
			.addFunction ("GetBeastCoordY", &LuaAdapter::GetBeastCoordY)
			.addFunction ("SetBeastCoordX", &LuaAdapter::SetBeastCoordX)
			.addFunction ("SetBeastCoordY", &LuaAdapter::SetBeastCoordY)
			.addFunction ("GetBeastID", &LuaAdapter::GetBeastID)
			.addFunction ("SetBeastID", &LuaAdapter::SetBeastID)
			.addFunction ("GetBeastIsDead", &LuaAdapter::GetBeastIsDead)
			.addFunction ("SetBeastIsDead", &LuaAdapter::SetBeastIsDead)
			.addFunction ("GetBeastDefense", &LuaAdapter::GetBeastDefense)
			.addFunction ("SetBeastDefense", &LuaAdapter::SetBeastDefense)
			.addFunction ("GetBeastDex", &LuaAdapter::GetBeastDex)
			.addFunction ("SetBeastDex", &LuaAdapter::SetBeastDex)
			.addFunction ("GetBeastStr", &LuaAdapter::GetBeastStr)
			.addFunction ("SetBeastStr", &LuaAdapter::SetBeastStr)
			.addFunction ("GetDefenseOfSlot", &LuaAdapter::GetDefenseBySlot)
			.addFunction ("GetDefense2OfSlot", &LuaAdapter::GetDefense2BySlot)
			.addFunction ("GetDefense3OfSlot", &LuaAdapter::GetDefense3BySlot)
			.addFunction ("GetDefense4OfSlot", &LuaAdapter::GetDefense4BySlot)
			.addFunction ("GetDefense5OfSlot", &LuaAdapter::GetDefense5BySlot)
			.addProperty ("GamerX", &LuaAdapter::GetGamerX, &LuaAdapter::SetGamerX)
			.addProperty ("GamerY", &LuaAdapter::GetGamerY, &LuaAdapter::SetGamerY)
			.addProperty ("GamerHP", &LuaAdapter::GetGamerHP, &LuaAdapter::SetGamerHP)
			.addProperty ("GamerMaxHP", &LuaAdapter::GetGamerMaxHP, &LuaAdapter::SetGamerMaxHP)
			.addProperty ("GamerStr", &LuaAdapter::GetGamerStr, &LuaAdapter::SetGamerStr)
			.addProperty ("GamerDex", &LuaAdapter::GetGamerDex, &LuaAdapter::SetGamerDex)
			.addProperty ("GamerEnergy", &LuaAdapter::GetGamerEnergy, &LuaAdapter::SetGamerEnergy)
			.addProperty ("GamerRangeOfSight", &LuaAdapter::GetGamerRangeOfSight, &LuaAdapter::SetGamerRangeOfSight)
			.addProperty ("GamerMaxEnergy", &LuaAdapter::GetGamerMaxEnergy, &LuaAdapter::SetGamerMaxEnergy)
			.addProperty ("GamerDefense", &LuaAdapter::GetGamerDefense, &LuaAdapter::SetGamerDefense)
			.addProperty ("GamerDefense2", &LuaAdapter::GetGamerDefense2, &LuaAdapter::SetGamerDefense2)
			.addProperty ("GamerDefense3", &LuaAdapter::GetGamerDefense3, &LuaAdapter::SetGamerDefense3)
			.addProperty ("GamerDefense4", &LuaAdapter::GetGamerDefense4, &LuaAdapter::SetGamerDefense4)
			.addProperty ("GamerDefense5", &LuaAdapter::GetGamerDefense5, &LuaAdapter::SetGamerDefense5)
			.addProperty ("GamerRegenHP", &LuaAdapter::GetGamerRegenHP, &LuaAdapter::SetGamerRegenHP)
			.addProperty ("GamerRegenEnergy", &LuaAdapter::GetGamerRegenEnergy, &LuaAdapter::SetGamerRegenEnergy)
		.endClass();

	getGlobalNamespace (L)
		.beginClass <Beast> ("Beast")
		.addFunction ("Move", &Beast::MoveCreature)
		.addProperty ("CoordX", &Beast::GetCoordX, &Beast::SetCoordX)
		.addProperty ("CoordY", &Beast::GetCoordY, &Beast::SetCoordY)
		.addProperty ("HP", &Beast::GetHP,&Beast::SetHP)
		.addProperty ("Dex", &Beast::GetDex, &Beast::SetDex)
		.addProperty ("Energy", &Beast::GetEnergy, &Beast::SetEnergy)
		.addProperty ("RangeOfSight", &Beast::GetRangeOfSight, &Beast::SetRangeOfSight)
		.addProperty ("Defense", &Beast::GetDefence, &Beast::SetDefense)
		.addProperty ("Speed", &Beast::GetSpeed, &Beast::SetSpeed)
		.addProperty ("RegenHP", &Beast::GetRegenHp, &Beast::SetRegenHP)
		.addProperty ("RegenEnergy", &Beast::GetRegenEnergy, &Beast::SetRegenEnergy)
		.addProperty ("Str", &Beast::GetRegenEnergy, &Beast::SetRegenEnergy)
		.addProperty ("Behavior", &Beast::GetBehavior, &Beast::SetBehavior)
		.addProperty ("Sleeping", &Beast::GetSleep, &Beast::SetSleep)
		.addProperty ("Active", &Beast::GetActive, &Beast::SetActive)
		.addProperty ("MaxAttack", &Beast::GetMaxAttack, &Beast::SetMaxAttack)
		.addProperty ("MinAttack", &Beast::GetMinAttack, &Beast::SetMinAttack)
		.addProperty ("AttackType", &Beast::GetAttackType, &Beast::SetAttackType)
		.addProperty ("IsDead", &Beast::GetIsDead, &Beast::SetIsDead)
		.addFunction ("GetNextStep", &Beast::GetNextStep)
		.addFunction ("SetNextStep", &Beast::SetNextStep)
		.addFunction ("ClearAllSteps", &Beast::ClearAllSteps)
		.addFunction ("GetStepsSize", &Beast::GetNextStepSize)
		.addFunction ("RemoveFirstStep", &Beast::RemoveFirstStep)
		.endClass();
		
}


char  LuaAdapter::GetTileBaseType (int x, int y) const
{
	return MyLevel->GetBaseType (x,y);
}

int LuaAdapter::GetLevelWidth ()
{
	return (MyLevel->GetLevelWidth());
}

int LuaAdapter::GetLevelHeight()
{
	return (MyLevel->GetLevelHeight());
}

int LuaAdapter::GetGamerX () const 
{
	return MyGamer->GetCoordX ();
}
int LuaAdapter::GetGamerY () const 
{
	return MyGamer->GetCoordY ();
}
void LuaAdapter::SetGamerX (int a)
{
	MyGamer->SetCoordX (a);
	return;
}
void LuaAdapter::SetGamerY (int a)
{
	MyGamer->SetCoordY (a);
	return;
}
void LuaAdapter::CreateTheBeast (int ID, int x, int y)
{
	MyBestiary->MakeCreature (ID, x, y);
	return;
}

int LuaAdapter::GetRandom (int a)
{
	return (rand() %a);
}

int LuaAdapter::PathFind (int StartX, int StartY, int EndX, int EndY)
{
	return MyLevel->PathFind (StartX, StartY, EndX, EndY);
}

int LuaAdapter::GetCellPassable (int x, int y)
{
	return MyLevel->GetPassable (x,y);
}

void LuaAdapter::SetPassable (int x, int y, int passable)
{
	MyLevel->SetPassable (x,y,passable);
	return;
}

int LuaAdapter::GetGamerHP () const
{
	return MyGamer->GetHP();
}
void LuaAdapter::SetGamerHP (int a)
{
	MyGamer->SetHP (a);
	return;
}
int LuaAdapter::GetGamerStr () const
{
	return MyGamer->GetStr();	
}
void LuaAdapter::SetGamerStr (int a)
{
	MyGamer->SetStr (a);
	return;
}
int LuaAdapter::GetGamerMaxHP () const
{
	return MyGamer->GetMaxHP();
}
void LuaAdapter::SetGamerMaxHP (int a)
{
	MyGamer->SetMaxHP (a);
	return;
}
int LuaAdapter::GetGamerDex () const
{
	return MyGamer->GetDex ();
}
void LuaAdapter::SetGamerDex (int a)
{
	MyGamer->SetDex (a);
	return;
}
int LuaAdapter::GetGamerEnergy () const
{
	return MyGamer->GetEnergy();
}
void LuaAdapter::SetGamerEnergy (int a)
{
	MyGamer->SetEnergy(a);
	return;
}

int LuaAdapter::GetGamerRangeOfSight () const
{
	return MyGamer->GetRangeOfSight();
}

void LuaAdapter::SetGamerRangeOfSight (int a)
{
	MyGamer->SetRangeOfSight (a);
	return;
}
int LuaAdapter::GetGamerMaxEnergy () const
{
	return MyGamer->GetMaxEnergy();
}
void LuaAdapter::SetGamerMaxEnergy (int a)
{
	MyGamer->SetMaxEnergy(a);
	return;
}
int LuaAdapter::GetGamerDefense () const
{
	return MyGamer->GetDefense();
}
void LuaAdapter::SetGamerDefense (int a)
{
	MyGamer->SetDefense (a);
	return;
}
int LuaAdapter::GetGamerDefense2 () const
{
	return MyGamer->GetDefense2();
}
void LuaAdapter::SetGamerDefense2 (int a)
{
	MyGamer->SetDefense2 (a);
	return;
}int LuaAdapter::GetGamerDefense3 () const
{
	return MyGamer->GetDefense3();
}
void LuaAdapter::SetGamerDefense3 (int a)
{
	MyGamer->SetDefense3 (a);
	return;
}int LuaAdapter::GetGamerDefense4 () const
{
	return MyGamer->GetDefense4();
}
void LuaAdapter::SetGamerDefense4 (int a)
{
	MyGamer->SetDefense4 (a);
	return;
}int LuaAdapter::GetGamerDefense5 () const
{
	return MyGamer->GetDefense5();
}
void LuaAdapter::SetGamerDefense5 (int a)
{
	MyGamer->SetDefense5 (a);
	return;
}



int LuaAdapter::GetGamerRegenHP () const
{
	return MyGamer->GetRegenHP ();
}
void LuaAdapter::SetGamerRegenHP (int a)
{
	MyGamer->SetRegenHP (a);
	return;
}
int LuaAdapter::GetGamerRegenEnergy () const
{
	return MyGamer->GetRegenEnergy();
}
void LuaAdapter::SetGamerRegenEnergy (int a)
{
	MyGamer->SetRegenEnergy(a);
	return;
}

int LuaAdapter::GetBeastNumber (int x, int y)
{
	return MyLevel->GetCreature (x,y);
}

void LuaAdapter::RemoveCreature (int Num)
{
	MyBestiary->RemoveCreature (Num);
	return;
}

void LuaAdapter::SetCreature (int x, int y, int Num)
{
	MyLevel->SetCreature (Num, x, y);
	return;
}

void LuaAdapter::AttackBeastByNum (int Num)
{
	using namespace luabridge;

	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\GamerMove.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef GamerAttack = getGlobal(L, "GamerAttack");
	  //
	try {
            GamerAttack (Luaad, MyBestiary->GetCreatureFromLevel (Num), Num);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }

	
}

int LuaAdapter::LOS (int x1, int y1, int x2, int y2)
{
	return MyLevel->LOS (x1, y1, x2, y2);
}

void LuaAdapter::SetBeastHP (int Num, int HP)
{
	MyBestiary->SetHP (Num, HP);
	return;
}

int LuaAdapter::GetBeastHP (int Num)
{
	return MyBestiary->GetHP (Num);
}

void LuaAdapter::SetBeastCoordX (int Num, int x)
{
	MyBestiary->SetCoordX (Num, x);
	return;
}

void LuaAdapter::SetBeastCoordY (int Num, int y)
{
	MyBestiary->SetCoordY (Num,y);
	return;
}

int LuaAdapter::GetBeastCoordX (int Num)
{
	return MyBestiary->GetCoordX(Num);
}

int LuaAdapter::GetBeastCoordY (int Num)
{
	return MyBestiary->GetCoordY (Num);
}

void LuaAdapter::SetBeastID (int Num, int ID)
{
	MyBestiary->SetID (Num,ID);
	return;
}

int LuaAdapter::GetBeastID (int Num)
{
	return MyBestiary->GetID (Num);
}

void LuaAdapter::SetBeastIsDead (int Num, int a)
{
	MyBestiary->SetIsDead (Num, a);
	return;
}

int LuaAdapter::GetBeastIsDead (int Num)
{
	return MyBestiary->GetIsDead (Num);
}

void LuaAdapter::SetBeastDefense (int Num, int Def)
{
	MyBestiary->SetDefense (Num,Def);
	return;
}

int LuaAdapter::GetBeastDefense (int Num)
{
	return MyBestiary->GetDefense (Num);
}

void LuaAdapter::SetBeastDex (int Num, int Dex)
{
	MyBestiary->SetDex (Num,Dex);
	return;
}

int LuaAdapter::GetBeastDex (int Num)
{
	return MyBestiary->GetDex (Num);
}

void LuaAdapter::SetBeastStr (int Num, int Str)
{
	MyBestiary->SetStr (Num, Str);
	return;
}

int LuaAdapter::GetBeastStr (int Num)
{
	return MyBestiary->GetStr (Num);
}

int LuaAdapter::GetDefenseBySlot (int NumOfSlot)
{
	return MyGamer->GetDefenseFromEquipment (NumOfSlot);
}

int LuaAdapter::GetDefense2BySlot (int NumOfSlot)
{
	return MyGamer->GetDefense2FromEquipment (NumOfSlot);
}

int LuaAdapter::GetDefense3BySlot (int NumOfSlot)
{
	return MyGamer->GetDefense3FromEquipment (NumOfSlot);
}

int LuaAdapter::GetDefense4BySlot (int NumOfSlot)
{
	return MyGamer->GetDefense4FromEquipment (NumOfSlot);
}

int LuaAdapter::GetDefense5BySlot (int NumOfSlot)
{
	return MyGamer->GetDefense5FromEquipment (NumOfSlot);
}