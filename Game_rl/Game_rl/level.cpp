#include "stdafx.h"
#include "level.h"
#include "cell.h"
#include "Dungeon.h"


level::level()
{
	cout << "level constructor" << endl;
}


level::~level()
{
	delete [] cells;
	cout << "level destructor" << endl;
}


void level::LevelCreate ( int Type,int Width, int Height, int Density)
{
	LevelWidth = Width;
	LevelHeight = Height;
	cells = new X_cell [Width*Height];
	Dungeon *ptr;
	ptr = Dungeon::MakeDungeon (Type, Width, Height, Density);
	level *temp;
	temp = this;
	ptr->ReturnDungeon (temp);
	delete ptr;

}

void level::LevelPrint ()
{
	terminal_clear();
	int iter = 0;
	char c;
	for (int y = 0; y < 40; y++)
		for (int x = 0; x<80; x++)
		{
		c = cells[iter].GetBaseType();
		terminal_put (x, y, c);
		iter++;
		}
	terminal_refresh();
	terminal_read();


}