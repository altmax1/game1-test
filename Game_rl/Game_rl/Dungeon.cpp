#include "StdAfx.h"
#include "Dungeon.h"
#include "level.h"
#include "Game.h"
using namespace std;


Dungeon::Dungeon()
{
};

Dungeon::~Dungeon()
{

};

Dungeon* Dungeon::MakeDungeon (int Type, int Width, int Height, int Density)
{
	if (Type == 1)
		return new DungeonType1 ( Width,Height,Density);
	if (Type == 2)
		return new DungeonType2 (Width, Height, Density);
}


DungeonType1::DungeonType1(void)
{
	MaxRooms = 20;
	srand (time (0));
	MapWidth = 79;
	MapHeight = 24;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount+1];
}

DungeonType1::DungeonType1(int nums)
{
	MaxRooms = nums;
	srand (time (0));
	MapWidth = 79;
	MapHeight = 24;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount];
}

DungeonType1::DungeonType1(int Width, int Height, int nums)
{
	MaxRooms = nums;
	srand (time (0));
	MapWidth = Width-1;
	MapHeight = Height-1;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount+1];
}

DungeonType1::~DungeonType1(void)
{
	delete [] DungeonCells;
}

void DungeonType1::SetLinearCoordsWide ( vector <room> ::iterator p)
{
	int LeftX = (p->LeftUpCornerX)-1;
	int RightX = (p->LeftUpCornerX)+(p->RoomWidth);
	int UpperY = (p->LeftUpCornerY)-1;
	int DownY = (p->LeftUpCornerY)+(p->RoomHeight);
	for (int x = LeftX; x<= RightX; x++)
		for ( int y = UpperY; y<= DownY; y++)
		{
			int linear=(y*(MapWidth+1))+x;
			p->LinearCoordsWide.insert (linear);
		}	
}

void DungeonType1::DetectCohesion ()
{
	vector <room>::iterator p1,p2;
	p1= Rooms.begin();
	int koef = 1;
	while (p1!=Rooms.end())
	{
		p2 = (Rooms.begin()+koef);
		while (p2!=Rooms.end())
		{
			if (p2!=p1)
			{
				set <int> temp;
				temp.clear();
				set_intersection (p1->LinearCoords.begin(), p1->LinearCoords.end(),
				p2->LinearCoordsWide.begin(), p2->LinearCoordsWide.end(),
				inserter (temp, temp.begin()));
				if (temp.size() >0)
				{
				
					p1->cohesion.push_back (p2->RoomId);
					p2->cohesion.push_back (p1->RoomId);
				}
			}
			p2++;

			
		}
		p1++;
		koef++;
		
	}
	return;
}

void DungeonType1::MakeRooms ()
{
	Game *MyGame;
	MyGame = Game::GetGameInstance();
	level *MyLevel;
	MyLevel = MyGame->GetLevel();
	for (int i=0; i<MaxRooms; i++)
	{
		room TempRoom;
		TempRoom.RoomWidth = (rand () %7)+2;
		TempRoom.RoomHeight = (rand () %7)+2;
		TempRoom.LeftUpCornerX = rand () %(MapWidth - TempRoom.RoomWidth);
		TempRoom.LeftUpCornerY = rand () %(MapHeight - TempRoom.RoomHeight);
		if (TempRoom.LeftUpCornerX == 0)
			TempRoom.LeftUpCornerX  = 1;
		if (TempRoom.LeftUpCornerY == 0)
			TempRoom.LeftUpCornerY = 1;
		TempRoom.RoomId = i;
		TempRoom.RoomFlag = 0;
		Rooms.push_back (TempRoom);	
		LevelRoom Temp2;
		Temp2.LeftX = TempRoom.LeftUpCornerX;
		Temp2.UpY = TempRoom.LeftUpCornerY;
		Temp2.Width = TempRoom.RoomWidth;
		Temp2.Height = TempRoom.RoomHeight;
		MyLevel->AddRoom(Temp2);
	}
	return;

}

void DungeonType1::PlaceRooms ()
{
	for (int i = 0; i <= MapCellsCount; i++)
		DungeonCells [i] = 35; // заполняем поле стенами
	vector <room>::iterator p = Rooms.begin();
	while ( p!= Rooms.end())
	{
		int LeftX = p->LeftUpCornerX;
		int RightX = (p->LeftUpCornerX)+(p->RoomWidth)-1;
		int UpperY = p->LeftUpCornerY;
		int DownY = (p->LeftUpCornerY)+(p->RoomHeight)-1;
		for (int x = LeftX; x<= RightX; x++)
			for ( int y = UpperY; y<= DownY; y++)
			{
				int linear=(y*(MapWidth+1))+x;
				DungeonCells [linear] = 46;
				p->LinearCoords.insert (linear);
			}
		SetLinearCoordsWide (p);
	
		p++;
	}
	return;

}

