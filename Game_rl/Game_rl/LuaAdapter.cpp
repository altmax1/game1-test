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
	MyLog = MyGame->GetLog();

}

LuaAdapter::~LuaAdapter(void)
{
}

int LuaAdapter::GetConnectorType(int ConnectorNum)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorType(ConnectorNum);
}
int LuaAdapter::GetLevelNumOfRooms()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetRoomsCount();
}
int LuaAdapter::GetRoomLefX(int Num)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetRooomLeftX(Num);
}
int LuaAdapter::GetRoomUpY(int Num)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetRoomUpY(Num);
}
int LuaAdapter::GetRoomWidth(int Num)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetRoomWidth(Num);
}
int LuaAdapter::GetRoomHeight(int Num)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetRoomHeight(Num);
}
int LuaAdapter::GetLevelTile(int x, int y)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetTile(x, y);
}
void LuaAdapter::SetLevelTile(int x, int y, int Tile)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetTile(x, y, Tile);
}
void LuaAdapter::PutItemInInventory(int x, int y)
{
	MyGame = Game::GetGameInstance();
	MyGamer = MyGame->GetGamer();
	MyInventory = MyGamer->GetInventory();
	MyInventory->PutItemInInventory(x, y);
}
int LuaAdapter::GetMemoryCell(int Num)
{
	return MyGame->GetMemotyCell(Num);
}
void LuaAdapter::SetMemotyCell(int Num, int Value)
{
	MyGame->SetMemoryCell(Num,Value);
}

int LuaAdapter::GetLevelIndex()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetLevelIndex();
}

void LuaAdapter::SetLevelIndex(int index)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetLevelIndex(index);
}

string LuaAdapter::GetLevelName()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetLevelName();
}

void LuaAdapter::SetLevelName(string Name)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetLevelName(Name);
}

void LuaAdapter::SaveGame()
{
	MyGame->SaveGame();
}

void LuaAdapter::LTerminal_clear()
{
	terminal_clear();
	return;
}

void LuaAdapter::LTerminal_refresh()
{
	terminal_refresh();
	return;
}

void LuaAdapter::LTerminal_print(int x, int y, string text)
{
	terminal_print(x, y, text.c_str());
	return;
}

void LuaAdapter::LTerminal_print_ext(int x, int y, int width, int height, string text)
{
	terminal_print_ext(x, y, width, height, TK_ALIGN_DEFAULT, text.c_str());
	return;
}

void LuaAdapter::LTerminal_put(int x, int y, int code)
{
	terminal_put(x, y, code);
	return;
}

void LuaAdapter::LTerminal_color(int code)
{
	terminal_color(code);
	return;

}

int LuaAdapter::LTerminal_read()
{
	return terminal_read();
}

int LuaAdapter::FindItemByID(int ID)
{
	return MyInventory->FindItemByID(ID);
}

int LuaAdapter::GetNumOfSlots()
{
	return MyInventory->GetNumOfSlots();
}

int LuaAdapter::GetQuantityByNum(int Num)
{
	return MyInventory->GetQuantityByNum(Num);
}

int LuaAdapter::GetQuantityByID(int ID)
{
	return MyInventory->GetQuantityByID(ID);

}

int LuaAdapter::CreateUniqueItem(int ID)
{
	return MyItems->GetIdForCreation(ID);
}

void LuaAdapter::PutItemInInventory2(int Id, int Num)
{
	bool st;
	st = MyItems->GetStackable(Id);
	MyInventory->PutItemInVector(Id, st, Num);
	return;
}

