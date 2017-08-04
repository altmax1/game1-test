#pragma once
#include "level.h"
#include "Bestiary.h"
#include "Gamer.h"

class Interface
{
private:
	int LevelWidth;			 //������ ������ �� 1
	int LevelHeight;
	int WindowWidth;		// ������ ���� ���������
	int WindowHeight;
	int FOVHeight;			//������ ������� ��������� � ���������
	int FOVWidth;
	level *Mylevel;
	int GamerCoordX;		//���������� ������
	int GamerCoordY;
	int MiniMapCoordX;		//���������� ���������
	int MiniMapCoordY;
	int GamerCoordXInTerminal;
	int GamerCoordYInTerminal;

	int MessageExist;
	string Message;
	wstring Message2;

public:
	void ReadIniFile ();
	void GetGamerAndLevel ();
	void PrintFOV ();
	void PrintMiniMap ();
	void PrintBorder ();
	void CorrectLeftUp (int &x, int &y);
	void PrintItems (int BaseX, int BaseY, int FOVX, int FOVY);
	void PrintEffects (int BaseX, int BaseY, int FOVX, int FOVY);
	void PrintMiniMapBorder ();
	int SelectTarget ();
	//void PrintField ( int x, int y); ������� ��� ��� � ��������� �����?
	void SetMessage (string Message);
	void SetMessage(wstring Message);
	void PrintMessage ();
	void PrintMessageNow (string Message);
	void PrintMessageNow(wstring Message);
	void PrintCreature (int x, int y,int LevelX, int LevelY, int NumOfCreature); 
	void PrintHealthBar (int x, int y, int NumOfCreature, Bestiary *A);
	void PrintHID ();
	void PrintGamerHBar (Gamer *MyGamer);
	void PrintGamerEBar (Gamer *MyGamer);
	void PrintOtherHIDs (Gamer *MyGamer);
	void PrintInventory (Gamer *MyGamer);
	string GetInputString ();
	int GetInputNumber ();
	int GetInputKey();
	Interface(void);
	~Interface(void);
	void ExitMenu();
};

