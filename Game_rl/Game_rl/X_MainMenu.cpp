#include "StdAfx.h"
#include "X_File.h"
#include "X_MainMenu.h"


using namespace std;


X_MainMenu::X_MainMenu(void)
{
}


X_MainMenu::~X_MainMenu(void)
{
	delete [] buffer.content;
}

void X_MainMenu::GetMenu ()
{
	X_File::X_ReadFile ((LPCTSTR)L"MainMenu.txt", buffer);
	
	return;
}

void X_MainMenu::PrintBuffer ()
{
	int size;
	size = buffer.lenght;
	
	for (int i = 0; i < size; i++)
	{
	cout << buffer.content[i];
	
	}
	return;

}