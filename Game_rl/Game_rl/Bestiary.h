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
};

