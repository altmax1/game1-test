#pragma once

struct FileContent
{
int lenght;
unsigned char* content;
};

class X_File
{
private:
public:
	X_File(void);
	~X_File(void);
	static void X_ReadFile ( LPCTSTR filename, FileContent &fc);

};

