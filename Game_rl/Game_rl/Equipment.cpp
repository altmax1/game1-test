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

	Ptr[0] = &HeadEq;
	Ptr[1] = &BodyEq;
	Ptr[2] = &ArmsEq;
	Ptr[3] = &GlovesEq;
	Ptr[4] = &LegsEq;
	Ptr[5] = &BootsEq;
	Ptr[6] = &LeftArmWeapon;
	Ptr[7] = &RightArmWeapon;

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
			terminal_wprint (MenuX, MenuY+2, L"Голова:");
			if (HeadEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+2, L"Нет");
			else terminal_print (MenuX+DeltaXName, MenuY+2, MyItems->GetNameOfArmour (HeadEq).c_str());
		}
	
		if (MenuState == 2)
		{
			terminal_wprint (MenuX, MenuY+3, L"Тело: ");
			if (BodyEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+3, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+3, MyItems->GetNameOfArmour (BodyEq).c_str());
		}
	
		if (MenuState == 3)
		{
			terminal_wprint (MenuX, MenuY+4, L"Руки:");
			if (ArmsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+4, L"Нет");
			else terminal_print (MenuX+DeltaXName, MenuY+4, MyItems->GetNameOfArmour (ArmsEq).c_str());
		}

		if (MenuState == 4)
		{
			terminal_wprint (MenuX, MenuY+5, L"Перчатки:");
			if (GlovesEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+5, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+5, MyItems->GetNameOfArmour (GlovesEq).c_str());
		}
		
		if (MenuState == 5)
		{
			terminal_wprint (MenuX, MenuY+6, L"Ноги:");
			if (LegsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+6, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+6, MyItems->GetNameOfArmour (LegsEq).c_str());
		}
		if (MenuState == 6)
		{
			terminal_wprint (MenuX, MenuY+7, L"Обувь:");
			if (BootsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+7, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+7, MyItems->GetNameOfArmour (BootsEq).c_str());
		}
		
		if (MenuState == 7)
		{
			terminal_wprint (MenuX, MenuY+11, L"Правая рука:");
		}
		if (MenuState == 8)
		{
			terminal_wprint (MenuX, MenuY+12, L"ГЛевая рука:");
		}
		
		terminal_refresh();
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
		if (a == TK_ENTER)
			MakeChoise (MenuState);
		
	
	}
}

void Equipment::PrintItems ()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();

	terminal_wprint (MenuX, MenuY+2, L"Голова:");
	terminal_wprint (MenuX, MenuY+3, L"Тело: ");
	terminal_wprint (MenuX, MenuY+4, L"Руки:");
	terminal_wprint (MenuX, MenuY+5, L"Перчатки:");
	terminal_wprint (MenuX, MenuY+6, L"Ноги:");
	terminal_wprint (MenuX, MenuY+7, L"Обувь:");
	terminal_wprint (MenuX, MenuY+9, L"Оборудование/вооружение:");
	terminal_wprint (MenuX, MenuY+11, L"Правая рука:");
	terminal_wprint (MenuX, MenuY+12, L"ГЛевая рука:");

	if (HeadEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+2, L"Нет");
	else terminal_print (MenuX+DeltaXName, MenuY+2, MyItems->GetNameOfArmour (HeadEq).c_str());
	if (BodyEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+3, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+3, MyItems->GetNameOfArmour (BodyEq).c_str());
	if (ArmsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+4, L"Нет");
	else terminal_print (MenuX+DeltaXName, MenuY+4, MyItems->GetNameOfArmour (ArmsEq).c_str());
	if (GlovesEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+5, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+5, MyItems->GetNameOfArmour (GlovesEq).c_str());
	if (LegsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+6, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+6, MyItems->GetNameOfArmour (LegsEq).c_str());
	if (BootsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+7, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+7, MyItems->GetNameOfArmour (BootsEq).c_str());
}
void Equipment::PrintEquipment ()
{
	
	terminal_color (0xAAFFFFFF);
	int a;
	while (1)
	{
		terminal_wprint (MenuX, MenuY, L"Э К И П И Р О В К А:");
		PrintItems ();
		//terminal_refresh();
		//a = terminal_read();
		//if (a==TK_ESCAPE)
			return;
	
	
	}

	return;
}

void Equipment::MakeChoise (int MenuState)
{
	if (*Ptr[MenuState-1] >=0)
		UnWearItem (MenuState);
	if (*Ptr[MenuState-1] < 0)
		WearItem (MenuState);
	return;

}

void Equipment::WearItem (int MenuState)
{

}

void Equipment::UnWearItem (int MenuState)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	Inventory *MyInventory;
	MyInventory = MyGamer->GetInventory();
	terminal_clear ();
	terminal_color (0xAAFFFFFF);
	terminal_printf (MenuX, MenuY, L"Вы действительно хотите снять");
	terminal_color (0xFFFFFFFF);
	string Temp;
	Temp = MyItems->GetNameById (*Ptr[MenuState-1])+'?';
	terminal_printf (MenuX, MenuY+2, Temp.c_str());
	terminal_color (0xAAFFFFFF);
	terminal_printf (MenuX, MenuY+4, L"ДА (Y) или НЕТ (N) - нажмите клавишу");
	terminal_refresh();
	int a;
	a = terminal_read();
	if (a== TK_N)
		return;
	if (a == TK_Y)
	{
		MyInventory ->PutItemInVector (*Ptr[MenuState-1],0,1);
		*Ptr[MenuState-1] = -1;
		return;
	}
	

}