void DungeonType1::PrintRoomDebug () // потом удалить !!! только для отладки!!!
{
	vector <room>::iterator p;
	p = Rooms.begin();
	while (p!=Rooms.end())
	{
		if (p->cohesion.empty())
		{ 
			set <int>::iterator p3;
			p3 = p->LinearCoords.begin();
			while (p3!=p->LinearCoords.end())
			{
				DungeonCells [*p3] = 32;
			    p3++;
			}

		}
		p++;
	
	}

}

int DungeonType1::DecartToLinear( int x, int y)
{
	return (y*(MapWidth+1))+x;
}

void DungeonType1::PrintDungeon ()
{
	terminal_clear ();
	terminal_refresh ();
	PrintRoomDebug();
	int iter = 0;
	for (int y = 0; y <= MapHeight; y++)
		for (int x = 0; x<=MapWidth; x++)
		{
		terminal_put (x, y, DungeonCells [iter]);
		iter++;
		}
	terminal_refresh();
	return;

}

void DungeonType1::Vremenn()
{
	int i;
	for (i = 0; i < Rooms.size(); i++)
	{
		cout << i << "  " <<Rooms[i].RoomGrafComponent<< endl;
	}
	return;
}

void DungeonType1::DrawPassage (int room1, int room2)
{
	int x1,y1,x2,y2;
	int temp;
	x1 = Rooms[room1].LeftUpCornerX + rand () % Rooms[room1].RoomWidth;
	y1 = Rooms[room1].LeftUpCornerY + rand () % Rooms[room1].RoomHeight;
	x2 = Rooms[room2].LeftUpCornerX + rand () % Rooms[room2].RoomWidth;
	y2 = Rooms[room2].LeftUpCornerY + rand () % Rooms[room2].RoomHeight;
	if (x2>x1)
	{
		for (int i = x1; i<=x2; i++)
		{
			int temp = DecartToLinear (i, y1);
			DungeonCells[temp] = 46;
		}
	}
	if (x2<x1)
	{
		for (int i = x2; i<=x1; i++)
		{
			int temp = DecartToLinear (i, y1);
			DungeonCells[temp] = 46;
		}
	}if (y2>y1)
	{
		for (int i = y1; i<=y2; i++)
		{
			int temp = DecartToLinear (x2, i);
			DungeonCells[temp] = 46;
		}
	}
	if (y2<y1)
	{
		for (int i = y2; i<=y1; i++)
		{
			int temp = DecartToLinear (x2, i);
			DungeonCells[temp] = 46;
		}
	}
	return;

}

void DungeonType1::FindGrafComponents()
{
	GraphComponentCount = 0;
	queue<int> temp;
	for (int i=0; i< Rooms.size(); i++)
		Rooms[i].RoomFlag = 0;
	for (int i=0; i< Rooms.size(); i++)
	{
		if (Rooms[i].RoomFlag!=0)
			continue;
		temp.push (i);
		GraphComponentCount++;
		while (!temp.empty())
		{
			int b;
			b = temp.front();
			temp.pop();
			list <int>::iterator p;
			p = Rooms[b].cohesion.begin();
			while (p!=Rooms[b].cohesion.end())
			{
				int a = *p;
				if (Rooms[a].RoomFlag == 0)
				{	
					temp.push (a);
					Rooms[a].RoomFlag = 2;
				}
				p++;			
			}
			Rooms[b].RoomFlag = 3;
			Rooms[b].RoomGrafComponent = GraphComponentCount;

		}
		
	
	}


}

void DungeonType1::MakePassages ()
{ 
	for (int a=1; a < (GraphComponentCount); a++)
	{
		vector <int> first, second;
		for (int i = 0; i < Rooms.size(); i++)
		{
			if (Rooms[i].RoomGrafComponent == a)
				first.push_back (i);
			if (Rooms[i].RoomGrafComponent == (a+1))
				second.push_back(i);				
		}
		int rand1, rand2;
		rand1 = rand () % (first.size());
		rand2 = rand () % (second.size());
		int randomroom1 = first[rand1];
		int randomroom2 = second[rand2];
		DrawPassage(randomroom1, randomroom2);
	
	}
	return;
}



