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
int level::GetQuantityItemsOnCell (int x, int y)
{
	int linear;
	linear = DecartToLinear (x,y);
	int quantity = cells[linear].GetItemsQuantity();
	return quantity;
}
int level::GetItemIDByCell (int x, int y, int stacknum)
{
	int linear;
	linear = DecartToLinear (x,y);
	int ID = cells[linear].GetItemsID(stacknum);
	return ID;
}
bool level::GetStackableByCell (int x, int y, int stacknum)
{
	int linear;
	linear = DecartToLinear (x,y);
	bool Stackable = cells[linear].GetItemsStackable(stacknum);
	return Stackable;
}
int level::GetNumsInStack (int x, int y, int stacknum)
{
	int linear;
	linear = DecartToLinear (x,y);
	int nums = cells[linear].GetNumsInStack(stacknum);
	return nums;

}

void level::RemoveItemFromCell (int x, int y, int stacknum, int quantity)
{
	int linear;
	linear = DecartToLinear (x,y);
	cells[linear].RemoveItem(stacknum, quantity);
	return;
}

void level::PrintWeapons (int x, int y, int linear)
{
	int ID = cells[linear].GetItemsID(0);
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
		int QuantityTypes = MyItems->QuantityWeaponItems();
		int WeaponType;
		bool Stackable;
		WeaponType = rand() % QuantityTypes;
		Stackable = MyItems->GetStackable (WeaponType);
		cells[coords].AddItems(WeaponType, Stackable, 1);
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
	for (int i = 0; i <Width*Height; i++)
	{
		if (cells[i].GetBaseType() == '#')
		{
			cells[i].SetOpaque(1);
		}
		else
			cells[i].SetOpaque (0);
	}
}
char level::GetBaseType (int x, int y)
{
	int coord = DecartToLinear (x,y);
	return cells[coord].GetBaseType();
}
unsigned char level::GetFlagsFOV (int x, int y)
{
	int coord = DecartToLinear (x,y);
	return map.Cells[coord].Flags;

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
void level::PutItemsOnCell (int ID, int Quantity, const bool Stackable, int x, int y)
{
	int coord = DecartToLinear (x,y);
	if (Stackable == false)
	{
		cells[coord].AddItems(ID, Stackable, Quantity);
		return;
	}
	if (cells[coord].IsEmpty())
	{
		cells[coord].AddItems(ID, Stackable, Quantity);
		return;
	}

	int NumberOfItem = cells[coord].FindItemByID (ID);
	if (NumberOfItem == 0)
	{
		cells[coord].AddItems(ID, Stackable, Quantity);
		return;
	}
	cells[coord].AddItemsInSlot (ID, Quantity, NumberOfItem);
	return;

}
int level::SelectItem (int x, int y)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].SelectItem();
}
int level::SelectQuantity (int x, int y, int stacknum)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].SelectQuantity (stacknum);
}
void level::SetCreature (int a, int x, int y)
{
	int linear = DecartToLinear (x, y);
	cells[linear].SetCreature (a);
	return;
}
void level::RemoveCreature (int x, int y)
{
	int linear = DecartToLinear (x, y);
	cells[linear].RemoveCreature();
	return;
}
int level::GetCreature (int x, int y)
{
	int linear = DecartToLinear (x, y);
	return cells[linear].GetCreature();
}
int level::GetOpaque (int x, int y)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].GetOpaque ();
}
void level::SetOpaque (int x, int y, int a)
{
	int linear = DecartToLinear (x,y);
	cells[linear].SetOpaque (a);
	return;
}
int level::LOS (int x1, int y1, int x2, int y2)
{
	int x, y, xend, yend, s, dx, dy, d, inc1, inc2;
	dx = abs(x2-x1); 
    dy = abs(y2-y1);
    if (dx > dy) 
    {
        inc1 = 2*dy; 
        inc2 = 2*(dy - dx); 
        d = 2*dy - dx;
        if (x1 < x2)
        {
            x = x1; y = y1; xend = x2;
            if (y1 < y2) s = 1;
            else s = -1;
        }
        else
        {
            x = x2;
            y = y2; 
            xend = x1;
            if (y1 > y2) s = 1;
            else s = -1;
        }
        //SetPixel(hdc,x,y,cDraw);
		
        while (x < xend)
        {
            x++;
            if (d > 0)
            {
                y+=s;
                d+=inc2;
            }
            else d+=inc1;
           // SetPixel(hdc,x,y,cDraw);
			if (GetOpaque(x,y)==1)
				return 0;
        }
    }
    else
    {
        inc1 = 2*dx; 
        inc2 = 2*(dx - dy); 
        d = 2*dx - dy;
        if (y1 < y2)
        {
            y = y1; x = x1; yend = y2;
            if (x1 < x2) s = 1;
            else s = -1;
        }
        else
        {
            y = y2; 
            x = x2; 
            yend = y1;
            if (x1 > x2)s = 1;
            else s = -1;
        }
        //SetPixel(hdc,x,y,RGB(255,255,255));
        while (y < yend)
        {
            y++;
            if (d > 0)
            {
                x+=s;
                d+=inc2;
            }
            else d+=inc1;
          //  SetPixel(hdc,x,y,RGB(255,255,255));
			if (GetOpaque(x,y)==1)
			return 0;
        }
    }
	return 1;
}
int level::PathFind ( int StartX, int StartY, int EndX, int EndY)
{
	struct CellPath
	{
		int x;
		int y;
		int a;
	}
	int MyMap [LevelWidth][LevelHeight];
	for (int x = 0; x < LevelWidth; x++)
		for (int y = 0; y < LevelHeight; y++)
			MyMap [x][y] = -1;
	queue<CellPath> MyQueue;
	CellPath Temp;
	Temp.x = EndX;
	Temp.y = EndY;
	Temp.a = 0;
	int WayHasFind = 0;
	MyQueue.push (Temp);
	MyMap[EndX][EndY] = 0;
	while (!MyQueue.empty())
	{
		for (int i = -1; i<=1; i++)
		{
			for (int j = -1; j<=1; j++) 
			{
				int x = MyQueue.front().x+i;
				int y = MyQueue.front().y+j;
				if ((x<0)|| (x>LevelWidth-1)) 
					continue;
				if ((y<0) || (y>LevelHeight-1))
					continue;
				if ((GetBaseType (x,y) == '.') && (MyMap [x][y]<0))
				{
					MyMap[x][y] = MyQueue.front().a+1;
					CellPath Temp2;
					Temp2.x = x;
					Temp2.y = y;
					Temp2.a = (MyQueue.front().a+1);
					MyQueue.push (Temp2);
				
				}
				if ((x==StartX) && (y==StartY))
				{
					WayHasFind = 1;
					break;
				}
			if (WayHasFind == 1)
				break;
			}

		}
		MyQueue.pop();
	
	}

	if (WayHasFind == 0)
		return 0;
}

