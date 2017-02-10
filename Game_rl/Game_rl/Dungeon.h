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
set <int> LinearCoords; //���������� ������� � �������� �������
set <int> LinearCoordsWide;//�������� ���������� +1 �� ��� ������� ��� ����������� ���������
list <int> cohesion; // � ������ ��������� �������� ��� ��������

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
	void SetLinearCoordsWide ( list <room> ::iterator p);
	void DetectCohesion ();
	void PrintRoomDebug ();
	void Vremenn ();

};
