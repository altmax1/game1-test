#pragma once
#include "cell.h"
#include "bearlibfov.h"

using namespace std;
class level
{
private:
	int LevelWidth;
	int LevelHeight;
	FOV_MAP    map;
	
public:
	X_cell *cells;
	level();
	~level();
	void LevelCreate ( int Type,int Width, int Height, int Density);
	void LevelPrint ();
	int DecartToLinear (int x, int y); // утилита для перевода
	int GetLevelWidth ();
	int GetLevelHeight ();
	void FovCellsInit ();
	void FovProcess (int x, int y, int radius);
	void PlaceItems ();
	void PlaceWeapons (int quantity);
	void PrintWeapons(int x, int y, int linear);
	int GetItemIDByCell (int x, int y);
	int GetQuantityItemsOnCell (int x, int y);
	void RemoveItemFromCell (int x, int y);
	bool GetStackableByCell (int x, int y);
	int GetNumsInStack (int x, int y);
};

