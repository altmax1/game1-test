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
	MyItems = MyGame->GetItems();
	MyInterface = MyGame->GetInterface();
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
			.addFunction ("GetBeastHP", &LuaAdapter::GetBeastHP)
			.addFunction ("SetBeastHP", &LuaAdapter::SetBeastHP)
			.addFunction ("GetBeastCoordX", &LuaAdapter::GetBeastCoordX)
			.addFunction ("GetBeastCoordY", &LuaAdapter::GetBeastCoordY)
			.addFunction ("SetBeastCoordX", &LuaAdapter::SetBeastCoordX)
			.addFunction ("SetBeastCoordY", &LuaAdapter::SetBeastCoordY)
			.addFunction ("GetBeastID", &LuaAdapter::GetBeastID)
			.addFunction ("SetBeastID", &LuaAdapter::SetBeastID)
			.addFunction ("GetBeastRName", &LuaAdapter::GetBeastRName)
			.addFunction ("SetBeastRName", &LuaAdapter::SetBeastRName)
			.addFunction ("GetBeastIsDead", &LuaAdapter::GetBeastIsDead)
			.addFunction ("SetBeastIsDead", &LuaAdapter::SetBeastIsDead)
			.addFunction ("GetBeastDefense", &LuaAdapter::GetBeastDefense)
			.addFunction ("SetBeastDefense", &LuaAdapter::SetBeastDefense)
			.addFunction ("GetBeastDefenseAdvansed", &LuaAdapter::GetBeastDefenseAdvansed)
			.addFunction ("SetBeastDefenseAdvansed", &LuaAdapter::SetBeastDefenseAdvansed)
			.addFunction ("GetBeastDex", &LuaAdapter::GetBeastDex)
			.addFunction ("SetBeastDex", &LuaAdapter::SetBeastDex)
			.addFunction ("GetBeastStr", &LuaAdapter::GetBeastStr)
			.addFunction ("SetBeastStr", &LuaAdapter::SetBeastStr)
			.addFunction ("GetDefenseOfSlot", &LuaAdapter::GetDefenseBySlot)
			.addFunction ("GetDefenseOfSlotAdvansed", &LuaAdapter::GetDefenseBySlotAdvansed)
			.addFunction ("GetIdByGamerSlot", &LuaAdapter::GetItemIdBySlot)
			.addFunction ("GetItemTypeById", &LuaAdapter::GetTypeById)
			.addFunction ("GetItemType2ById", &LuaAdapter::GetType2ById)
			.addFunction ("GetItemWeightById", &LuaAdapter::GetWeightById)
			.addFunction ("GetWeaponMaxDamage", &LuaAdapter::GetWeaponMaxDamage)
			.addFunction ("SetWeaponMaxDamage", &LuaAdapter::SetWeaponMaxDamage)
			.addFunction ("GetWeaponMinDamage", &LuaAdapter::GetWeaponMinDamage)
			.addFunction ("SetWeaponMinDamage", &LuaAdapter::SetWeaponMinDamage)
			.addFunction ("GetWeaponNeedsAmmo", &LuaAdapter::GetWeaponNeedsAmmo)
			.addFunction ("GetWeaponIsAmmo", &LuaAdapter::GetWeaponIsAmmo)
			.addFunction ("GetWeaponCalober", &LuaAdapter::GetWeaponCaliber)
			.addFunction ("GetWeaponAmmoQuantity", &LuaAdapter::GetWeaponAmmoQuantity)
			.addFunction ("SetWeaponAmmoQuantity", &LuaAdapter::SetWeaponAmmoQuantity)
			.addFunction ("GetWeaponCurrentAmmoQuantity", &LuaAdapter::GetWeaponCurrentAmmoQuantity)
			.addFunction ("GetItemQuality", &LuaAdapter::GetQuality)
			.addFunction ("SetItemQuality", &LuaAdapter::SetQuality)
			.addFunction ("GetIsDestroyed", &LuaAdapter::GetIsDestroyed)
			.addFunction ("SetIsDestroyed", &LuaAdapter::SetIsDestroyed)
			.addFunction ("GetWeaponRange", &LuaAdapter::GetWeaponRange)
			.addFunction ("SetWeaponRange", &LuaAdapter::SetWeaponRange)
			.addFunction ("GetWeaponBlastRadius", &LuaAdapter::GetWeaponBlastRadius)
			.addFunction ("SetWeaponBlastRadius", &LuaAdapter::SetWeaponBlastRadius)
			.addFunction ("GetWeaponNextAmmo", &LuaAdapter::GetWeaponNextAmmo)
			.addFunction ("UnloadWeapon", &LuaAdapter::UnloadWeapon)
			.addFunction ("ReloadWeapon", &LuaAdapter::ReloadWeapon)
			.addFunction ("SelectTarget", &LuaAdapter::SelectTarget)
			.addFunction ("GetWeaponShotsByStep", &LuaAdapter::GetWeaponShotsByStep)
			.addFunction ("SetWeaponShotsByStep", &LuaAdapter::SetWeaponShotsByStep)
			.addFunction ("WeaponMakeOneShot", &LuaAdapter::WeaponMakeOneShot)
			.addFunction ("GetKeyCode", &LuaAdapter::GetKeyCode)
			.addFunction ("PrintMessage", &LuaAdapter::PrintMessage)
			.addFunction ("PrintMessageNow", &LuaAdapter::PrintMessageNow)
			.addFunction ("GetMoves", &LuaAdapter::GetMoves)
			.addFunction ("GetGamerMoved", &LuaAdapter::GetGamerMoved)
			.addFunction ("SetGamerMoved", &LuaAdapter::SetGamerMoved)
			.addFunction ("ResetGamerMoved", &LuaAdapter::ResetGamerMoved)
			.addFunction ("AddEffectOnCell", &LuaAdapter::AddEffectOnCell)
			.addFunction ("GetNumOfEffectsOnCell", &LuaAdapter::GetNumOfEffectsOnCell)
			.addFunction ("CheckEffects", &LuaAdapter::CheckEffectsOnCell)
			.addFunction ("GetEffectTypeOnCell", &LuaAdapter::GetTypeOfEffectOnCell)
			.addFunction ("GetEffectPowerOnCell", &LuaAdapter::GetPowerOfEffectOnCell)
			.addFunction ("GetEffectTimeOnCell", &LuaAdapter::GetTimeOfEffectOnCell)
			.addFunction ("EffectTOnCellimeDec", &LuaAdapter::EffectOnCellTimeDec)
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
		.addProperty ("CharCode", &Beast::GetCharCode, &Beast::SetCharCode)
		.addProperty ("MovePoints", &Beast::GetMovePoints, &Beast::SetMovePoints)
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