void LuaAdapter::RemoveItemFromInventory(int num, int Quantity)
{
	MyInventory->RemoveItemFromVector(num, Quantity);
	return;
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
			.addFunction ("GetBeastCoordZ", &LuaAdapter::GetBeastCoordZ)
			.addFunction ("SetBeastCoordX", &LuaAdapter::SetBeastCoordX)
			.addFunction ("SetBeastCoordY", &LuaAdapter::SetBeastCoordY)
			.addFunction ("SetBeastCoordZ", &LuaAdapter::SetBeastCoordZ)
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
			.addFunction ("GetGamerDefenseAdvansed", &LuaAdapter::GetGamerDefenseAdvansed)
			.addFunction("SetGamerDefenseAdvansed", &LuaAdapter::SetGamerDefenseAdvansed)
			.addFunction("GetGamerBaseDefense", &LuaAdapter::GetGamerBaseDefense)
			.addFunction("SetGamerBaseDefense", &LuaAdapter::SetGamerBaseDefense)
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
			.addFunction ("GetWeaponCaliber", &LuaAdapter::GetWeaponCaliber)
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
			.addFunction ("GetWeaponAfterEffectType", &LuaAdapter::GetWeaponAfterEffectType)
			.addFunction ("GetWeaponAfterEffectTime", &LuaAdapter::GetWeaponAfterEffectTime)
			.addFunction ("GetWeaponAfterEffectPower", &LuaAdapter::GetWeaponAfterEffectPower)
			.addFunction ("GetInputString", &LuaAdapter::GetInputString)
			.addFunction ("GetInputNumber", &LuaAdapter::GetInputNumber)
			.addFunction ("GetInputKey", &LuaAdapter::GetInputKey)
			.addFunction ("CheckItemID", &LuaAdapter::CheckItemID)
			.addFunction ("CheckBeastID", &LuaAdapter::CheckBeastID)
			.addFunction ("AddItemOnLevel", &LuaAdapter::AddItemOnLevel)
			.addFunction ("AddMessageToLog", &LuaAdapter::AddMessageToLog)
			.addFunction ("AddToDevLog", &LuaAdapter::AddDevLog)
			.addFunction ("SetWeaponMaxDamage2", &LuaAdapter::SetWeaponMaxDamage2)
			.addFunction ("SetWeaponMaxDamage3", &LuaAdapter::SetWeaponMaxDamage3)
			.addFunction ("SetWeaponMinDamage2", &LuaAdapter::SetWeaponMinDamage2)
			.addFunction ("SetWeaponMinDamage3", &LuaAdapter::SetWeaponMinDamage3)
			.addFunction ("GetWeaponMaxDamage2", &LuaAdapter::GetWeaponMaxDamage2)
			.addFunction ("GetWeaponMaxDamage3", &LuaAdapter::GetWeaponMaxDamage3)
			.addFunction ("GetWeaponMinDamage2", &LuaAdapter::GetWeaponMinDamage2)
			.addFunction ("GetWeaponMinDamage3", &LuaAdapter::GetWeaponMinDamage3)
			.addFunction ("SetWeaponDamage2Type", &LuaAdapter::SetWeaponDamage2Type)
			.addFunction ("SetWeaponDamage3Type", &LuaAdapter::SetWeaponDamage3Type)
			.addFunction ("GetWeaponDamage2Type", &LuaAdapter::GetWeaponDamage2Type)
			.addFunction ("GetWeaponDamage3Type", &LuaAdapter::GetWeaponDamage3Type)
			.addFunction ("GetWeaponNeedsEnergy", &LuaAdapter::GetWeaponNeedsEnergy)
			.addFunction ("GetWeaponEnergyPerUse", &LuaAdapter::GetWeaponEnergyPerUse)
			.addFunction ("GetWeaponFacultEnergy", &LuaAdapter::GetWeaponEnergyFacultative)
			.addFunction ("LevelRefresh", &LuaAdapter::LevelRefresh)
			.addFunction ("CreateNewLevel", &LuaAdapter::CreateNewLevel)
			.addFunction ("SetCurrentLevel", &LuaAdapter::SetCurrentLevel)
			.addFunction("MakeNewConnector", &LuaAdapter::MakeNewConnector)
			.addFunction("GetLevelNum", &LuaAdapter::GetLevelNum)
			.addFunction("GetConnectorNum", &LuaAdapter::GetConnectorNum)
			.addFunction("SetConnectorNum", &LuaAdapter::SetConnectorNum)
			.addFunction("MakeNewConnector", &LuaAdapter::MakeNewConnector)
			.addFunction("SetConnectorDestX", &LuaAdapter::SetConnectorDestX)
			.addFunction("SetConnectorDestY", &LuaAdapter::SetConnectorDestY)
			.addFunction("SetConnectorDestZ", &LuaAdapter::SetConnectorDestZ)
			.addFunction("GetConnectorDestX", &LuaAdapter::GetConnectorDestX)
			.addFunction("GetConnectorDestY", &LuaAdapter::GetConnectorDestY)
			.addFunction("GetConnectorDestZ", &LuaAdapter::GetConnectorDestZ)
			.addFunction("SetConnectorIsCompleted", &LuaAdapter::SetConnectorComplete)
			.addFunction("GetConnectorIsCompleted", &LuaAdapter::GetConnectorComplete)
			//.addFunction ("GetConnectorIsCompleted", &LuaAdapter::GetConnectorComplete)
			.addFunction("GetConnectorType", &LuaAdapter::GetConnectorType)
			.addFunction("GetConnectorName", &LuaAdapter::GetConnectorName)
			.addFunction("GetLevelNumOfRooms", &LuaAdapter::GetLevelNumOfRooms)
			.addFunction ("GetRoomLeftX", &LuaAdapter::GetRoomLefX)
			.addFunction("GetRoomUpY", &LuaAdapter::GetRoomUpY)
			.addFunction("GetRoomWidth", &LuaAdapter::GetRoomWidth)
			.addFunction("GetRoomHeight", &LuaAdapter::GetRoomHeight)
			.addFunction("GetLevelTile", &LuaAdapter::GetLevelTile)
			.addFunction("SetLevelTile", &LuaAdapter::SetLevelTile)
			.addFunction("PutItemInInventoryFromCell", &LuaAdapter::PutItemInInventory)
			.addFunction("GetMemoryCell", &LuaAdapter::GetMemoryCell)
			.addFunction("SetMemotyCell", &LuaAdapter::SetMemotyCell)
			.addFunction ("GetLevelIndex", &LuaAdapter::GetLevelIndex)
			.addFunction("SetLevelIndex", &LuaAdapter::SetLevelIndex)
			.addFunction("GetLevelName", &LuaAdapter::GetLevelName)
			.addFunction("SetLevelName", &LuaAdapter::SetLevelName)
			.addFunction("SaveGame", &LuaAdapter::SaveGame)
			.addFunction("Terminal_clear", &LuaAdapter::LTerminal_clear)
			.addFunction("Terminal_refresh", &LuaAdapter::LTerminal_refresh)
			.addFunction("Terminal_print", &LuaAdapter::LTerminal_print)
			.addFunction("Terminal_put", &LuaAdapter::LTerminal_put)
			.addFunction("Terminal_print_ext", &LuaAdapter::LTerminal_print_ext)
			.addFunction("Terminal_color", &LuaAdapter::LTerminal_color)
			.addFunction("Terminal_read", &LuaAdapter::LTerminal_read)
			.addFunction("FindItemByID", &LuaAdapter::FindItemByID)
			.addFunction("GetNumOfSlots", &LuaAdapter::GetNumOfSlots)
			.addFunction("GetQuantityByNum", &LuaAdapter::GetQuantityByNum)
			.addFunction("GetQuantityByID", &LuaAdapter::GetQuantityByID)
			.addFunction("CreateUniqueItem", &LuaAdapter::CreateUniqueItem)
			.addFunction("PutItemInInventory2", &LuaAdapter::PutItemInInventory2)
			.addFunction("RemoveItemFromInventory", &LuaAdapter::RemoveItemFromInventory)
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
			.addProperty ("GamerRegenHP", &LuaAdapter::GetGamerRegenHP, &LuaAdapter::SetGamerRegenHP)
			.addProperty ("GamerRegenEnergy", &LuaAdapter::GetGamerRegenEnergy, &LuaAdapter::SetGamerRegenEnergy)
		.endClass();

	getGlobalNamespace (L)
		.beginClass <Beast> ("Beast")
		.addFunction ("Move", &Beast::MoveCreature)
		.addFunction ("GetMaxAttack", &Beast::GetMaxAttack)
		.addFunction ("GetMinAttack", &Beast::GetMinAttack)
		.addFunction ("GetAttackType", &Beast::GetAttackType)
		.addFunction ("GetAttackRange", &Beast::GetAttackRange)
		.addProperty ("CoordX", &Beast::GetCoordX, &Beast::SetCoordX)
		.addProperty ("CoordY", &Beast::GetCoordY, &Beast::SetCoordY)
		.addProperty ("CoordZ", &Beast::GetCoordZ, &Beast::SetCoordZ)
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
		.addProperty ("IsDead", &Beast::GetIsDead, &Beast::SetIsDead)
		.addProperty ("CharCode", &Beast::GetCharCode, &Beast::SetCharCode)
		.addProperty ("MovePoints", &Beast::GetMovePoints, &Beast::SetMovePoints)
		.addProperty ("RName", &Beast::GetRName, &Beast::SetRName)
		.addFunction ("GetNextStep", &Beast::GetNextStep)
		.addFunction ("SetNextStep", &Beast::SetNextStep)
		.addFunction ("ClearAllSteps", &Beast::ClearAllSteps)
		.addFunction ("GetStepsSize", &Beast::GetNextStepSize)
		.addFunction ("RemoveFirstStep", &Beast::RemoveFirstStep)
		.endClass();

	getGlobalNamespace(L)
		.beginClass <level>("Level")
		.addFunction ("MakeDungeon", &level::LevelCreate)
		.addFunction ("GetLevelNum", &level::GetLevelNum)
		.addFunction ("GetConnectorNum", &level::GetConnectorNum)
		.addFunction ("SetConnectorNum", &level::SetConnectorNum)
		.addFunction ("MakeNewConnector", &level::MakeNewConnector)
		.addFunction ("SetConnectorDestX", &level::SetConnectorDestX)
		.addFunction ("SetConnectorDestY", &level::SetConnectorDestY)
		.addFunction ("SetConnectorDestZ", &level::SetConnectorDestZ)
		.addFunction("GetConnectorDestX", &level::GetConnectorDestX)
		.addFunction ("GetConnectorDestY", &level::GetConnectorDestY)
		.addFunction ("GetConnectorDestZ", &level::GetConnectorDestZ)
		.addFunction ("SetConnectorIsComleted", &level::SetConnectorIsComleted)
		.addFunction ("GetConnectorIsComleted", &level::GetConnectorIsComleted)
		.addFunction ("GetConnectorType", &level::GetConnectorType)
		.addFunction ("GetConnectorName", &level::GetConnectorName)
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
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	
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
int LuaAdapter::GetGamerDefenseAdvansed(int Num)
{
	return MyGamer->GetDefenseAdvansed (Num);
}
void LuaAdapter::SetGamerDefenseAdvansed(int Num, int Def)
{
	MyGamer->SetDefenseAdvansed(Num, Def);
}
int LuaAdapter::GetGamerBaseDefense(int NumOfDefense)
{
	return MyGamer->GetBaseDefenseAdvansed(NumOfDefense);
}
void LuaAdapter::SetGamerBaseDefense(int NumOfDefense, int Def)
{
	MyGamer->SetBaseDefenseAdvansed(NumOfDefense, Def);
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

void LuaAdapter::SetBeastCoordZ(int Num, int z)
{
	MyBestiary->SetCoordZ(Num, z);
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

int LuaAdapter::GetBeastCoordZ(int Num)
{
	return MyBestiary->GetCoordZ(Num);
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

int LuaAdapter::GetWeaponAfterEffectType (int Id)
{
	return MyItems->GetWeaponAfterEffectType (Id);
}

int LuaAdapter::GetWeaponAfterEffectTime (int Id)
{
	return MyItems->GetWeaponAfterEffectTime (Id);
}

int LuaAdapter::GetWeaponAfterEffectPower (int Id)
{
	return MyItems->GetWeaponAfterEffectPower (Id);
}

string LuaAdapter::GetInputString ()
{
	return MyInterface->GetInputString();
}

int LuaAdapter::GetInputKey ()
{
	return MyInterface->GetInputKey();
}

int LuaAdapter::CheckItemID (int ID)
{
	return MyItems->CheckID (ID);
}

void LuaAdapter::AddItemOnLevel (int ID, int Quantity, int x, int y)
{
	MyLevel = MyGame->GetLevel();
	MyLevel->AddItem (ID, Quantity,x,y);
	return;
}

void LuaAdapter::AddMessageToLog(string Message)
{
	MyLog->AddMessageToLog(Message);
	return;
}

void LuaAdapter::AddDevLog(string Message)
{
	MyLog->AddToDevLog(Message);
}

void LuaAdapter::SetWeaponMaxDamage2(int ID, int Damage)
{
	MyItems->SetWeaponMaxDamage2(ID, Damage);
}

int LuaAdapter::GetWeaponMaxDamage2(int ID)
{
	return MyItems->GetWeaponMaxDamage2(ID);
}

void LuaAdapter::SetWeaponMaxDamage3(int ID, int Damage)
{
	MyItems->SetWeaponMaxDamage2(ID, Damage);
}

int LuaAdapter::GetWeaponMaxDamage3(int ID)
{
	return MyItems->GetWeaponMaxDamage3(ID);
}

void LuaAdapter::SetWeaponMinDamage2(int ID, int Damage)
{
	MyItems->SetWeaponMinDamage2(ID, Damage);
}

int LuaAdapter::GetWeaponMinDamage2(int ID)
{
	return MyItems->GetWeaponMinDamage2(ID);
}

void LuaAdapter::SetWeaponMinDamage3(int ID, int Damage)
{
	MyItems->SetWeaponMinDamage3(ID, Damage);
}

int LuaAdapter::GetWeaponMinDamage3(int ID)
{
	return MyItems->GetWeaponMinDamage3(ID);
}

void LuaAdapter::SetWeaponDamage2Type(int ID, int Type)
{
	MyItems->SetWeaponDamage2Type(ID, Type);
}

int LuaAdapter::GetWeaponDamage2Type(int ID)
{
	return MyItems->GetWeaponDamage2Type(ID);
}

void LuaAdapter::SetWeaponDamage3Type(int ID, int Type)
{
	MyItems->SetWeaponDamage3Type(ID, Type);
}

int LuaAdapter::GetWeaponDamage3Type(int ID)
{
	return MyItems->GetWeaponDamage3Type(ID);
}

int LuaAdapter::GetWeaponNeedsEnergy(int ID)
{
	return MyItems->GetWeaponNeedsEnergy(ID);
}

int LuaAdapter::GetWeaponEnergyPerUse(int ID)
{
	return MyItems->GetWeaponEnergyPerUse(ID);
}

int LuaAdapter::GetWeaponEnergyFacultative(int ID)
{
	return MyItems->GetWeaponFaccultativeEnergy(ID);
}

void LuaAdapter::LevelRefresh()
{
	MyLevel = MyGame->GetLevel();
	MyInterface->GetGamerAndLevel();
	MyGamer->LevelUpdate();
	
}

void LuaAdapter::CreateNewLevel()
{
	MyGame->CreateNewLevel();
}

void LuaAdapter::SetCurrentLevel(int NumOfLevel)
{
	MyGame->SetCurrentLevel(NumOfLevel);
}

void LuaAdapter::MakeNewConnector(int x1, int y1, int x2, int y2, int z2, int Type, string Name, int IsCompleted)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->MakeNewConnector(x1, y1, x2, y2, z2, Type, Name, IsCompleted);
}

int LuaAdapter::GetLevelNum()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetLevelNum();
}

int LuaAdapter::GetConnectorNum(int x, int y)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorNum(x,y);
}

void LuaAdapter::SetConnectorNum(int x, int y, int Num)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetConnectorNum(x, y, Num);
}

