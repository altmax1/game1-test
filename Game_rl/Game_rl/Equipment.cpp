#include "StdAfx.h"
#include "Equipment.h"
#include "Game.h"
#include "LuaAdapter.h"


Equipment::Equipment(void)
{
	HeadEq = -1;
	BodyEq = -1;
	ArmsEq = -1;
	GlovesEq = -1;
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
	Ptr[7] = &LeftArmWeapon;
	Ptr[6] = &RightArmWeapon;

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
			else terminal_print (MenuX+DeltaXName, MenuY+2, MyItems->GetNameById (HeadEq).c_str());
		}
	
		if (MenuState == 2)
		{
			terminal_wprint (MenuX, MenuY+3, L"Тело: ");
			if (BodyEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+3, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+3, MyItems->GetNameById (BodyEq).c_str());
		}
	
		if (MenuState == 3)
		{
			terminal_wprint (MenuX, MenuY+4, L"Руки:");
			if (ArmsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+4, L"Нет");
			else terminal_print (MenuX+DeltaXName, MenuY+4, MyItems->GetNameById (ArmsEq).c_str());
		}

		if (MenuState == 4)
		{
			terminal_wprint (MenuX, MenuY+5, L"Перчатки:");
			if (GlovesEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+5, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+5, MyItems->GetNameById (GlovesEq).c_str());
		}
		
		if (MenuState == 5)
		{
			terminal_wprint (MenuX, MenuY+6, L"Ноги:");
			if (LegsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+6, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+6, MyItems->GetNameById (LegsEq).c_str());
		}
		if (MenuState == 6)
		{
			terminal_wprint (MenuX, MenuY+7, L"Обувь:");
			if (BootsEq < 0)
			terminal_wprint (MenuX+DeltaXName,MenuY+7, L"Нет");
			else terminal_print (MenuX+DeltaXName,MenuY+7, MyItems->GetNameById (BootsEq).c_str());
		}
		
		if (MenuState == 7)
		{
			terminal_wprint (MenuX, MenuY+11, L"Правая рука:");
			if (RightArmWeapon <0 )
				terminal_wprint (MenuX+DeltaXName, MenuY+11, L"Нет");
			else 
			{
				terminal_print (MenuX+DeltaXName, MenuY+11, MyItems->GetNameById (RightArmWeapon).c_str());
				if (MyItems->GetWeaponNeedsAmmo(RightArmWeapon) == 1)
				{
					int AmmoQuantity = MyItems->GetWeaponCurrentAmmoQuantity (RightArmWeapon);
					string temp = MyItems->GetNameById (RightArmWeapon).c_str();
					char *tempchar = new char [4];
					_itoa (AmmoQuantity, tempchar, 10);
					temp = temp+'('+tempchar+')';
					delete [] tempchar;
					terminal_print (MenuX+DeltaXName, MenuY+11, temp.c_str());
				}
			}

		}
		if (MenuState == 8)
		{
			terminal_wprint (MenuX, MenuY+12, L"Левая рука:");
			if (LeftArmWeapon <0 )
				terminal_wprint (MenuX+DeltaXName, MenuY+12, L"Нет");
			else 
				terminal_print (MenuX+DeltaXName, MenuY+12, MyItems->GetNameById (LeftArmWeapon).c_str());
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

void Equipment::SelectEqToWear (std::vector<int> &temp)
{
	
	int menustate = 1;
	int MaxMenuState = temp.size();
	while (1)
	{
		terminal_clear();
		terminal_color (0xAAFFFFFF);
		terminal_wprint (MenuX, MenuY, L"Выберите предмет, который хотите надеть:");
		PrintEqToWear (temp, menustate);
		terminal_refresh();
		int a = terminal_read();
		if (a == TK_UP && menustate >1)
			menustate--;
		if (a == TK_DOWN && menustate < MaxMenuState)
			menustate++;
		if (a == TK_ENTER)
		{
			WearThisItem (temp[menustate-1]);
			return;
		}
		if (a==TK_ESCAPE)
			return;

	
	}

}

void Equipment::WearThisItem (int Num)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Inventory *MyInventory;
	Items *MyItems;
	MyItems = MyGame->GetItems();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	MyInventory = MyGamer->GetInventory();

	int ID = MyInventory->GetIdByNum (Num);
	int Type = MyItems->GetTypeById (ID)-1000000;
	int GlobalType = MyItems->GetGlobalType (ID);
	if (Type >0 && Type <=8 && GlobalType == 1)
		*Ptr [Type-1] = ID;  
	if (GlobalType==0)
		*Ptr [6] = ID;
	MyInventory->RemoveItemFromVector (Num,1);
	LuaMakeSumOfDef();
	return;
}

