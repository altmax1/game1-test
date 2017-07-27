#include "stdafx.h"
#include "MiniGame.h"

using namespace std;

MiniGame::MiniGame()
{
	for (int i = 0; i <6; i++)
	IntState[i] = 0; // входные интерфейсы
	for (int i = 0; i <20; i++)
	Wire[i] = 0; // провода
	Switcher = 1; //переключатель
	for (int i = 0; i <6; i++)
		Invertor[i] = 1; // инверторы
	for (int i = 0; i <6; i++)
		LogicElements[i] = 0;// логические элементы
	ColorOn = 0xffffffff;
	ColorOff = 0xff7f7f7f;
	CursorPosition = 0;
}


MiniGame::~MiniGame()
{
}

void MiniGame::PrintInterface()
{
	terminal_clear();
	//PrintElements();
	PrintInputInterfaces();
	PrintWires1Level();
	PrintWires2Level();
	PrintWires3Level();
	PrintElements();
	PrintInvertors();
	PrintSwitcher();
	PrintCursor();
	terminal_refresh();
}

void MiniGame::PrintElementBorder(int x, int y)
{
	terminal_color(0xffffffff);
	terminal_put(x, y, 0x250f);
	terminal_put(x, y + 2, 0x2517);
	terminal_put(x + 6, y, 0x2513);
	terminal_put(x + 6, y + 2, 0x251b);
	for (int i = 1; i <= 5; i++)
	{
		terminal_put(x + i, y, 0x2501);
		terminal_put(x + i, y+2, 0x2501);
	}
	terminal_put(x, y + 1, 0x2503);
	terminal_put(x + 6, y + 1, 0x2503);
}

void MiniGame::MiniGameInit()
{
	InitFromFile();
	while (1) {
		Calculate();
		PrintInterface();
		int a = terminal_read();
		if (a == TK_ESCAPE)
			break;
		MoveCursor(a);
		if (a == TK_ENTER)
			ChangeState();

	}
	terminal_color(0xffffffff);
	return;
}

void MiniGame::PrintElements()
{
	PrintElementBorder(37, 8);
	terminal_print(39, 9, GetTypeOfElement(5).c_str());
	PrintElementBorder(33, 14);
	terminal_print(35, 15, GetTypeOfElement(3).c_str());
	PrintElementBorder(41, 14);
	terminal_print(43, 15, GetTypeOfElement(4).c_str());
	PrintElementBorder(29, 20);
	terminal_print(31, 21, GetTypeOfElement(0).c_str());
	PrintElementBorder(37, 20);
	terminal_print(39, 21, GetTypeOfElement(1).c_str());
	PrintElementBorder(45, 20);
	terminal_print(47, 21, GetTypeOfElement(2).c_str());
}

std::string MiniGame::GetTypeOfElement(int Num)
{
	string Temp;
	if (LogicElements[Num] == 0)
		Temp =  "AND";
	else if (LogicElements[Num] == 1)
		Temp =  "OR";
	else if (LogicElements[Num] == 2)
		Temp =  "XOR";
	return Temp;
		
}

void MiniGame::PrintInputInterfaces()
{	
	SetTerminalColor(IntState[0]);
	terminal_put(31, 26, 0x2206);

	SetTerminalColor(IntState[1]);
	terminal_put(33, 26, 0x2206);

	SetTerminalColor(IntState[2]);
	terminal_put(39, 26, 0x2206);

	SetTerminalColor(IntState[3]);
	terminal_put(41, 26, 0x2206);

	SetTerminalColor(IntState[4]);
	terminal_put(47, 26, 0x2206);

	SetTerminalColor(IntState[5]);
	terminal_put(49, 26, 0x2206);
}

void MiniGame::SetTerminalColor(int State)
{
	if (State == 1)
		terminal_color(ColorOn);
	else if (State == 0)
		terminal_color(ColorOff);
}

