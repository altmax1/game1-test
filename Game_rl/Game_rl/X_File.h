#pragma once
using namespace std;

struct FileContent
{
int lenght;
char* content;
};

class X_File
{
private:
public:
	X_File(void);
	~X_File(void);
	static void X_ReadFile ( LPCTSTR filename, FileContent &fc);
	static void X_ParseIniFile ( FileContent &MyFile, vector <map <string, string>> &MyVector);
};

