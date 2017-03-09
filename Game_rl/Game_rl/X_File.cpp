#include "StdAfx.h"
#include "X_File.h"
#include "Game.h"

using namespace std;
using namespace luabridge;
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

void X_File::X_ParseIniFile ( FileContent &MyFile, vector <map <string, string>> &MyVector)
{
        
		MyVector.clear();
		int iter;
        iter = 0;
        while (iter < MyFile.lenght)
        {
                map <string,string>::iterator p;
                map <string,string> TempMap;
                string p1,p2;
                while (MyFile.content[iter]!= '[')
                {	
                        iter++;
                        if (iter>= MyFile.lenght) break;
                }
                iter++;
                p1.clear(); p2.clear();
                while(MyFile.content[iter]!= ']')
                {
                        p1+= MyFile.content[iter];
                        iter++;
                        if (iter>= MyFile.lenght) break;
                }
                iter++;
                while((MyFile.content[iter]== '\r')||(MyFile.content[iter]== '\n'))
                        {
                                iter++;
                                if (iter>= MyFile.lenght) break;
                        }
                TempMap.insert (pair <string, string> ("ID", p1));
                while ((MyFile.content[iter]!= '[') && (iter <MyFile.lenght ))
                {	
                        p1.clear(); p2.clear();
                        while (MyFile.content[iter]!= '=')
                        {
                                p1+= MyFile.content[iter];
                                iter++;
                                if (iter>= MyFile.lenght) break;
                        }
                        iter++;
                        while((MyFile.content[iter]!= '\r')&&(MyFile.content[iter]!= '\n'))
                        {
                                p2+= MyFile.content[iter];
                                iter++;
                                if (iter>= MyFile.lenght) break;
                        }
                        while((MyFile.content[iter]== '\r')||(MyFile.content[iter]== '\n'))
                        {
                                iter++;
                                if (iter>= MyFile.lenght) break;
                        }
                        TempMap.insert (pair <string, string> (p1, p2));
                        
                }
                
				MyVector.push_back (TempMap);

        }

return;
}

