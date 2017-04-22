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
	MenuX = 5;
	MenuY = 5;
	DeltaXName = 12;

}


Equipment::~Equipment(void)
{
}

void Equipment::PrintBorder (int MenuState)
{
	
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	terminal_color (0xFFFFFFFF);
	
	if (MenuState == 1)
		{
			terminal_wprint (MenuX, MenuY+2, L"������:");
			if (HeadEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+2, L"���");
			else terminal_print (MenuX+DeltaXName, MenuY+2, MyItems->GetNameOfArmour (HeadEq).c_str());
		}
	
		if (MenuState == 2)
		{
			terminal_wprint (MenuX, MenuY+3, L"����: ");
			if (BodyEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+3, L"���");
			else terminal_print (MenuX+DeltaXName,MenuY+3, MyItems->GetNameOfArmour (BodyEq).c_str());
		}
	
		if (MenuState == 3)
		{
			terminal_wprint (MenuX, MenuY+4, L"����:");
			if (ArmsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+4, L"���");
			else terminal_print (MenuX+DeltaXName, MenuY+4, MyItems->GetNameOfArmour (ArmsEq).c_str());
		}

		if (MenuState == 4)
		{
			terminal_wprint (MenuX, MenuY+5, L"��������:");
			if (GlovesEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+5, L"���");
			else terminal_print (MenuX+DeltaXName,MenuY+5, MyItems->GetNameOfArmour (GlovesEq).c_str());
		}
		
		if (MenuState == 5)
		{
			terminal_wprint (MenuX, MenuY+6, L"����:");
			if (LegsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+6, L"���");
			else terminal_print (MenuX+DeltaXName,MenuY+6, MyItems->GetNameOfArmour (LegsEq).c_str());
		}
		if (MenuState == 6)
		{
			terminal_wprint (MenuX, MenuY+7, L"�����:");
			if (BootsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+7, L"���");
			else terminal_print (MenuX+DeltaXName,MenuY+7, MyItems->GetNameOfArmour (BootsEq).c_str());
		}
		
		if (MenuState == 7)
		{
			terminal_wprint (MenuX, MenuY+11, L"������ ����:");
		}
		if (MenuState == 8)
		{
			terminal_wprint (MenuX, MenuY+12, L"������ ����:");
		}
		
		int a = clock ();
		terminal_refresh();
		cout <<clock()-a<<endl;
		
		return;
}

void Equipment::SelectEquipment ()
{
	
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	

	int MenuState = 1;
	int MaxMenuState = 8;
	int MinMenuState = 1;
	while (1)
	{	
		
		terminal_clear ();
		PrintEquipment ();
		PrintBorder (MenuState);
		int a = terminal_read();
		if (a == TK_ESCAPE)
			return;
		if (a == TK_DOWN && MenuState <MaxMenuState)
			MenuState++;
		if (a == TK_UP && MenuState > MinMenuState)
			MenuState--;
		
	
	}
}

void Equipment::PrintItems ()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();

	terminal_wprint (MenuX, MenuY+2, L"������:");
	terminal_wprint (MenuX, MenuY+3, L"����: ");
	terminal_wprint (MenuX, MenuY+4, L"����:");
	terminal_wprint (MenuX, MenuY+5, L"��������:");
	terminal_wprint (MenuX, MenuY+6, L"����:");
	terminal_wprint (MenuX, MenuY+7, L"�����:");
	terminal_wprint (MenuX, MenuY+9, L"������������/����������:");
	terminal_wprint (MenuX, MenuY+11, L"������ ����:");
	terminal_wprint (MenuX, MenuY+12, L"������ ����:");

	if (HeadEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+2, L"���");
	else terminal_print (MenuX+DeltaXName, MenuY+2, MyItems->GetNameOfArmour (HeadEq).c_str());
	if (BodyEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+3, L"���");
	else terminal_print (MenuX+DeltaXName,MenuY+3, MyItems->GetNameOfArmour (BodyEq).c_str());
	if (ArmsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+4, L"���");
	else terminal_print (MenuX+DeltaXName, MenuY+4, MyItems->GetNameOfArmour (ArmsEq).c_str());
	if (GlovesEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+5, L"���");
	else terminal_print (MenuX+DeltaXName,MenuY+5, MyItems->GetNameOfArmour (GlovesEq).c_str());
	if (LegsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+6, L"���");
	else terminal_print (MenuX+DeltaXName,MenuY+6, MyItems->GetNameOfArmour (LegsEq).c_str());
	if (BootsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+7, L"���");
	else terminal_print (MenuX+DeltaXName,MenuY+7, MyItems->GetNameOfArmour (BootsEq).c_str());
}
void Equipment::PrintEquipment ()
{
	
	terminal_color (0xAAFFFFFF);
	int a;
	while (1)
	{
		terminal_wprint (MenuX, MenuY, L"� � � � � � � � � �:");
		PrintItems ();
		//terminal_refresh();
		//a = terminal_read();
		//if (a==TK_ESCAPE)
			return;
	
	
	}

	return;
}
