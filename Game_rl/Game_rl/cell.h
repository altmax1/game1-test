#pragma once
using namespace std;
class cell
{
private:
	int tile;
	char visible:1;
	char opaque:1;
	char visited:1;
	char passable:1;
	char empty_cell:1;// 1 ���� ���� ������ � ��� ��������
	list <int> items;
	char creature;

public:
	cell(void);
	~cell(void);
};

