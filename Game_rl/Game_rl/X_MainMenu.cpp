#include "StdAfx.h"
#include "stdafx.h"
#include "X_File.h"
#include "X_MainMenu.h"


using namespace std;


X_MainMenu::X_MainMenu(void)
{
	GetMenu ();
	MenuState = 0;
	if ( !ParseFile() ) cout << "Parse ERROR!!!";

}


X_MainMenu::~X_MainMenu(void)
{
	delete [] buffer.content;
	delete [] MenuString;
}

void X_MainMenu::GetMenu ()
{
	X_File::X_ReadFile ((LPCTSTR)L"MainMenu.txt", buffer);
	return;
}
void X_MainMenu::ParseDecorStrings (int &BufferIterator)
{
	return;
}

bool X_MainMenu::ParseFile ()
{
	int BufferIterator = 0;
	string temp;
	temp += buffer.content[BufferIterator];//загоняем первый символ в темп
	NumberLines = atoi (temp.c_str()); //преобразуем в инт
	if ( NumberLines == 0 ) return false;
	do	{BufferIterator++;
		if ( BufferIterator > buffer.lenght+1 ) return false;	
		} while (buffer.content[BufferIterator] != '\n'); //идем до перевода строки
	BufferIterator++;
	while (buffer.content[BufferIterator] == '\n' || buffer.content[BufferIterator] == 'r') //теперь если много переводов пока не закончатся
		BufferIterator++;
	
	MenuString = new string [NumberLines];

	for (int i =0; i<NumberLines; i++)  // заполняем само меню
		{while (buffer.content[BufferIterator] != '\n')
			{MenuString[i] += buffer.content[BufferIterator];
			 BufferIterator++;
			 if ( BufferIterator > buffer.lenght+1 ) return true; //вышли за пределы буфера
			}
		while (buffer.content[BufferIterator] == '\n' || buffer.content[BufferIterator] == 'r') //пролистываем пустые строки и переводы
			{BufferIterator++;
			if ( BufferIterator > buffer.lenght+1 ) return false; //вышли за пределы буффера
			}

		}
	ParseDecorStrings (BufferIterator);
	return true;

}

void X_MainMenu::BorderPrint (int x, int y, int number)
{
	int lenght;
	lenght = MenuString[number].size()/2+2;
	terminal_put (x-1, y-1, 9487);
	terminal_put (x-1, y+1, 9495);
	terminal_put (x+1+lenght, y-1, 9491);
	terminal_put (x+1+lenght, y+1,9499);
	for (int i = 0; i<=lenght; i++)
	{
		terminal_put (x+i, y-1, 9473);
		terminal_put (x+i, y+1, 9473);
	}
	terminal_put (x-1, y, 9475);
	terminal_put (x+1+lenght, y, 9475);
	return;

}

void X_MainMenu::MenuStateUp()
{
	if (MenuState == 0)
		return;
	MenuState--;
	return;
}

void X_MainMenu::MenuStateDown()
{
	if (MenuState == NumberLines-1)
		return;
	MenuState++;
	return;
}

void X_MainMenu::PrintMenu()
{
	int TerminalRead;
	while (1)
	{
	terminal_clear();
	for (int i = 0; i< NumberLines; i++)
	{	
		int x, y;
		x = 20;
		y = 7+i*2;
		terminal_print (x, y, MenuString [i].c_str());
		if (MenuState == i)
		{
		BorderPrint (x,y,i);
		}
	
	}
	terminal_refresh();
	TerminalRead = terminal_read();
	if (TerminalRead == TK_UP)
		MenuStateUp();
	if (TerminalRead == TK_DOWN)
		MenuStateDown();
	if (TerminalRead == TK_ESCAPE)
		{terminal_close();
		return;
		}

	}

}