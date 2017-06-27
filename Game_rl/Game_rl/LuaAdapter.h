#pragma once
#include "Game.h"
class LuaAdapter
{
private:
	Game *MyGame;
	level *MyLevel;
	Gamer *MyGamer;
	Bestiary *MyBestiary;
	Items *MyItems;
	Interface *MyInterface;
	Log *MyLog;
	
public:
	void LuaDesc (lua_State *L);
	char GetTileBaseType (int x, int y) const;
	int GetLevelWidth();
	int GetLevelHeight ();
	int GetRandom (int a);
	void CreateTheBeast (int ID, int x, int y);
	int GetGamerX () const;
	void SetGamerX ( int a);
	int GetGamerY () const;
	void SetGamerY (int a);
	int PathFind (int StartX, int StartY, int EndX, int EndY);
	int GetCellPassable (int x, int y);
	void SetPassable (int x, int y, int passable);
	int GetGamerHP () const;
	void SetGamerHP (int a);
	int GetGamerStr () const;
	void SetGamerStr (int a);
	int GetGamerMaxHP () const;
	void SetGamerMaxHP (int a);
	int GetGamerDex () const;
	void SetGamerDex (int a);
	int GetGamerEnergy () const;
	void SetGamerEnergy (int a);
	int GetGamerRangeOfSight () const;
	void SetGamerRangeOfSight (int a); 
	int GetGamerMaxEnergy () const;
	void SetGamerMaxEnergy (int a);
	int GetGamerDefense () const;
	void SetGamerDefense (int a);
	int GetGamerDefense2 () const;
	void SetGamerDefense2 (int a);
	int GetGamerDefense3 () const;
	void SetGamerDefense3 (int a);
	int GetGamerDefense4 () const;
	void SetGamerDefense4 (int a);
	int GetGamerDefense5 () const;
	void SetGamerDefense5 (int a);
	int GetGamerRegenHP () const;
	void SetGamerRegenHP (int a);
	int GetGamerRegenEnergy () const;
	void SetGamerRegenEnergy (int a);
	int GetBeastNumber (int x, int y);
	void RemoveCreature (int Num);
	void SetCreature (int x, int y, int Num);
	void AttackBeastByNum (int Num);
	int LOS (int x1, int y1, int x2, int y2);
	void SetBeastHP (int Num, int HP);
	int GetBeastHP (int Num);
	void SetBeastCoordX (int Num, int x);
	void SetBeastCoordY (int Num, int y);
	int GetBeastCoordX (int Num);
	int GetBeastCoordY (int Num);
	void SetBeastID (int Num, int ID);
	int GetBeastID (int Num);
	string GetBeastRName (int Num);
	void SetBeastRName (int Num, string Name);
	void SetBeastIsDead (int Num, int a);
	int GetBeastIsDead (int Num);
	void SetBeastDefense (int Num, int Def);
	int GetBeastDefense (int Num);
	void SetBeastDefenseAdvansed (int NumOfBeast,int NumOfDefense, int Def);
	int GetBeastDefenseAdvansed (int NumOfBeast, int NumOfdefense);
	void SetBeastDex (int Num, int Dex);
	int GetBeastDex (int Num);
	void SetBeastStr (int Num, int Str);
	int GetBeastStr (int Num);
	int GetDefenseBySlot (int NumOfSlot);
	int GetDefenseBySlotAdvansed (int NumOfSlot, int NumOfdefense);
	int GetDefenseByID (int Id, int NumOfDefense);
	int GetItemIdBySlot (int SlotNum);
	int GetTypeById (int ID);
	int GetType2ById (int ID);
	int GetWeightById (int Id);
	int GetWeaponMaxDamage (int Id);
	void SetWeaponMaxDamage (int Id, int MaxDamage);
	int GetWeaponMinDamage (int Id);
	void SetWeaponMinDamage (int Id, int MinDamage);
	int GetWeaponNeedsAmmo (int Id);
	int GetWeaponIsAmmo (int Id);
	int GetWeaponCaliber (int Id);
	int GetWeaponAmmoQuantity (int Id);
	void SetWeaponAmmoQuantity (int Id, int Quantity);
	int GetWeaponCurrentAmmoQuantity (int Id);
	int GetQuality (int Id);
	void SetQuality (int Id, int Quality);
	int GetIsDestroyed (int Id);
	void SetIsDestroyed (int Id, int a);
	int GetWeaponRange (int Id);
	void SetWeaponRange (int Id, int Range);
	int GetWeaponBlastRadius (int Id);
	void SetWeaponBlastRadius (int Id, int Radius);
	int GetWeaponNextAmmo (int Id);
	void UnloadWeapon (int Id);
	void ReloadWeapon (int Id);
	int GetWeaponShotsByStep (int Id);
	void SetWeaponShotsByStep (int Id, int Shots);
	int GetWeaponAfterEffectType (int Id);
	int GetWeaponAfterEffectTime (int Id);
	int GetWeaponAfterEffectPower (int Id);
	void WeaponMakeOneShot (int Id);
	int SelectTarget ();
	void PrintMessage (string MyMessage);
	int GetKeyCode ();
	void PrintMessageNow (string Message);
	int GetMoves ();
	void SetGamerMoved ();
	void ResetGamerMoved ();
	int GetGamerMoved ();
	void AddEffectOnCell (int x, int y, int Type, int Power, int Time);
	int GetNumOfEffectsOnCell (int x, int y);
	void CheckEffectsOnCell (int x, int y);
	int GetTypeOfEffectOnCell (int x, int y, int Num);
	int GetPowerOfEffectOnCell (int x, int y, int Num);
	int GetTimeOfEffectOnCell (int x, int y, int Num);
	void EffectOnCellTimeDec (int x, int y);
	string GetInputString ();
	int GetInputNumber ();
	int GetInputKey();
	int CheckItemID(int ID);
	int CheckBeastID (int ID);
	void AddItemOnLevel (int ID, int Quantity, int x, int y);
	void AddMessageToLog(string Message);
	void AddDevLog(string Message);
	void SetWeaponMaxDamage2(int ID, int Damage);
	int GetWeaponMaxDamage2(int ID);
	void SetWeaponMaxDamage3(int ID, int Damage);
	int GetWeaponMaxDamage3(int ID);
	void SetWeaponMinDamage2(int ID, int Damage);
	int GetWeaponMinDamage2(int ID);
	void SetWeaponMinDamage3(int ID, int Damage);
	int GetWeaponMinDamage3(int ID);
	void SetWeaponDamage2Type(int ID, int Type);
	int GetWeaponDamage2Type(int ID);
	void SetWeaponDamage3Type(int ID, int Type);
	int GetWeaponDamage3Type(int ID);
	LuaAdapter(void);
	~LuaAdapter(void);
};

