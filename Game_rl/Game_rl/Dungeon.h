#pragma once
using namespace std;
struct room
{
int LeftUpCornerX;
int LeftUpCornerY;
int RoomWidth;
int RoomHeight;
int RoomId;
int RoomFlag;

};

class Dungeon
{
private:
	int MapWidth;
	int MapHeight;
	list <room> Rooms;
	int MaxRooms;
	char *DungeonCells;
	int MapCellsCount;
public:
	Dungeon(void);
	Dungeon(int nums);
	~Dungeon(void);
	void MakeRooms ();
	void PlaceRooms ();
	void PrintDungeon ();
	void InitDungeon ();

};
