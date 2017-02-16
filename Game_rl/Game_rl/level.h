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
	int DecartToLinear (int x, int y); // ������� ��� ��������
	int GetLevelWidth ();
	int GetLevelHeight ();
	void FovCellsInit ();
	void FovProcess (int x, int y, int radius);
};

