#pragma once
#include "level.h"

class Interface
{
private:
	int LevelWidth;			 //размер уровня от 1
	int LevelHeight;
	int WindowWidth;		// размер окна терминала
	int WindowHeight;
	int FOVHeight;			//размер области видимости в терминале
	int FOVWidth;
	level *Mylevel;
	int GamerCoordX;		//координаты игрока
	int GamerCoordY;
	int MiniMapCoordX;		//координаты миникарты
	int MiniMapCoordY;
	int GamerCoordXInTerminal;
	int GamerCoordYInTerminal;

public:
	void ReadIniFile ();
	void GetGamerAndLevel ();
	void PrintFOV ();
	void PrintMiniMap ();
	void PrintBorder ();
	void CorrectLeftUp (int &x, int &y);
	void PrintItems (int BaseX, int BaseY, int FOVX, int FOVY);
	void PrintMiniMapBorder ();
	int SelectTarget ();
	//void PrintField ( int x, int y); вынести или нет в отдельный класс?
	Interface(void);
	~Interface(void);
};

