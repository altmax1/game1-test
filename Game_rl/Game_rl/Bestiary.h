#pragma once
#include "Beast.h"
using namespace std;

class Bestiary
{
private:
	vector <Beast> Creatures;
	vector <Beast> BeastsOfLevel;
public:
	void MakeCreatures ();
	void FillCreatures ();
	void MakeCreature (int ID, int x, int y);
	void RemoveCreature (int Num);
	Beast* GetCreatureFromLevel (int Num);
	void MakeBeastsMove();
	Bestiary(void);
	~Bestiary(void);
	void SetIsDead (int Num, int a);
	int GetIsDead (int Num);
	int GetID (int Num);
	void SetID (int Num, int ID);
	int GetCoordX (int Num);
	void SetCoordX (int Num, int x);
	int GetCoordY (int Num);
	void SetCoordY (int Num, int y);
	int GetHP (int Num);
	void SetHP (int Num, int HP);
	int GetDefense (int Num);
	void SetDefense (int Num, int def);
	int GetDex (int Num);
	void SetDex (int Num, int Dex);
	int GetStr (int Num);
	void SetStr (int Num, int Str);
	
};