void Equipment::PrintEqToWear (std::vector<int> &temp, int MenuState)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Inventory *MyInventory;
	Items *MyItems;
	MyItems = MyGame->GetItems();
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	MyInventory = MyGamer->GetInventory();
	vector<int>::iterator p;
	int itera = 1;
	p = temp.begin();
	while (p!= temp.end())
	{
		int ID = MyInventory->GetIdByNum (*p);
		string stemp = MyItems->GetNameById (ID);
		if (itera==MenuState)
			terminal_color (0xFFFFFFFF);
		terminal_print (MenuX,MenuY+1+itera, stemp.c_str());
		if (itera==MenuState)
			terminal_color (0xAAFFFFFF);
		p++;
		itera++;
	
	}

	return;
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
	terminal_wprint (MenuX, MenuY+12, L"Левая рука:");

	if (HeadEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+2, L"Нет");
	else terminal_print (MenuX+DeltaXName, MenuY+2, MyItems->GetNameById (HeadEq).c_str());
	if (BodyEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+3, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+3, MyItems->GetNameById (BodyEq).c_str());
	if (ArmsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+4, L"Нет");
	else terminal_print (MenuX+DeltaXName, MenuY+4, MyItems->GetNameById (ArmsEq).c_str());
	if (GlovesEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+5, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+5, MyItems->GetNameById (GlovesEq).c_str());
	if (LegsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+6, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+6, MyItems->GetNameById (LegsEq).c_str());
	if (BootsEq < 0)
		terminal_wprint (MenuX+DeltaXName,MenuY+7, L"Нет");
	else terminal_print (MenuX+DeltaXName,MenuY+7, MyItems->GetNameById (BootsEq).c_str());
	if (RightArmWeapon<0)
		terminal_wprint (MenuX+DeltaXName,MenuY+11, L"Нет");
	else
		terminal_print (MenuX+DeltaXName,MenuY+11, MyItems->GetNameById (RightArmWeapon).c_str());
	if (LeftArmWeapon<0)
		terminal_wprint (MenuX+DeltaXName,MenuY+12, L"Нет");
	else
		terminal_print (MenuX+DeltaXName,MenuY+12, MyItems->GetNameById (LeftArmWeapon).c_str());
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
	{
		UnWearItem (MenuState);
		return;
	}
	if (*Ptr[MenuState-1] < 0)
		WearItem (MenuState);
	return;

}

void Equipment::WearItem (int MenuState)
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Inventory *MyInventory;
	Gamer *MyGamer;
	MyGamer = MyGame->GetGamer();
	MyInventory = MyGamer->GetInventory();
	vector<int> temp;
	MyInventory->FindItemsByType (temp,1,MenuState);
	if (temp.size() == 0)
		{
			NothingToWear ();
			return;
		}
	SelectEqToWear (temp);
	MyGame->SetPlayerMoved();
	return;	

}

void Equipment::NothingToWear ()
{
	terminal_clear();
	terminal_wprint (MenuX, MenuY, L"Нет подходящего предмета для данного слота.");
	terminal_wprint (MenuX, MenuY+2, L"Вам нечего туда надеть");
	terminal_refresh();
	while ( terminal_read())
		return;

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
		int Stackable = MyItems->GetStackable (*Ptr[MenuState-1]);
		MyInventory ->PutItemInVector (*Ptr[MenuState-1],Stackable,1);
		*Ptr[MenuState-1] = -1;
		LuaMakeSumOfDef();
		MyGame->SetPlayerMoved();
		return;
	}
	

}

