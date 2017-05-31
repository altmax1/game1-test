#pragma once
#include "item.h"
class Weapon1 :
	public Item
{
private:
	int Type;
	int MaxDamage;
	int MinDamage;
	bool NeedsAmmo; //нужны ли патроны
	bool IsAmmo; //является ли зарядом/патроном
	int Caliber; //калибр
	int AmmoQuantity; // max количество патронов в обойме
	vector <int> Ammo; //патроны здесь - пихаем их ID
	int Quality; //качество - износ мб, если батарея, то заряд.
	bool Destroyed; //если разрушено оружие, ставим 1. у not unique не учитывать.
	int Range;  // дистанция поражения (стрельбы)
	int BlastRadius; //радиус поражения


public:
	Weapon1(void);
	~Weapon1(void);
	int GetType();
	void SetType (int Type);
	int GetMaxDamage ();
	void SetMaxDamage (int a);
	int GetMinDamage ();
	void SetMinDamage (int a);
	bool GetNeedsAmmo ();
	void SetNeedsAmmo (int a);
	bool GetIsAmmo ();
	void SetIsAmmo (int a);
	int GetCaliber ();
	void SetCaliber (int a);
	int GetAmmoQuantity ();
	void SetAmmoQuantity (int a);
	void ReloadAmmo	();
	void UnloadAmmo ();
	int GetQuality ();
	void SetQuality (int a);
	bool GetDestroyed ();
	void SetDestroyed (int a);
	int GetRange ();
	void SetRange (int a);
	int GetBlastRadius ();
	void SetBlastRadius (int a);

};

