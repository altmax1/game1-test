#pragma once
#include "level.h"
#include "Bestiary.h"
#include "Gamer.h"

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

	int MessageExist;
	string Message;

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
	void SetMessage (string Message);
	void PrintMessage ();
	void PrintMessageNow (string Message);
	void PrintCreature (int x, int y,int LevelX, int LevelY, int NumOfCreature); 
	void PrintHealthBar (int x, int y, int NumOfCreature, Bestiary *A);
	void PrintHID ();
	void PrintGamerHBar (Gamer *MyGamer);
	void PrintGamerEBar (Gamer *MyGamer);
	Interface(void);
	~Interface(void);
};