void DungeonType1::InitDungeon ()
{	
	int i = clock ();
	cout << "MakeRooms ();" << endl;
	MakeRooms ();
	cout << "MakeRooms (); "<< clock()-i<< "ms" << endl;
	i = clock ();
	cout << "PlaceRooms ();" << endl;
	PlaceRooms ();
	cout << "PlaceRooms (); "<< clock()-i<< "ms" << endl;
	i = clock ();
	cout << "PrintDungeon ();" << endl;
	DetectCohesion ();
	cout << "DetectCohesion (); "<< clock()-i<< "ms" << endl;
	i = clock ();
	FindGrafComponents();
	MakePassages();
	PrintDungeon ();
	cout << "PrintRooms (); "<< clock()-i<< "ms" << endl;
	i = clock ();
	cout << "GraphComponentCount  " << GraphComponentCount << endl;
	cout << "GraphComponentCount; "<< clock()-i<< "ms" << endl;
	//Vremenn ();
	Rooms.clear ();
	return;

}


void DungeonType1::ReturnDungeon (level *MyLevel)
{
	MakeRooms();
	PlaceRooms();
	DetectCohesion ();
	FindGrafComponents();
	MakePassages();
	for (int i = 0; i <(MapWidth+1)*(MapHeight+1); i++)
		MyLevel->cells[i].SetBaseType(DungeonCells[i]);
	return;
}


//-------------------------DungeonType2---------------------------

DungeonType2::DungeonType2(void)
{
	MapWidth = 80;
	MapHeight = 40;
	Density = 4;
}

DungeonType2::DungeonType2(int Width, int Height, int nums)
{
	MapWidth = Width;
	MapHeight = Height;
	Density = nums;
	if (Density < 1)
		Density = 1;
	if (Density > 7)
		Density = 7;
}

DungeonType2::~DungeonType2()
{
}

void DungeonType2::InitDungeon()
{
	cells.clear();
	MyCells.clear();
	Rooms.clear();
	FillArrayRandom();
	CellsProcessing();
	ConvertToMyCell();
	FindRooms();
	AddRoomsToVector();
	ConnectRooms();
	
}

void DungeonType2::FillArrayRandom()
{
	srand( time(0) );
	for (int y = 0; y < MapHeight; y++)
		for (int x = 0; x < MapWidth; x++)
		{
			if (x == 0 || y == 0 || y == MapHeight-1 || x == MapWidth-1)
				cells.push_back(100);
			else
				cells.push_back(rand() % 100);
		}
}

void DungeonType2::CellsProcessing()
{
	for (int i = 0; i<Density; i++)
		for (int y = 1; y < MapHeight - 1; y++)
			for (int x = 1; x < MapWidth - 1; x++)
				Averaging(x, y);
}

void DungeonType2::Averaging(int x, int y)
{
	/*for (int a = -1; a<=1; a++)
		for (int b = -1; b <= 1; b++)
		{
			int avg = (cells[DecToLin(x, y)] + cells[DecToLin(x + b, y + a)]) / 2;
			cells[DecToLin(x, y)] = avg;
		}*/
	int avg = 0;
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
		{
			avg = avg + cells[DecToLin(x + b, y + a)];
			
		}
	cells[DecToLin(x, y)] = avg/9;
	
}

int DungeonType2::DecToLin(int x, int y)
{
	return y*MapWidth+x;
}

void DungeonType2::PrintDungeon()
{
	cells.clear();
	MyCells.clear();
	Rooms.clear();
	FillArrayRandom();
	CellsProcessing();
	ConvertToMyCell();
	FindRooms();
	ConnectRooms();
	for (int y = 0; y< MapHeight; y++)
		for (int x = 0; x < MapWidth; x++)
		{
			if (MyCells[DecToLin(x, y)].pasable == 1)
				terminal_put(x, y, '.');
			else
				terminal_put(x, y, '#');
		}
	terminal_refresh();
	cout <<endl<< Rooms.size() << endl;
	for (auto a : Rooms)
	{
		cout << a.size() << endl;
	}
}

void DungeonType2::ConvertToMyCell()
{
	PassableCells = 0;
	for (int i = 0; i < MapHeight*MapWidth; i++)
	{
	 MyCell Temp;
	 if (cells[i] > 47)
	 {
		 Temp.pasable = 0;
		 Temp.visited = 0;
	 }
	 else
	 {
		 Temp.pasable = 1;
		 Temp.visited = 0;
		 PassableCells++;
	 }
	 MyCells.push_back(Temp);
	 }
}