void LuaAdapter::SetConnectorDestX(int ConnectorNum, int X)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetConnectorDestX(ConnectorNum, X);
}

void LuaAdapter::SetConnectorDestY(int ConnectorNum, int Y)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetConnectorDestY(ConnectorNum, Y);
}

void LuaAdapter::SetConnectorDestZ(int ConnectorNum, int Z)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetConnectorDestZ(ConnectorNum, Z);
}

int LuaAdapter::GetConnectorDestX(int ConnectorNum)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorDestX(ConnectorNum);
}

int LuaAdapter::GetConnectorDestY(int ConnectorNum)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorDestY(ConnectorNum);
}

int LuaAdapter::GetConnectorDestZ(int ConnectorNum)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorDestZ(ConnectorNum);
}

void LuaAdapter::SetConnectorComplete(int ConnectorNum, int State)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	MyLevel->SetConnectorIsComleted(ConnectorNum, State);
}

int LuaAdapter::GetConnectorComplete(int ConnectorNum)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorIsComleted(ConnectorNum);
}

string LuaAdapter::GetConnectorName(int ConnectorNum)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyLevel = MyGame->GetLevel();
	return MyLevel->GetConnectorName(ConnectorNum);
}

int LuaAdapter::GetInputNumber ()
{
	return MyInterface->GetInputNumber();
}

int LuaAdapter::CheckBeastID (int ID)
{
	return MyBestiary->CheckBeastID (ID);
}