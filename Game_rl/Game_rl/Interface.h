#pragma once
#include "level.h"

class Interface
{
private:
	int LevelWidth; //������ �� 1!!
	int LevelHeight;
	int WindowWidth;
	int WindowHeight;
	int FOVHeight;
	int FOVWidth;
	level *Mylevel;
	int GamerCoordX;
	int GamerCoordY;

public:
	void ReadIniFile ();
	void GetGamerAndLevel ();
	void PrintFOV ();
	void CorrectLeftUp (int &x, int &y);
	//void PrintField ( int x, int y); ������� ��� ��� � ��������� �����?
	Interface(void);
	~Interface(void);
};

