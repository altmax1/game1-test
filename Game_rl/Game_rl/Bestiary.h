#pragma once
#include "Beast.h"
using namespace std;

class Bestiary
{
private:
	vector <Beast> Creatures;
	vector <Beast> BeastsOfLevel;
	set<int> DeadBeasts;
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
	string GetRName (int Num) {return BeastsOfLevel[Num].GetRName();};
	void SetRName (int Num, string Name) {BeastsOfLevel[Num].SetRName(Name);};
	int GetCoordX (int Num);
	void SetCoordX (int Num, int x);
	int GetCoordY (int Num);
	void SetCoordY (int Num, int y);
	int GetHP (int Num);
	void SetHP (int Num, int HP);
	int GetMaxHP (int Num);
	void SetMaxHP (int Num, int HP);
	int GetDefense (int Num);
	void SetDefense (int Num, int def);
	int GetDefenseAdvansed (int Num, int TypeOfDef);
	void SetDefenseAdvansed (int Num, int TypeOfDef, int Def);
	int GetDex (int Num);
	void SetDex (int Num, int Dex);
	int GetStr (int Num);
	void SetStr (int Num, int Str);
	int GetCharCode (int Num);
	void SetCharCode (int Num, int Code);
	int GetColorVisible (int Num);
	void SetColorVisible (int Num, int Color);
	int GetColorNotVisible (int Num);
	void SetColorNotVisible (int Num, int Color);
	int GetSpeed (int Num);
	void SetSpeed (int Num, int Speed);
	int GetMovePoints (int Num) {return BeastsOfLevel[Num].GetMovePoints();}
	void SetMovePoints (int Num, int Points) {BeastsOfLevel[Num].SetMovePoints(Points);}
	void SetDeadBeast (int Num) {DeadBeasts.insert (Num);};
	
};

