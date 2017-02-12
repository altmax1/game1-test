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
set <int> LinearCoords; //���������� ������� � �������� �������
set <int> LinearCoordsWide;//�������� ���������� +1 �� ��� ������� ��� ����������� ���������
list <int> cohesion; // � ������ ��������� �������� ��� ��������

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
