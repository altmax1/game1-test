// Game_rl.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "cell.h"
#include "level.h"
#include "X_File.h"
#include "X_MainMenu.h"




int _tmain(int argc, _TCHAR* argv[])
{
	terminal_open ();
	X_MainMenu Menu1;
	Menu1.GetMenu();
	Menu1.PrintBuffer();
	getchar();
	return 0;
}

