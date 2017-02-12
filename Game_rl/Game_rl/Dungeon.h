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
	vector <room> Rooms;
	int MaxRooms;
	char *DungeonCells;
	int MapCellsCount;
	int GraphComponentCount;
public:
	Dungeon(void);
	Dungeon(int nums);
	~Dungeon(void);
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

};
