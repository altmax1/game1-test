#include "stdafx.h"
#include "level.h"
#include "cell.h"
#include "Dungeon.h"
#include "Game.h"
#include "LuaAdapter.h"


level::level()
{
	
}


level::~level()
{
	delete[] cells;
	
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
	int TypeOfWeapon=0;
	if (ID < 1000000)
		TypeOfWeapon = MyItems->GetTypeById (1);
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
		//int QuantityTypes = MyItems->QuantityWeaponItems();
		int QuantityTypes = MyItems->QuantityUniqueWeapon ();
		int WeaponType;
		bool Stackable;
		WeaponType = rand() % QuantityTypes;
		int Id = MyItems->GetIdForCreation (WeaponType);
		cout<< "Id="<<Id<<endl;
		Stackable = 0;
		cells[coords].AddItems(Id, Stackable, 1);
	}

	for (int i = 0; i< 10; i++)
	{
		int coords;
		char basetype;
		do {
		coords = rand () % (LevelWidth*LevelHeight);
		basetype = cells[coords].GetBaseType();
		} while (basetype!= '.');
		int Quant2 = rand () %20;
		cells[coords].AddItems(900001,1,Quant2);

	}

	for (int i = 0; i< 10; i++)
	{
		int coords;
		char basetype;
		do {
		coords = rand () % (LevelWidth*LevelHeight);
		basetype = cells[coords].GetBaseType();
		} while (basetype!= '.');
		int Quant2 = rand () %20;
		cells[coords].AddItems(900003,1,Quant2);

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
			cells[i].SetPassable(0);
		}
		else
		{	
			cells[i].SetOpaque (0);
			cells[i].SetPassable(1);
		}
	}
}
char level::GetBaseType (int x, int y)
{
	int coord = DecartToLinear (x,y);
	return cells[coord].GetBaseType();
}
void level::SetBaseType(int x, int y, char BaseType)
{
	int coord = DecartToLinear(x, y);
	cells[coord].SetBaseType(BaseType);
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
	int a = clock ();
	int iteration = 0;
	struct CellPath
	{
		int x;
		int y;
		int a;
	};
//	int MyMap [LevelWidth][LevelHeight];  Доделать на динамический массив!!!!
	int MyMap[128][80];
	for (int x = 0; x < LevelWidth; x++)
		for (int y = 0; y < LevelHeight; y++)
			MyMap[x][y] = -1;
	list<CellPath> MyQueue;
	CellPath Temp;
	Temp.x = EndX;
	Temp.y = EndY;
	Temp.a = 0;
	int WayHasFind = 0;
	MyQueue.push_back (Temp);
	MyMap[EndX][EndY] = 0;
	while (!MyQueue.empty())
	{
		for (int i = -1; i<=1; i++)
		{
			for (int j = -1; j<=1; j++) 
			{
				iteration++;
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
					MyQueue.push_back (Temp2);
				
				}
				if ((x==StartX) && (y==StartY))
				{
					WayHasFind = 1;
					break;
				}
			if (WayHasFind == 1)
				break;
			}
			if (WayHasFind == 1)
				break;

		}
		MyQueue.pop_front();
		if (WayHasFind == 1)
			break;

	
	}
	//cout << "Time: "<< clock()-a<<endl;
	//cout << "Iteration: " <<iteration<<endl;

	if (WayHasFind == 0)
		return 0;
	int a1 = MyMap[StartX][StartY];
	int iter = 1;
	for (int y = -1; y <=1; y++)
		for (int x = -1; x<=1; x++)
		{
			int MyX = StartX+x;
			int MyY = StartY+y;
			if ((MyX>=0) && (MyX<=LevelWidth-1)&& (MyY>=0) && (MyY<=LevelHeight-1)) 
			{
			 if ( ((MyMap[StartX+x][StartY+y])+1) == a1)
			 {
				 
				 return iter;
			 
			 }
			
			}
			iter++;
		}
	return -100;
}

int level::GetPassable (int x, int y)
{
	int linear = DecartToLinear (x, y);
	return cells[linear].GetPassable();
}

void level::SetPassable (int x, int y, int passable)
{
	int linear = DecartToLinear (x,y);
	cells[linear].SetPassable (passable);
	return;
}

void level::AddEffect (int x, int y, int Type, int Power, int Time)
{
	int linear = DecartToLinear (x,y);
	cells[linear].AddEffect (Type,Power,Time);
	CellsUnderEffects.insert (linear);
}

int level::GetNumOfEffects (int x, int y)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].GetNumOfEffects();
}

void level::CheckEffects (int x, int y)
{
	int linear = DecartToLinear (x,y);
	cells[linear].CheckEffects();
}

void level::CheckEffectsGlobal ()
{
	/*int linear = DecartToLinear (x,y);
	cells[linear].CheckEffects();
	if (cells[linear].GetNumOfEffects() == 0)
		CellsUnderEffects.erase (linear);
	return;*/
	set <int> CellsToDelete;
	set <int>::iterator p;
	for (p = CellsUnderEffects.begin(); p!= CellsUnderEffects.end(); p++)
	{
		if (cells[*p].GetNumOfEffects () == 0)
			CellsToDelete.insert (*p);
	}

	for (p = CellsToDelete.begin(); p!= CellsToDelete.end(); p++)
	{
		CellsUnderEffects.erase (*p);
	}
	CellsToDelete.clear();
}

