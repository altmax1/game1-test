#include "StdAfx.h"
#include "X_File.h"

using namespace std;

X_File::X_File(void)
{
}


X_File::~X_File(void)
{
}

void X_File::X_ReadFile ( LPCTSTR filename, FileContent &fc)  // читаем произвольный файл в структуру FileContent
{													// и возвращаем ссылку на эту структуру.
	//FileContent fc;
	HANDLE file;
	DWORD size;

	file = CreateFile 
	(
		filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		
	);

	if ( file == INVALID_HANDLE_VALUE )
	{
		cout << "INVALID_HANDLE_VALUE in X_File.cpp X_ReadFile()"<<endl;
		cout << filename << endl;
		return;
	}

	size = GetFileSize ( file, NULL);
	fc.lenght = size;
	fc.content = new char [size];

	DWORD offset, read;
	offset = 0;
	read = 0;
	while ( offset < size)
	{
		ReadFile ( file, (LPVOID) (fc.content + offset), size, &read, NULL);
		offset += read;	
	}

	CloseHandle ( file);

	

	return;
}