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
public:
	X_MainMenu(void);
	~X_MainMenu(void);
	void GetMenu ();
	void PrintBuffer ();
	bool ParseFile ();
	void PrintFile ();
};

