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

int X_MainMenu::ParseNumber (int &BufferIterator)
{
	string temp;
	int number;
	temp += buffer.content[BufferIterator];
	if (buffer.content[BufferIterator+1] != '\n' || buffer.content[BufferIterator+1] != '\r')
		temp += buffer.content[BufferIterator+1];
	do	{BufferIterator++;
		if ( BufferIterator > buffer.lenght+1 )
			return false;	
		} while (buffer.content[BufferIterator] != '\n'); //идем до перевода строки
	BufferIterator++;
	while (buffer.content[BufferIterator] == '\n' || buffer.content[BufferIterator] == '\r') //теперь если много переводов пока не закончатся
		BufferIterator++;
	number = atoi (temp.c_str());
	return number;
}

string X_MainMenu::ParseString (int &BufferIterator)
{
	string temp;
	while (buffer.content[BufferIterator] != '\n')
			{temp += buffer.content[BufferIterator];
			 BufferIterator++;
			 if ( BufferIterator > buffer.lenght+1 ) return temp; //вышли за пределы буфера
			}
		while (buffer.content[BufferIterator] == '\n' || buffer.content[BufferIterator] == 'r') //пролистываем пустые строки и переводы
			{BufferIterator++;
			if ( BufferIterator > buffer.lenght+1 ) return temp; //вышли за пределы буффера
			}
	return temp;
	
}

void X_MainMenu::ParseDecorStrings (int &BufferIterator)
{
	
	while (BufferIterator < buffer.lenght)
	{
		MenuDecorString temp;
		temp.CoordX = ParseNumber (BufferIterator);
		temp.CoordY = ParseNumber (BufferIterator);
		temp.DecorString = ParseString (BufferIterator);
		DecorStrings.push_back (temp);
	
	}
	return;
}

void X_MainMenu::DecorStringsPrint ()
{
	list <MenuDecorString>::iterator p = DecorStrings.begin();
		
	while (p != DecorStrings.end())
	{
		int x,y;
		x = p->CoordX;
		y = p->CoordY;
		const char *s = p->DecorString.c_str(); 

		terminal_print (x,y,s);
		p++;
	}
		
	return;
}

bool X_MainMenu::ParseFile ()
{
	int BufferIterator = 0;
	NumberLines = ParseNumber (BufferIterator);
	MenuString = new string [NumberLines];
	for (int i =0; i<NumberLines; i++)  // заполняем само меню
		MenuString[i] = ParseString (BufferIterator);
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
	DecorStringsPrint();
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