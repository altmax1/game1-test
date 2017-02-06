#pragma once
using namespace std;

struct MenuDecorString
{
int CoordX;
int CoordY;
string DecorString;
};

class X_MainMenu
{
private:
	FileContent buffer;
	list <MenuDecorString> DecorStrings;
	string *MenuString;
	int NumberLines;
	int MenuState;
public:
	X_MainMenu(void);
	~X_MainMenu(void);
	void GetMenu ();
	bool ParseFile ();
	void PrintMenu ();
	void BorderPrint (int x, int y, int number);
	void MenuStateUp();
	void MenuStateDown();
	void ParseDecorStrings (int &BufferIterator);
};

