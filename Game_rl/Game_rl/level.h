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
	void LevelCreate ( int Width, int Height, char *&DungeonCells);
};

