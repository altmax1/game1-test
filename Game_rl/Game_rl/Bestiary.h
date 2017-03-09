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
	void PutCreatureInBOL (int ID);
	Bestiary(void);
	~Bestiary(void);
};

