#pragma once
#include "cell.h"

using namespace std;
class level
{
private:
	int LevelWidth;
	int LevelHeight;
	
public:
	X_cell *cells;
	level();
	~level();
	void LevelCreate ( int Type,int Width, int Height, int Density);
	void LevelPrint ();
	int DecartToLinear (int x, int y); // утилита для перевода
	int GetLevelWidth ();
	int GetLevelHeight ();
};