void MiniGame::PrintWires1Level()
{
	terminal_layer(10);
	SetTerminalColor(Wire[0]);
	terminal_put(31, 26, 0x2579);
	terminal_put(31, 25, 0x2503);
	terminal_put(31, 24, 0x2503);
	terminal_put(31, 23, 0x2503);
	terminal_put(31, 22, 0x257b);

	SetTerminalColor(Wire[1]);
	terminal_put(33, 26, 0x2579);
	terminal_put(33, 25, 0x2503);
	terminal_put(33, 24, 0x2503);
	terminal_put(33, 23, 0x2503);
	terminal_put(33, 22, 0x257b);

	SetTerminalColor(Wire[2]);
	terminal_put(39, 26, 0x2579);
	terminal_put(39, 25, 0x2503);
	terminal_put(39, 24, 0x2503);
	terminal_put(39, 23, 0x2503);
	terminal_put(39, 22, 0x257b);

	SetTerminalColor(Wire[3]);
	terminal_put(41, 26, 0x2579);
	terminal_put(41, 25, 0x2503);
	terminal_put(41, 24, 0x2503);
	terminal_put(41, 23, 0x2503);
	terminal_put(41, 22, 0x257b);

	SetTerminalColor(Wire[4]);
	terminal_put(47, 26, 0x2579);
	terminal_put(47, 25, 0x2503);
	terminal_put(47, 24, 0x2503);
	terminal_put(47, 23, 0x2503);
	terminal_put(47, 22, 0x257b);

	SetTerminalColor(Wire[5]);
	terminal_put(49, 26, 0x2579);
	terminal_put(49, 25, 0x2503);
	terminal_put(49, 24, 0x2503);
	terminal_put(49, 23, 0x2503);
	terminal_put(49, 22, 0x257b);

	terminal_layer(0);
}

void MiniGame::PrintWires2Level()
{
	terminal_layer(10);
	terminal_composition(TK_ON);
	SetTerminalColor(Wire[6]);
	terminal_put(32, 20, 0x2579);
	terminal_put(32, 19, 0x2503);
	terminal_put(32, 18, 0x250f);
	terminal_put(33, 18, 0x2501);
	terminal_put(34, 18, 0x2501);
	terminal_put(35, 18, 0x251b);
	terminal_put(35, 17, 0x257b);

	SetTerminalColor(Wire[7]);
	terminal_put(40, 20, 0x2579);
	terminal_put(40, 19, 0x257b);

	SetTerminalColor(Wire[8]);
	terminal_put(48, 20, 0x2579);
	terminal_put(48, 19, 0x2503);
	terminal_put(48, 18, 0x2513);
	terminal_put(47, 18, 0x2501);
	terminal_put(46, 18, 0x2501);
	terminal_put(45, 18, 0x2517);
	terminal_put(45, 17, 0x257b);

	SetTerminalColor(Wire[9]);
	terminal_put(38, 18, 0x2578);
	terminal_put(37, 18, 0x2517);
	terminal_put(37, 17, 0x257b);

	SetTerminalColor(Wire[10]);
	terminal_put(42, 18, 0x257a);
	terminal_put(43, 18, 0x251b);
	terminal_put(43, 17, 0x257b);

	SetTerminalColor(Wire[11]);
	terminal_put(35, 17, 0x2579);
	terminal_put(35, 16, 0x257b);

	SetTerminalColor(Wire[12]);
	terminal_put(37, 17, 0x2579);
	terminal_put(37, 16, 0x257b);

	SetTerminalColor(Wire[13]);
	terminal_put(43, 17, 0x2579);
	terminal_put(43, 16, 0x257b);

	SetTerminalColor(Wire[14]);
	terminal_put(45, 17, 0x2579);
	terminal_put(45, 16, 0x257b);



}

