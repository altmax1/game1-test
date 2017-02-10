#include "StdAfx.h"
#include "Dungeon.h"
using namespace std;


Dungeon::Dungeon(void)
{
	MaxRooms = 20;
	srand (time (0));
	MapWidth = 79;
	MapHeight = 24;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount];
}

Dungeon::Dungeon(int nums)
{
	MaxRooms = nums;
	srand (time (0));
	MapWidth = 79;
	MapHeight = 24;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount];
}


Dungeon::~Dungeon(void)
{
	delete [] DungeonCells;
}

void Dungeon::MakeRooms ()
{
	for (int i=0; i<MaxRooms; i++)
	{
		room TempRoom;
		TempRoom.RoomWidth = (rand () %7)+2;
		TempRoom.RoomHeight = (rand () %7)+2;
		TempRoom.LeftUpCornerX = rand () %(MapWidth - TempRoom.RoomWidth);
		TempRoom.LeftUpCornerY = rand () %(MapHeight - TempRoom.RoomHeight);
		TempRoom.RoomId = i;
		TempRoom.RoomFlag = 0;
		Rooms.push_back (TempRoom);		
	
	}
	return;

}

void Dungeon::PlaceRooms ()
{
	for (int i = 0; i <= MapCellsCount; i++)
		DungeonCells [i] = 35;
	list <room>::iterator p = Rooms.begin();
	while ( p!= Rooms.end())
	{
		int LeftX = p->LeftUpCornerX;
		int RightX = (p->LeftUpCornerX)+(p->RoomWidth)-1;
		int UpperY = p->LeftUpCornerY;
		int DownY = (p->LeftUpCornerY)+(p->RoomHeight)-1;
		for (int x = LeftX; x<= RightX; x++)
			for ( int y = UpperY; y<= DownY; y++)
			{
				int linear=(y*(MapWidth+1))+x;
				DungeonCells [linear] = 46;
			}
	
		p++;
	}
	return;

}

void Dungeon::PrintDungeon ()
{
	terminal_clear ();
	terminal_refresh ();
	int iter = 0;
	for (int y = 0; y <= MapHeight; y++)
		for (int x = 0; x<=MapWidth; x++)
		{
		terminal_put (x, y, DungeonCells [iter]);
		iter++;
		}
	terminal_refresh();
	return;

}

void Dungeon::InitDungeon ()
{
	cout << "MakeRooms ();" << endl;
	MakeRooms ();
	cout << "PlaceRooms ();" << endl;
	PlaceRooms ();
	cout << "PrintDungeon ();" << endl;
	PrintDungeon ();
	Rooms.clear ();
	return;

}