int Equipment::GetHeadDef()
{
	if (HeadEq >=0)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		return MyItems->GetDefenseById (HeadEq);
	}
	return 0;
}
int Equipment::GetBodyDef()
{
	if (BodyEq >=0)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		return MyItems->GetDefenseById (BodyEq);
	}
	return 0;
}
int Equipment::GetArmsDef()
{
	if (ArmsEq >=0)
	{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	Items *MyItems;
	MyItems = MyGame->GetItems();
	return MyItems->GetDefenseById (ArmsEq);
	}
	return 0;
}
int Equipment::GetGlovesDef()
{
	if (GlovesEq >=0)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		return MyItems->GetDefenseById (GlovesEq);
	}
	return 0;
}
int Equipment::GetLegsDef()
{
	if (LegsEq >=0)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		return MyItems->GetDefenseById (LegsEq);
	}
	return 0;
}
int Equipment::GetBootsDef()
{
	if (BootsEq >=0)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		return MyItems->GetDefenseById (BootsEq);
	}
	return 0;
}

int Equipment::GetDefBySlot (int Num)
{
	if (Num>0 && Num <=8)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		int ID = *Ptr[Num-1];
		return MyItems->GetDefenseById (ID);	
	}
	return 0;
}

int Equipment::GetDefBySlotAdvansed (int Num, int NumOfDefense)
{
	if (Num>0 && Num <=8)
	{
		Game *MyGame;
		MyGame = Game::GetGameInstance();
		Items *MyItems;
		MyItems = MyGame->GetItems();
		int ID = *Ptr[Num-1];
		return MyItems->GetDefenseByIdAdvanced (ID, NumOfDefense);	
	}
	return 0;
}



int Equipment::GetIdBySlot (int Slot)
{
	if (Slot >= 1 && Slot <=8)
	{
		return *Ptr[Slot-1];
	}
	try{
		throw "BAD_SLOT_ID_IN_Equipment::GetIdBySlot";}
	catch(char *str)//сюда передастся строка
		{
		    cout << str << endl;
			return -1;
		}

}

void Equipment::LuaMakeSumOfDef ()
{
using namespace luabridge;

	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
	LuaAdapter Luaad;
	Luaad.LuaDesc(L);
	luaL_dofile(L, ".\\Files\\lua\\Equipment.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef MakeSumOfEq = getGlobal(L, "MakeSumOfEq");
	  //
	try {
            MakeSumOfEq (Luaad);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }


}

void Equipment::SaveEquipment()
{
	ofstream out(".\\Files\\Save\\equipmetn.sav", ios::binary | ios::out);
	out.write((char*)&HeadEq, sizeof HeadEq);
	out.write((char*)&BodyEq, sizeof BodyEq);
	out.write((char*)&ArmsEq, sizeof ArmsEq);
	out.write((char*)&GlovesEq, sizeof GlovesEq);
	out.write((char*)&LegsEq, sizeof LegsEq);
	out.write((char*)&BootsEq, sizeof BootsEq);
	out.write((char*)&LeftArmWeapon, sizeof LeftArmWeapon);
	out.write((char*)&RightArmWeapon, sizeof RightArmWeapon);
	out.write((char*)&MenuX, sizeof MenuX);
	out.write((char*)&MenuY, sizeof MenuY);
	out.write((char*)&DeltaXName, sizeof DeltaXName);


}

void Equipment::LoadEquipment()
{
	ifstream in(".\\Files\\Save\\equipmetn.sav", ios::binary | ios::in);
	in.read((char*)&HeadEq, sizeof HeadEq);
	in.read((char*)&BodyEq, sizeof BodyEq);
	in.read((char*)&ArmsEq, sizeof ArmsEq);
	in.read((char*)&GlovesEq, sizeof GlovesEq);
	in.read((char*)&LegsEq, sizeof LegsEq);
	in.read((char*)&BootsEq, sizeof BootsEq);
	in.read((char*)&LeftArmWeapon, sizeof LeftArmWeapon);
	in.read((char*)&RightArmWeapon, sizeof RightArmWeapon);
	in.read((char*)&MenuX, sizeof MenuX);
	in.read((char*)&MenuY, sizeof MenuY);
	in.read((char*)&DeltaXName, sizeof DeltaXName);

}