void MiniGame::PrintWires3Level()
{
	terminal_layer(10);
	terminal_composition(TK_ON);
	SetTerminalColor(Wire[15]);
	terminal_put(36, 14, 0x2579);
	terminal_put(36, 13, 0x2503);
	terminal_put(36, 12, 0x250f);
	terminal_put(37, 12, 0x2501);
	terminal_put(38, 12, 0x2501);
	terminal_put(39, 12, 0x251b);
	terminal_put(39, 11, 0x257b);

	SetTerminalColor(Wire[16]);
	terminal_put(44, 14, 0x2579);
	terminal_put(44, 13, 0x2503);
	terminal_put(44, 12, 0x2513);
	terminal_put(43, 12, 0x2501);
	terminal_put(42, 12, 0x2501);
	terminal_put(41, 12, 0x2517);
	terminal_put(41, 11, 0x257b);

	SetTerminalColor(Wire[17]);
	terminal_put(39, 11, 0x2579);
	terminal_put(39, 10, 0x257b);

	SetTerminalColor(Wire[18]);
	terminal_put(41, 11, 0x2579);
	terminal_put(41, 10, 0x257b);

	SetTerminalColor(Wire[19]);
	terminal_put(40, 8, 0x2579);
	terminal_put(40, 7, 0x2503);
	terminal_put(40, 6, 0x2503);
	terminal_put(40, 5, 0x257b);


}

void MiniGame::PrintInvertors()
{
	terminal_color(0xffffffff);
	if (Invertor[0] == 1)
		terminal_put(35, 17, 0x25d8);
	if (Invertor[1] == 1)
		terminal_put(37, 17, 0x25d8);
	if (Invertor[2] == 1)
		terminal_put(43, 17, 0x25d8);
	if (Invertor[3] == 1)
		terminal_put(45, 17, 0x25d8);
	if (Invertor[4] == 1)
		terminal_put(39, 11, 0x25d8);
	if (Invertor[5] == 1)
		terminal_put(41, 11, 0x25d8);

}

void MiniGame::PrintSwitcher()
{
	if (Switcher == 0)
	{
		SetTerminalColor(Wire[7]);
		terminal_put(40, 19, 0x2579);
		terminal_put(40, 18, 0x252f);
		terminal_put(39, 18, 0x2501);
		terminal_put(38, 18, 0x2501);
		terminal_put(41, 18, 0x2501);
		terminal_put(42, 18, 0x2501);
	}
	else if (Switcher == 1)
	{
		terminal_color(0xffffffff);
		terminal_put(38, 17, 0x250f);
		terminal_put(39, 17, 0x2501);
		terminal_put(40, 17, 0x2501);
		terminal_put(41, 17, 0x2501);
		terminal_put(39, 19, 0x2501);
		terminal_put(40, 19, 0x2501);
		terminal_put(41, 19, 0x2501);
		terminal_put(42, 17, 0x2513);
		terminal_put(42, 19, 0x251b);
		terminal_put(38, 19, 0x2517);
		terminal_put(38, 18, 0x2503);
		terminal_put(42, 18, 0x2503);
		terminal_put(39, 18, 0x2588);
		terminal_put(40, 18, 0x25c4);

	}
	else if (Switcher == 2)
	{
		terminal_color(0xffffffff);
		terminal_put(38, 17, 0x250f);
		terminal_put(39, 17, 0x2501);
		terminal_put(40, 17, 0x2501);
		terminal_put(41, 17, 0x2501);
		terminal_put(39, 19, 0x2501);
		terminal_put(40, 19, 0x2501);
		terminal_put(41, 19, 0x2501);
		terminal_put(42, 17, 0x2513);
		terminal_put(42, 19, 0x251b);
		terminal_put(38, 19, 0x2517);
		terminal_put(38, 18, 0x2503);
		terminal_put(42, 18, 0x2503);
		terminal_put(41, 18, 0x2588);
		terminal_put(40, 18, 0x25ba);

	}
}

