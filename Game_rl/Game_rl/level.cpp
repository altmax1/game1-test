#include "stdafx.h"
#include "level.h"
#include "cell.h"


level::level()
{
}


level::~level()
{
}

void level::LevelCreate ( int Width, int Height, char *&DungeonCells)
{
	LevelWidth = Width;
	LevelHeight = Height;
	cells = new X_cell [Width*Height];
	for (int i = 0; i < Width*Height; i++)
	{
		cells[i].SetBaseType (DungeonCells[i]);
	}

}