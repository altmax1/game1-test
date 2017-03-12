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
	Bestiary(void);
	~Bestiary(void);
};

