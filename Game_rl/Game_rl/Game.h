#pragma once
#include "level.h"
#include "Gamer.h"
#include "Items.h"
#include "Interface.h"
#include "X_File.h"
#include "Bestiary.h"
#include "Equipment.h"
#include "Log.h"

#define SLOT_HEAD			1
#define SLOT_BODY			2
#define SLOT_ARMS			3
#define SLOT_GLOVES			4
#define SLOT_LEGS			5
#define SLOT_BOOTS			6
#define SLOT_RWEAPON		7
#define SLOT_LWEAPON		8

#define DEFENSE				1
#define DEF_FIRE			2
#define DEF_COLD			3
#define DEF_NEG_ENERGY		4
#define DEF_POISON			5
#define DEF_ELECTRIC		6
#define	DEF_MAGIC			7
#define DEF_ACIDS			8
#define DEF_BIO_MUTAGEN		9
#define DEF_RADIATION		10

#define DAMAGE				1
#define DAM_FIRE			2
#define DAM_COLD			3
#define DAM_NEG_ENERGY		4
#define DAM_POISON			5
#define DAM_ELECTRIC		6
#define	DAM_MAGIC			7
#define DAM_ACIDS			8
#define DAM_BIO_MUTAGEN		9
#define DAM_RADIATION		10

#define FIRE				2
#define COLD				3
#define NEG_ENERGY			4
#define POISON				5
#define ELECTRIC			6
#define	MAGIC				7
#define ACIDS				8
#define BIO_MUTAGEN			9
#define RADIATION			10



class Game
{
private:
	static Game *MyGame;
	level *MyLevel;
	Gamer *MyGamer;
	Items *MyItems;
	Interface *MyInterface;
	Bestiary *MyBestiary;
	Log *MyLog;
	Game(void);
	int DeveloperMode;
	int FullLogging;
	int PlayerMoved;
	int Moves;

public:
	static Game* GetGameInstance ();
	~Game(void);
	void GameInit ();
	void MakeLog();
	void MakeLevel (int Type, int Width, int Height, int Density);
	void MakeGamer ();
	void MakeItems ();
	void MakeInterface();
	void MakeBestiary ();
	void MakeAIMove ();
	Log* GetLog();
	Items* GetItems ();
	level *GetLevel();
	Gamer* GetGamer();
	Bestiary* GetBestiary();
	Interface* GetInterface();
	void ChangeGameMode ();
	void IncMove (){ Moves++;}
	void SetPlayerMoved () {PlayerMoved = 1 ;IncMove();};
	void ResetPlayerMoved (){PlayerMoved = 0;};
	int GetPlayerMoved () {return PlayerMoved;};
	int GetMoves () {return Moves;};
	int GetDeveloperMode () {return DeveloperMode;};
	int GetFullLogging();

	
};

