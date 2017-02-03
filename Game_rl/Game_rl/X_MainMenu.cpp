#include "StdAfx.h"
#include "stdafx.h"
#include "X_File.h"
#include "X_MainMenu.h"


using namespace std;


X_MainMenu::X_MainMenu(void)
{
	GetMenu ();
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

bool X_MainMenu::ParseFile ()
{
	int BufferIterator = 0;
	string temp;
	temp += buffer.content[BufferIterator];//�������� ������ ������ � ����
	NumberLines = atoi (temp.c_str()); //����������� � ���
	if ( NumberLines == 0 ) return false;
	do	{BufferIterator++;
		if ( BufferIterator > buffer.lenght+1 ) return false;	
		} while (buffer.content[BufferIterator] != '\n'); //���� �� �������� ������
	BufferIterator++;
	while (buffer.content[BufferIterator] == '\n' && buffer.content[BufferIterator] == 'r') //������ ���� ����� ��������� ���� �� ����������
		BufferIterator++;
	
	MenuString = new string [NumberLines];

	for (int i =0; i<NumberLines; i++)  // ��������� ���� ����
		{while (buffer.content[BufferIterator] != '\n')
			{MenuString[i] += buffer.content[BufferIterator];
			 BufferIterator++;
			 if ( BufferIterator > buffer.lenght+1 ) return true; //����� �� ������� ������
			}
		while (buffer.content[BufferIterator] == '\n' || buffer.content[BufferIterator] == 'r') //������������ ������ ������ � ��������
			{BufferIterator++;
			if ( BufferIterator > buffer.lenght+1 ) return false; //����� �� ������� �������
			}

		}

	return true;

}

void X_MainMenu::PrintFile()
{
	for (int i =0; i<NumberLines; i++)
		{
			cout << MenuString [i] << endl;
		}

}