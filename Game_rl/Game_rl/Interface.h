#pragma once

class Interface
{
private:
	int LevelWidth; //размер от 1!!
	int LevelHeight;
	int WindowWidth;
	int WindowHeight;
	int FOVHeight;
	int FOVWidth;

public:
	void ReadIniFile ();
	void PrintFOV ();
	Interface(void);
	~Interface(void);
};