void MiniGame::PrintCursor()
{
	if (CursorPosition == 0)
		PrintCursorBorder(30, 25);
	if (CursorPosition == 1)
		PrintCursorBorder(32, 25);
	if (CursorPosition == 2)
		PrintCursorBorder(38, 25);
	if (CursorPosition == 3)
		PrintCursorBorder(40, 25);
	if (CursorPosition == 4)
		PrintCursorBorder(46, 25);
	if (CursorPosition == 5)
		PrintCursorBorder(48, 25);
	if (CursorPosition == 6)
		PrintBigCursorBorder(38, 17);
	
}

void MiniGame::PrintCursorBorder(int x, int y)
{
	terminal_color("yellow");
	terminal_put(x, y, 0x250f);
	terminal_put(x + 1, y, 0x2501);
	terminal_put(x + 2, y, 0x2513);
	terminal_put(x + 2, y + 1, 0x2503);
	terminal_put(x + 2, y + 2, 0x251b);
	terminal_put(x + 1, y + 2, 0x2501);
	terminal_put(x, y + 2, 0x2517);
	terminal_put(x, y + 1, 0x2503);
}

void MiniGame::PrintBigCursorBorder(int x, int y)
{
	terminal_color("yellow");
	terminal_put(x, y, 0x250f);
	terminal_put(x + 1, y, 0x2501);
	terminal_put(x + 2, y, 0x2501);
	terminal_put(x + 3, y, 0x2501);
	terminal_put(x + 4, y, 0x2513);
	terminal_put(x + 4, y + 1, 0x2503);
	terminal_put(x + 4, y + 2, 0x251b);
	terminal_put(x + 1, y + 2, 0x2501);
	terminal_put(x + 2, y + 2, 0x2501);
	terminal_put(x + 3, y + 2, 0x2501);
	terminal_put(x, y + 2, 0x2517);
	terminal_put(x, y + 1, 0x2503);
}

void MiniGame::MoveCursor(int a)
{
	if (a == TK_RIGHT)
	{
		if (CursorPosition < 5)
			CursorPosition++;
		else if (CursorPosition == 5 && Switcher != 0)
		{
			TempCursorPosition = 5;
			CursorPosition++;
		}
	}
	if (a == TK_LEFT)
	{
		if (CursorPosition > 0)
			CursorPosition--;
	}
	if (a == TK_UP)
	{
		if (CursorPosition != 6 && Switcher != 0)
		{
			TempCursorPosition = CursorPosition;
			CursorPosition = 6;
		}

	}
	if (a == TK_DOWN)
	{
		
		if (CursorPosition == 6)
			CursorPosition = TempCursorPosition;
	}
}

void MiniGame::ChangeState()
{
	if (CursorPosition < 6)
		IntState[CursorPosition] = ~(IntState[CursorPosition]) & 0b00000001;
	//cout << CursorPosition << " " << IntState[CursorPosition];
	if (CursorPosition == 6)
	{
		if (Switcher == 1)
			Switcher = 2;
		else if (Switcher == 2)
			Switcher = 1;
	}
}

void MiniGame::Calculate()
{
	for (int i = 0; i < 6; i++)
		Wire[i] = IntState[i];
	Wire[6] = LogicElementCalculate(Wire[0], Wire[1], 0);
	Wire[7] = LogicElementCalculate(Wire[2], Wire[3], 1);
	Wire[8] = LogicElementCalculate(Wire[4], Wire[5], 2);
	if (Switcher == 0)
	{
		Wire[9] = Wire[7];
		Wire[10] = Wire[7];
	}

	if (Switcher == 1)
	{
		Wire[9] = Wire[7];
		Wire[10] = 0;
	}

	if (Switcher == 2)
	{
		Wire[10] = Wire[7];
		Wire[9] = 0;
	}
	Wire[11] = InvertorCalculate(Wire[6], 0);
	Wire[12] = InvertorCalculate(Wire[9], 1);
	Wire[13] = InvertorCalculate(Wire[10], 2);
	Wire[14] = InvertorCalculate(Wire[8], 3);
	Wire[15] = LogicElementCalculate(Wire[11], Wire[12], 3);
	Wire[16] = LogicElementCalculate(Wire[13], Wire[14], 4);
	Wire[17] = InvertorCalculate(Wire[15], 4);
	Wire[18] = InvertorCalculate(Wire[16], 5);
	Wire[19] = LogicElementCalculate(Wire[17], Wire[18], 5);

}

