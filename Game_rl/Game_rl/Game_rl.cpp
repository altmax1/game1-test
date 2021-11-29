// Game_rl.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "cell.h"
#include "level.h"
#include "X_File.h"
#include "X_MainMenu.h"
#include "Dungeon.h"




int _tmain(int argc, _TCHAR* argv[])
{
	//setlocale(LC_CTYPE, "rus");
	terminal_open();
	terminal_set ("window:title = Game_RL, size=80x40"); //terminal_set("window: size=80x25
	terminal_set ("0x1000: ./Files/pricel1.png");
	terminal_color ("white");
	X_MainMenu Menu1;
	Menu1.PrintMenu(); 
	/*Dungeon *ptr;
	ptr = Dungeon::MakeDungeon (1, 80, 25, 30);
	while (terminal_read ())
	{	
		int i = clock ();
		ptr->InitDungeon();
		terminal_clear;
		cout << "main cikle  "<< clock () -i<<endl;
	}*/
	//getchar();
	return 0;
}

