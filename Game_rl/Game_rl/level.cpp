#include "stdafx.h"
#include "level.h"
#include "cell.h"
#include "Dungeon.h"
#include "Game.h"


level::level()
{
	
}


level::~level()
{
	delete [] cells;
	
}

void level::PrintWeapons (int x, int y, int linear)
{
	int ID = cells[linear].GetItemsID();
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	int TypeOfWeapon;
	TypeOfWeapon = MyItems->GetTypeOfWeapon (ID);
	if (TypeOfWeapon == 0)
		terminal_put (x,y,92);
	else if ((TypeOfWeapon == 1) || (TypeOfWeapon == 2))
		terminal_put (x,y,124);
	else terminal_put (x,y, 37);
	return;


}

void level::PlaceWeapons (int Quantity)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	for (int i = 0; i< Quantity; i++)
	{
		int coords;
		char basetype;
		do {
		coords = rand () % (LevelWidth*LevelHeight);
		basetype = cells[coords].GetBaseType();
		} while (basetype!= '.');
		int QuantityTypes = MyItems->QuantityColdWeaponItems();
		int WeaponType;
		WeaponType = rand() % QuantityTypes;
		cells[coords].AddItems(WeaponType);
	}
}
void level::PlaceItems()
{
	PlaceWeapons (20);
	return;
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
	 }

}

void level::FovProcess (int x, int y, int Radius )
{
	
	CalcFOVC (&map, x, y, Radius);

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
		if (map.Cells[iter].Flags & FOV_CELL_VISIBLE)
			terminal_color ("white");
		else if (map.Cells[iter].Flags & FOV_CELL_VISITED)
			terminal_color (0xafdfdfa9);
		else 
			terminal_color ("black");
		terminal_put (x, y, c);
		if (cells[iter].GetItemsQuantity() >0)
			PrintWeapons (x,y,iter);
		iter++;
		}
	//terminal_refresh();
	//terminal_read();
		return;



}