string LuaAdapter::GetBeastRName (int Num)
{
	return MyBestiary->GetRName (Num);
}

void LuaAdapter::SetBeastRName (int Num, string Name)
{
	MyBestiary->SetRName (Num, Name);
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

int LuaAdapter::GetDefenseBySlotAdvansed (int NumOfSlot, int NumOfDefense)
{
	return MyGamer->GetDefenseFromEquipmentAdvansed (NumOfSlot, NumOfDefense);
}

int LuaAdapter::GetItemIdBySlot (int Slot)
{
	return MyGamer->GetItemIdBySlot (Slot);
}

int LuaAdapter::GetWeightById (int Id)
{
	return MyItems->GetWeightById (Id);
}

int LuaAdapter::GetTypeById (int Id)
{
	return MyItems->GetTypeById (Id);
}

int LuaAdapter::GetType2ById (int Id)
{
	return MyItems->GetType2ById (Id);
}

int LuaAdapter::GetWeaponMaxDamage (int Id)
{
	return MyItems->GetWeaponMaxDamage (Id);
}

void LuaAdapter::SetWeaponMaxDamage (int Id, int MaxDamage)
{
	MyItems->SetWeaponMaxDamage (Id, MaxDamage);
}

int LuaAdapter::GetWeaponMinDamage (int Id)
{
	return MyItems->GetWeaponMinDamage (Id);
}

void LuaAdapter::SetWeaponMinDamage (int Id, int MinDamage)
{
	MyItems->SetWeaponMinDamage (Id,MinDamage);
}

int LuaAdapter::GetWeaponNeedsAmmo (int Id)
{
	return MyItems->GetWeaponNeedsAmmo (Id);
}

int LuaAdapter::GetWeaponIsAmmo (int Id)
{
	return MyItems->GetWeaponIsAmmo(Id);
}

int LuaAdapter::GetWeaponCaliber (int Id)
{
	return MyItems->GetWeaponCaliber(Id);
}

int LuaAdapter::GetWeaponAmmoQuantity (int Id)
{
	return MyItems->GetWeaponAmmoQuantity (Id);
}

void LuaAdapter::SetWeaponAmmoQuantity (int Id, int Quantity)
{
	MyItems->SetWeaponAmmoQuantity(Id,Quantity);
}

int LuaAdapter::GetWeaponCurrentAmmoQuantity (int Id)
{
	return MyItems->GetWeaponCurrentAmmoQuantity (Id);
}

int LuaAdapter::GetQuality (int Id)
{
	return MyItems->GetQuality (Id);
}

void LuaAdapter::SetQuality (int Id, int Quality)
{
	MyItems->SetQuality (Id, Quality);
}

int LuaAdapter::GetIsDestroyed (int Id)
{
	return MyItems->GetIsDestroyed (Id);
}

void LuaAdapter::SetIsDestroyed (int Id, int a)
{
	MyItems->SetIsDestroyed (Id, a);
}

int LuaAdapter::GetWeaponRange (int Id)
{
	return MyItems->GetWeaponRange (Id);
}

void LuaAdapter::SetWeaponRange (int Id, int Range)
{
	MyItems->SetWeaponRange (Id, Range);
}

int LuaAdapter::GetWeaponBlastRadius (int Id)
{
	return MyItems->GetWeaponBlastRadius (Id);
}

void LuaAdapter::SetWeaponBlastRadius (int Id, int Radius)
{
	MyItems->SetWeaponBlastRadius (Id, Radius);
}

int LuaAdapter::GetWeaponNextAmmo (int Id)
{
	return MyItems->GetWeaponNextAmmo (Id);
}

void LuaAdapter::UnloadWeapon (int Id)
{
	MyGamer->UnloadWeapon();
}

void LuaAdapter::ReloadWeapon (int Id)
{
	MyGamer->ReloadWeapon();
}

int LuaAdapter::SelectTarget ()
{
	return MyInterface->SelectTarget();
}

void LuaAdapter::PrintMessage (string MyMessage)
{
	MyInterface->SetMessage (MyMessage);
}

int LuaAdapter::GetKeyCode ()
{
	return terminal_read();
}

void LuaAdapter::PrintMessageNow (string Message)
{
	MyInterface->PrintMessageNow (Message);
}

int LuaAdapter::GetWeaponShotsByStep (int Id)
{
	return MyItems->GetWeaponShotPerStep (Id);
}

void LuaAdapter::SetWeaponShotsByStep (int Id, int Shots)
{
	MyItems->SetWeaponShotPerStep (Id, Shots);
	return;
}

void LuaAdapter::WeaponMakeOneShot(int Id)
{
	MyItems->WeaponMakeOneShot(Id);
}

int LuaAdapter::GetMoves ()
{
	return MyGame->GetMoves ();
}

int LuaAdapter::GetGamerMoved ()
{
	return MyGame->GetPlayerMoved();
}

void LuaAdapter::SetGamerMoved ()
{
	MyGame->SetPlayerMoved ();
}

void LuaAdapter::ResetGamerMoved ()
{
	MyGame->ResetPlayerMoved ();
}

void LuaAdapter::AddEffectOnCell (int x, int y, int Type, int Power, int Time)
{
	MyLevel->AddEffect (x,y,Type,Power,Time);
}
int LuaAdapter::GetNumOfEffectsOnCell (int x, int y)
{
	return MyLevel->GetNumOfEffects (x,y);
}
void LuaAdapter::CheckEffectsOnCell (int x, int y)
{
	MyLevel->CheckEffects(x,y);
}
int LuaAdapter::GetTypeOfEffectOnCell (int x, int y, int Num)
{
	return MyLevel->GetEffectTypeByNum (x,y,Num);
}
int LuaAdapter::GetPowerOfEffectOnCell (int x, int y, int Num)
{
	return MyLevel->GetEffectPowerByNum (x,y,Num);
}
int LuaAdapter::GetTimeOfEffectOnCell (int x, int y, int Num)
{
	return MyLevel->GetEffectTimeByNum (x,y,Num);
}
void LuaAdapter::EffectOnCellTimeDec (int x, int y)
{
	MyLevel->EffectTimeDesc (x,y);
}
void LuaAdapter::SetBeastDefenseAdvansed (int NumOfBeast,int NumOfDefense, int Def)
{
	MyBestiary->SetDefenseAdvansed (NumOfBeast, NumOfDefense, Def);
}
int LuaAdapter::GetBeastDefenseAdvansed (int NumOfBeast, int NumOfDefense)
{
	return MyBestiary->GetDefenseAdvansed (NumOfBeast, NumOfDefense);
}