int MiniGame::LogicElementCalculate(int a, int b, int Num)
{
	if (LogicElements[Num] == 0)
		return a&b;
	else if (LogicElements[Num] == 1)
		return a | b;
	else if (LogicElements[Num] == 2)
		return (a^b) & 0b00000001;
	return 0;
}

int MiniGame::InvertorCalculate(int WireIn, int Num)
{
	if (Invertor[Num] == 1)
		return (~WireIn) & 0b00000001;
	else
		return WireIn;
}

void MiniGame::CalculateAllVariants()
{
	ofstream fout;
	fout.open(".\\Files\\MiniGame\\MiniGame6-3-2-1.dat", ios_base::trunc | ios_base::out);
	Variants = 0;
	for (int i = 0; i < 14; i++)
		A[i] = 0;
	int limits[14] = {2,2,2,2,2,2,2,1,1,1,1,1,1,1};
	int counter = 0;
	while (A[13] < limits[13])
	{
		int i = 0;
		while (A[i] >= limits[i])
		{
			A[i] = 0;
			i++;
		}
		A[i]++;
		counter++;
		for (int k = 0; k < 6; k++)
			LogicElements[k] = A[k];
		Switcher = A[6];
		for (int k = 7; k < 13; k++)
			Invertor[k-7] = A[k];

		CalculateInterfaces( fout );
		if ((counter % 1000) == 0)
		{
			cout << "Total: " << counter;
			cout << "  Soluble " << Variants << endl;
		}

	}
	//cout << counter << endl;
	fout.close();
}

void MiniGame::CalculateInterfaces(ofstream &fout)
{
	int Soluble = 0;
	for (int i = 0; i < 6; i++)
		IntState[i] = 0;
	Calculate();
	if (Wire[19] == 1)
		return;

	int B[7] = { 0 };
	int limits[7] = {1,1,1,1,1,1,1 };
	
	while (B[6] < limits[6])
	{
		int i = 0;
		while (B[i] >= limits[i])
		{
			B[i] = 0;
			i++;
		}
		B[i]++;
		for (int m = 0; m < 6; m++)
			IntState[m] = B[m];
		Calculate();
		if (Wire[19] == 1)
		{
			Soluble = 1;
			if ((B[1] + B[2] + B[0] + B[3] + B[4] + B[5]) <= 1)
				return;
		}
		
	}
	if (Soluble == 1)
	{
		Variants++;
		for (int aa = 0; aa < 13; aa++)
			fout << A[aa];
		fout << endl;

	}

}

void MiniGame::InitFromFile()
{
	srand(time(0));
	ifstream fin;
	fin.open(".\\Files\\MiniGame\\MiniGame6-3-2-1.dat", ios_base::in);
	char temp[15];
	fin.seekg(0,fin.end);
	int FileSize = fin.tellg();
	int StringCount = FileSize / 15;
	int MyString = rand() % StringCount;
	fin.seekg(0, fin.beg);// + MyString * 15);
	fin.seekg(MyString * 15);
	fin.getline(temp, 15);
	cout << temp<<endl;
	string t1 = temp;
	string temp2;
	for (int i = 0; i < 6; i++)
	{
		temp2 = t1.at(i);
		LogicElements[i] = atoi(temp2.c_str());
		temp2 = t1.at(i + 7);
		Invertor[i] = atoi(temp2.c_str());
	}
	temp2 = t1.at(6);
	Switcher = atoi(temp2.c_str());
	fin.close();
}


