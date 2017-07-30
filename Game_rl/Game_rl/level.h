#pragma once
#include "cell.h"
#include "bearlibfov.h"

using namespace std;

struct Connector {
	int StartX;
	int StartY; 
	int DestinationX;
	int DestinationY;
	int DestinationZ;
	int ConnectorCompleted; // 0 если уровень назначения не готов и 1 если полностью  оформлен
	string ConnectorName;
	int Type;

};

struct LevelRoom {
	int LeftX;
	int UpY;
	int Width;
	int Height;
};

class level
{
private:
	int LevelWidth;
	int LevelHeight;
	FOV_MAP    map;
	set <int> CellsUnderEffects;
	vector <Connector> Connectors;
	vector <LevelRoom> Rooms; // прямоугольные комнаты
	vector < vector<int>> Rooms2; // комнаты не прямоугольные - линейные координаты
	int NumOfLevel; // номер уровня - генерируется автоматически
	int LevelIndex; // номер уровня - заполняется вручную по правилам;
	string LevelName; // название уровня
	
public:
	X_cell *cells;
	level();
	~level();
	void LevelCreate ( int Type,int Width, int Height, int Density);
	void LevelPrint ();
	int DecartToLinear (int x, int y); // утилита для перевода
	pair <int,int> LinearToDecart (int linear);
	int GetLevelWidth ();
	int GetLevelHeight ();
	char GetBaseType (int x, int y);
	void SetBaseType(int x, int y, char BaseType);
	unsigned char GetFlagsFOV (int x, int y);
	void FovCellsInit ();
	void FovProcess (int x, int y, int radius);
	void PlaceItems ();
	void PlaceWeapons (int quantity);
	void PrintWeapons(int x, int y, int linear);
	int GetItemIDByCell (int x, int y, int stacknum);
	int GetQuantityItemsOnCell (int x, int y);
	void RemoveItemFromCell (int x, int y,int stacknum, int quantity); 
	bool GetStackableByCell (int x, int y, int stacknum);
	int GetNumsInStack (int x, int y, int stacknum);
	void PutItemsOnCell (int ID, int Quantity, const bool Stackable, int x, int y) ;
	int SelectItem (int x, int y);
	int SelectQuantity (int x, int y, int stacknum);
	int GetCreature (int x, int y);
	void SetCreature (int a, int x, int y);
	void RemoveCreature (int x, int y);
	int LOS (int x1, int y1, int x2, int y2);
	int GetOpaque (int x, int y);
	void SetOpaque (int x, int y, int a);
	int PathFind ( int StartX, int StartY, int EndX, int EndY);
	int GetPassable (int x, int y);
	void SetPassable (int x, int y, int passable);
	void AddEffect (int x, int y, int Type, int Power, int Time);
	int GetNumOfEffects (int x, int y);
	void CheckEffects (int x, int y);
	void CheckEffectsGlobal ();
	int GetEffectTypeByNum (int x, int y, int Num);
	int GetEffectPowerByNum (int x, int y, int Num);
	int GetEffectTimeByNum (int x, int y, int Num);
	void EffectTimeDesc (int x, int y);
	void LevelProcessEffects ();
	void AddItem (int ID, int Quantity, int CoordX, int CoordY);
	int GetLevelNum();
	void SetLevelNum(int Num);
	int GetConnectorNum(int x, int y);
	void SetConnectorNum(int x, int y, int Num);
	void MakeNewConnector(int x1, int y1, int x2, int y2, int z2, int type, string Name, int Completed);
	void SetConnectorDestX(int NumOfConnector, int X);
	void SetConnectorDestY(int NumOfConnector, int Y);
	void SetConnectorDestZ(int NumOfConnector, int Z);
	void SetConnectorIsComleted(int NumOfConnector, int a);
	int GetConnectorDestX(int NumOfConnector);
	int GetConnectorDestY(int NumOfConnector);
	int GetConnectorDestZ(int NumOfConnector);
	int GetConnectorIsComleted(int NumOfConnector);
	int GetConnectorType(int NumOfConnector);
	string GetConnectorName(int NumOfConnector);
	int GetTile(int x, int y);
	void SetTile(int x, int y, int Tile);
	void AddRoom(LevelRoom MyRoom);
	int GetRoomsCount();
	int GetRooomLeftX(int Num);
	int GetRoomUpY(int Num);
	int GetRoomWidth(int Num);
	int GetRoomHeight(int Num);
	void AddRoomToRooms2(vector<int> Room);
	int GetLevelIndex();
	void SetLevelIndex(int Index);
	string GetLevelName();
	void SetLevelName(string Name);
	void SaveLevel();
	void SaveMap(ofstream &MyStream);
	void SaveConnectors(ofstream &MyStream);
	void SaveRooms(ofstream &MyStream);
	void SaveRooms2(ofstream &MyStream);
	void LoadLevel();
	void LoadMap(ifstream &in);
	void LoadConnectors(ifstream &MyStream);
	void LoadRooms(ifstream &MyStream);
	void LoadRooms2(ifstream &MyStream);


};