void DungeonType2::FindRooms()
{
	for (int y = 0; y< MapHeight; y++)
		for (int x = 0; x < MapWidth; x++)
		{
			int Lin = DecToLin(x, y);
			if (MyCells[Lin].pasable == 1 && MyCells[Lin].visited == 0)
			{
				vector <int> Stack;
				set<int> Temp;
				int a;
				Stack.push_back(Lin);
				MyCells[Lin].visited = 1;
				while (Stack.size() > 0)
				{
					a = Stack.back();
					Stack.pop_back();
					Temp.insert(a);
					int NewY = a / MapWidth;
					int NewX = a - NewY*MapWidth;
					for (int y2 = -1; y2<=1; y2++)
						for (int x2 = -1; x2 <= 1; x2++)
						{
							int linear2 = DecToLin(NewX + x2, NewY+y2);
							if (MyCells[linear2].pasable == 1 && MyCells[linear2].visited == 0)
							{
								Stack.push_back(linear2);
								MyCells[linear2].visited = 1;
							}


						}


				}

				Rooms.push_back(Temp);
				
			}

		}
	cout << "Rooms:: " << Rooms.size();
	
	for (auto &a : MyCells)
		a.visited = 0;
}

void DungeonType2::DrawLine(int x1, int y1, int x2, int y2)
{
	int x, y, xend, yend, s, dx, dy, d, inc1, inc2;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (dx > dy)
	{
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);
		d = 2 * dy - dx;
		if (x1 < x2)
		{
			x = x1; y = y1; xend = x2;
			if (y1 < y2) s = 1;
			else s = -1;
		}
		else
		{
			x = x2;
			y = y2;
			xend = x1;
			if (y1 > y2) s = 1;
			else s = -1;
		}
		//SetPixel(hdc,x,y,cDraw);

		while (x < xend)
		{
			x++;
			if (d > 0)
			{
				y += s;
				d += inc2;
			}
			else d += inc1;
			// SetPixel(hdc,x,y,cDraw);
			MyCells[DecToLin(x, y)].pasable = 1;
		}
	}
	else
	{
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);
		d = 2 * dx - dy;
		if (y1 < y2)
		{
			y = y1; x = x1; yend = y2;
			if (x1 < x2) s = 1;
			else s = -1;
		}
		else
		{
			y = y2;
			x = x2;
			yend = y1;
			if (x1 > x2)s = 1;
			else s = -1;
		}
		//SetPixel(hdc,x,y,RGB(255,255,255));
		while (y < yend)
		{
			y++;
			if (d > 0)
			{
				x += s;
				d += inc2;
			}
			else d += inc1;
			//  SetPixel(hdc,x,y,RGB(255,255,255));
			MyCells[DecToLin(x, y)].pasable = 1;
		}
	}
	
}

void DungeonType2::ConnectRooms()
{
	while (Rooms.size() > 1)
	{
		int Set1Size = Rooms[0].size();
		int CellNumber = rand() % Set1Size;
		auto p1 = Rooms[0].begin();
		for (int i = 0; i < CellNumber; i++)
			p1++;
		int y1 = *p1 / MapWidth;
		int x1 = *p1 - y1*MapWidth;

		Set1Size = Rooms[1].size();
		CellNumber = rand() % Set1Size;
		auto p2 = Rooms[1].begin();
		for (int i = 0; i < CellNumber; i++)
			p2++;
		int y2 = *p2 / MapWidth;
		int x2 = *p2 - y2*MapWidth;

		DrawLine(x1, y1, x2, y2);
		cout << "DrawLine" << endl;
		Rooms.clear();
		FindRooms();
	}
}

void DungeonType2::ReturnDungeon(level * MyLev)
{
	MyLevel = MyLev;
	InitDungeon();
	for (int i = 0; i <(MapWidth)*(MapHeight); i++)
		if (MyCells[i].pasable == 0)
			MyLevel->cells[i].SetBaseType('#');
		else if (MyCells[i].pasable ==1)
			MyLevel->cells[i].SetBaseType('.');
}

void DungeonType2::AddRoomsToVector()
{
	for (auto vec : Rooms)
	{
		vector<int> temp;
		for (auto a : vec)
		{
			temp.push_back(a);
		}
		MyLevel->AddRoomToRooms2(temp);
	}

}
