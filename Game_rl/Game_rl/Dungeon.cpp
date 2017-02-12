#include "StdAfx.h"
#include "Dungeon.h"
using namespace std;


Dungeon::Dungeon(void)
{
	MaxRooms = 20;
	srand (time (0));
	MapWidth = 79;
	MapHeight = 24;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount];
}

Dungeon::Dungeon(int nums)
{
	MaxRooms = nums;
	srand (time (0));
	MapWidth = 79;
	MapHeight = 24;
	MapCellsCount = (MapWidth+1)*(MapHeight+1)-1;
	DungeonCells = new char [ MapCellsCount];
}


Dungeon::~Dungeon(void)
{
	delete [] DungeonCells;
}

void Dungeon::SetLinearCoordsWide ( vector <room> ::iterator p)
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

void Dungeon::DetectCohesion ()
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

void Dungeon::MakeRooms ()
{
	for (int i=0; i<MaxRooms; i++)
	{
		room TempRoom;
		TempRoom.RoomWidth = (rand () %7)+2;
		TempRoom.RoomHeight = (rand () %7)+2;
		TempRoom.LeftUpCornerX = rand () %(MapWidth - TempRoom.RoomWidth);
		TempRoom.LeftUpCornerY = rand () %(MapHeight - TempRoom.RoomHeight);
		TempRoom.RoomId = i;
		TempRoom.RoomFlag = 0;
		Rooms.push_back (TempRoom);		
	
	}
	return;

}

void Dungeon::PlaceRooms ()
{
	for (int i = 0; i <= MapCellsCount; i++)
		DungeonCells [i] = 35; // ��������� ���� �������
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

void Dungeon::PrintRoomDebug () // ����� ������� !!! ������ ��� �������!!!
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

int Dungeon::DecartToLinear( int x, int y)
{
	return (y*(MapWidth+1))+x;
}

void Dungeon::PrintDungeon ()
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

void Dungeon::Vremenn()
{
	int i;
	for (i = 0; i < Rooms.size(); i++)
	{
		cout << i << "  " <<Rooms[i].RoomGrafComponent<< endl;
	}
	return;
}

void Dungeon::DrawPassage (int room1, int room2)
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

void Dungeon::FindGrafComponents()
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

void Dungeon::MakePassages ()
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
		cout << randomroom1 << "   "<< randomroom2<< endl;
		

	}
	return;
}



void Dungeon::InitDungeon ()
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