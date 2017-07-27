#pragma once
#include "cell.h"
#include "level.h"

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
	virtual void ReturnDungeon (level *MyLevel) = 0;

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
	void ReturnDungeon (level *MyLevel);

};

struct MyCell {
	int pasable;
	int visited;
};

class DungeonType2 : public Dungeon
{
private:
	int MapWidth;
	int MapHeight;
	int Density;
	vector <int> cells;
	vector <MyCell> MyCells;
	int PassableCells; //проходимые клетки
	vector <set <int>> Rooms;
	level *MyLevel;

public:
	DungeonType2(void);
	DungeonType2(int Width, int Height, int nums);
	~DungeonType2(void);
	void InitDungeon ();
	void FillArrayRandom();
	void CellsProcessing();
	void Averaging(int x, int y);
	int DecToLin(int x, int y);
	void PrintDungeon();
	void ConvertToMyCell();
	void FindRooms();
	void DrawLine(int x1, int y1, int x2, int y2);
	void ConnectRooms();
	void ReturnDungeon(level* MyLevel);
	void AddRoomsToVector(); // переносим комнаты в level

};