int level::GetEffectTypeByNum (int x, int y, int Num)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].GetEffectTypeByNum (Num);
}

int level::GetEffectPowerByNum (int x, int y, int Num)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].GetEffectPowerByNum (Num);
}

int level::GetEffectTimeByNum (int x, int y, int Num)
{
	int linear = DecartToLinear (x,y);
	return cells[linear].GetEffectTimeByNum (Num);
}

void level::EffectTimeDesc (int x, int y)
{
	int linear = DecartToLinear (x,y);
	cells[linear].EffectTimeDec ();
	return;
}

void level::LevelProcessEffects ()
{
	CheckEffects (0,0);
	set <int>::iterator p;
	if (CellsUnderEffects.size() > 0)
	{
	for (p = CellsUnderEffects.begin(); p!=CellsUnderEffects.end(); p++)
	{
		int linear = *p;
		pair <int,int> coords;
		coords = LinearToDecart (linear);
		int x = coords.first;
		int y = coords.second;

		using namespace luabridge;

		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		LuaAdapter Luaad;
		Luaad.LuaDesc(L);
		luaL_dofile(L, ".\\Files\\lua\\LevelProcess.lua");
		lua_pcall(L, 0, 0, 0);
		LuaRef LevelProcess = getGlobal(L, "LevelProcess");
	  //
		try {
		      LevelProcess (Luaad,x,y);
			  }
			  catch (luabridge::LuaException const& e) {
		      std::cout << "LuaException: " << e.what() << std::endl;
			 }
	
	}
	}
}
pair <int,int> level::LinearToDecart (int linear)
{
	int y = linear/LevelWidth;
	int x = linear -(LevelWidth*(y));
	pair <int,int> coords;
	coords = make_pair(x,y);
	return coords;

}

void level::AddItem (int ID, int Quantity, int CoordX, int CoordY)
{
	Items *MyItems;
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	MyItems = MyGame->GetItems();
	int a = MyItems->CheckID(ID);
	if (a == 0)
		return;
	int NewId = MyItems->GetIdForCreation (ID);
	int Stackable = MyItems->GetStackable (ID);
	if (Stackable == 0)
		Quantity = 1;
	int coords = DecartToLinear(CoordX, CoordY);
	cells[coords].AddItems (NewId, Stackable, Quantity);
	return;
}

int level::GetLevelNum()
{
	return NumOfLevel;
}

void level::SetLevelNum(int Num)
{
	NumOfLevel = Num;
	return;
}

int level::GetConnectorNum(int x, int y)
{
	int linear = DecartToLinear(x, y);
	return cells[linear].GetConnectorNum();
}

void level::SetConnectorNum(int x, int y, int Num)
{
	int linear = DecartToLinear(x, y);
	cells[linear].SetConnectorNum(Num);
}

void level::MakeNewConnector(int x1, int y1, int x2, int y2, int z2, int type, string Name, int Completed)
{
	Connector MyConnector;
	MyConnector.StartX = x1;
	MyConnector.StartY = y1;
	MyConnector.DestinationX = x2;
	MyConnector.DestinationZ = z2;
	MyConnector.DestinationY = y2;
	MyConnector.Type = type;
	MyConnector.ConnectorName = Name;
	MyConnector.ConnectorCompleted = Completed;
	Connectors.push_back(MyConnector);
	int ConNumber = Connectors.size() - 1;
	SetConnectorNum(x1, y1, ConNumber);
	SetOpaque(x1, y1, 1);
	SetPassable(x1, y1, 1);
	SetBaseType(x1, y1, '.');
	SetTile(x1, y1, 1000);
	
}

void level::SetConnectorDestX(int NumOfConnector, int X)
{
	Connectors[NumOfConnector].DestinationX = X;
}

void level::SetConnectorDestY(int NumOfConnector, int Y)
{
	Connectors[NumOfConnector].DestinationY = Y;
}

void level::SetConnectorDestZ(int NumOfConnector, int Z)
{
	Connectors[NumOfConnector].DestinationZ = Z;
}

void level::SetConnectorIsComleted(int NumOfConnector, int a)
{
	Connectors[NumOfConnector].ConnectorCompleted = a;
}

int level::GetConnectorDestX(int NumOfConnector)
{
	return Connectors[NumOfConnector].DestinationX;
}

int level::GetConnectorDestY(int NumOfConnector)
{
	return Connectors[NumOfConnector].DestinationY;
}

int level::GetConnectorDestZ(int NumOfConnector)
{
	return Connectors[NumOfConnector].DestinationZ;
}

int level::GetConnectorIsComleted(int NumOfConnector)
{
	return Connectors[NumOfConnector].ConnectorCompleted;
}

int level::GetConnectorType(int NumOfConnector)
{
	return Connectors[NumOfConnector].Type;
}

string level::GetConnectorName(int NumOfConnector)
{
	return Connectors[NumOfConnector].ConnectorName;
}

int level::GetTile(int x, int y)
{
	int coords = DecartToLinear(x, y);
	return cells[coords].GetTile();

}

void level::SetTile(int x, int y, int Tile)
{
	int coords = DecartToLinear(x, y);
	cells[coords].SetTile(Tile);
}
