#pragma once
#include "cell.h"
#include "bearlibfov.h"

using namespace std;
class level
{
private:
	int LevelWidth;
	int LevelHeight;
	FOV_MAP    map;
	set <int> CellsUnderEffects;
	
public:
	X_cell *cells;
	level();
	~level();
	void LevelCreate ( int Type,int Width, int Height, int Density);
	void LevelPrint ();
	int DecartToLinear (int x, int y); // ������� ��� ��������
	pair <int,int> LinearToDecart (int linear);
	int GetLevelWidth ();
	int GetLevelHeight ();
	char GetBaseType (int x, int y);
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
};

