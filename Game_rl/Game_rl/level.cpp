#include "stdafx.h"
#include "level.h"
#include "cell.h"
#include "Dungeon.h"


level::level()
{
	
}


level::~level()
{
	delete [] cells;
	
}

int level::DecartToLinear (int x, int y)
{
 return (y*LevelWidth+x); 
}
int level::GetLevelWidth ()
{
	return LevelWidth;
}
int level::GetLevelHeight ()
{
	return LevelHeight;
}

void level::FovCellsInit ()
{
	map.Width = LevelWidth;
	map.Height = LevelHeight;
	map.Cells = new FOV_CELL[map.Width * map.Height];
	ZeroMemory( map.Cells, sizeof(FOV_CELL) * map.Width * map.Height );
	for ( int i=0; i < map.Width * map.Height; i++ )
    {
		switch ( cells[i].GetBaseType())
        {
            case '.':
                map.Cells[i].Flags &= (0xFF ^ FOV_CELL_OPAQUE);
                break;

            case '#':
                map.Cells[i].Flags |= FOV_CELL_OPAQUE;
                break;

        };
		cout << map.Cells[i].Flags;
    }

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
	FovCellsInit ();

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
	//terminal_refresh();
	//terminal_read();
		return;



}