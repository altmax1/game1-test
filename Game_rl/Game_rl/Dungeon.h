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
int RoomGrafComponent;
set <int> LinearCoords; //координаты комнвты в линейном массиве
set <int> LinearCoordsWide;//линейные координаты +1 во все стороны для определения смежности
list <int> cohesion; // с какими комнатами граничит при создании

};


class Dungeon 
{
private:
	int MapWidth;
	int MapHeight;
public:
	Dungeon(void);
	virtual ~Dungeon();
	virtual void InitDungeon() = 0;
	static Dungeon* MakeDungeon (int Type, int Width, int Height, int Density);
	virtual void ReturnDungeon (char *&Dung) = 0;

};

class DungeonType1: public Dungeon
{
private:
	int MapWidth;
	int MapHeight;
	vector <room> Rooms;
	int MaxRooms;
	char *DungeonCells;
	int MapCellsCount;
	int GraphComponentCount;
public:
	DungeonType1(void);
	DungeonType1(int nums);
	DungeonType1(int Width, int Height, int nums);
	virtual ~DungeonType1(void);
	void MakeRooms ();
	void PlaceRooms ();
	void PrintDungeon ();
	void InitDungeon ();
	void SetLinearCoordsWide ( vector <room> ::iterator p);
	void DetectCohesion ();
	void PrintRoomDebug ();
	void Vremenn ();
	void FindGrafComponents ();
	void MakePassages ();
	void DrawPassage (int room1, int room2);
	int DecartToLinear (int x, int y);
	void ReturnDungeon (char *&Dung);

};
