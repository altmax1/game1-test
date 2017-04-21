#include "StdAfx.h"
#include "Equipment.h"
#include "Game.h"


Equipment::Equipment(void)
{
	HeadEq = 1000000;
	BodyEq = -1;
	ArmsEq = 1000001;
	GlovesEq = -1;
	BodyEq = -1;
	LegsEq = -1;
	BootsEq = -1;
	LeftArmWeapon = -1;
	RightArmWeapon = -1;

}


Equipment::~Equipment(void)
{
}

void Equipment::PrintItems ()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();

	terminal_wprint (10, 9, L"������:");
	terminal_wprint (10, 10, L"����: ");
	terminal_wprint (10, 11, L"����:");
	terminal_wprint (10, 12, L"��������:");
	terminal_wprint (10, 13, L"����:");
	terminal_wprint (10, 14, L"�����:");
	terminal_wprint (10, 16, L"������������/����������:");
	terminal_wprint (10, 18, L"������ ����:");
	terminal_wprint (10, 19, L"������ ����:");

	if (HeadEq < 0)
		terminal_wprint (20,9, L"���");
	else terminal_print (20, 9, MyItems->GetNameOfArmour (HeadEq).c_str());
	if (BodyEq < 0)
		terminal_wprint (20,10, L"���");
	else terminal_print (20,10, MyItems->GetNameOfArmour (BodyEq).c_str());
	if (ArmsEq < 0)
		terminal_wprint (20,11, L"���");
	else terminal_print (20, 11, MyItems->GetNameOfArmour (ArmsEq).c_str());
	if (GlovesEq < 0)
		terminal_wprint (20,12, L"���");
	else terminal_print (20,12, MyItems->GetNameOfArmour (GlovesEq).c_str());
	if (LegsEq < 0)
		terminal_wprint (20,13, L"���");
	else terminal_print (20,13, MyItems->GetNameOfArmour (LegsEq).c_str());
	if (BootsEq < 0)
		terminal_wprint (20,14, L"���");
	else terminal_print (20,14, MyItems->GetNameOfArmour (BootsEq).c_str());
}
void Equipment::PrintEquipment ()
{
	terminal_clear();
	terminal_refresh();
	int a;
	while (1)
	{
		terminal_wprint (10, 7, L"� � � � � � � � � �:");
		PrintItems ();
		terminal_refresh();
		a = terminal_read();
		if (a==TK_ESCAPE)
			return;
	
	
	}

	return;
}
