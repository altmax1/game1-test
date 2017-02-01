#pragma once
using namespace std;
class X_cell
{
private:
	int tile;
	char visible:1;
	char opaque:1;
	char visited:1;
	char passable:1;
	char empty_cell:1;// 1 если тайл пустой и без эффектов
	list <int> items;
	char creature;

public:
	X_cell(void);
	~X_cell(void);
};

