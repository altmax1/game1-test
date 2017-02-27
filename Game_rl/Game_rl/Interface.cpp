#include "StdAfx.h"
#include "Interface.h"
#include "Game.h"




Interface::Interface(void)
{
	ReadIniFile();
}


Interface::~Interface(void)
{
}

void Interface::ReadIniFile()
{
	FileContent MyFile;
	vector <map <string,string>> temp;
	X_File::X_ReadFile ((LPCTSTR)L".\\Files\\Interface.ini", MyFile);
	X_File::X_ParseIniFile (MyFile, temp);
	map <string,string>::iterator MapPtr;
	MapPtr = temp[0].find("WindowHeight");
	WindowHeight = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("WindowWidth");
	WindowWidth = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("FOVHeight");
	FOVHeight = atoi(MapPtr->second.c_str());
	MapPtr = temp[0].find("FOVWidth");
	FOVWidth = atoi(MapPtr->second.c_str());
	cout << FOVWidth;

}
void Interface::PrintFOV ()
{

}