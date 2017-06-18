#pragma once
class Beast
{
private:
	int IsDead;
	int ID;
	int NumInVector;
	int CoordX;
	int CoordY;
	std::string Name;
	std::string RName;
	std::string RDesc;
	int HP;  // Здоровье
	int MaxHP;
	int Energy;  // Энергия - аналог маны
	int RangeOfSight; //расстояние на которое видят
	int Speed; // Скороость передвижения
	int RegenHP; //Скорость регенерации здоровья
	int RegenEnergy;  // Скорость регенерации энергии
	int LevelOfBeast; //виртуальный уровень
	int Defense[10];  //уровень защиты
	int MaxAttack; // максимальная атака
	int MinAttack; // минимальная атака
	int AttackType; //тип атаки
	int Dex;  // ловкость
	int Str;  //сила
	int FlyAble:1; //способен к полету?
	int Fly:1; //летает ли сейчас?
	int Sleep:1;   // спит?
	int Active:1;  //активен или ждёт
	int Magic:1;  //пользуется ли магией
	int Behavior; // тип поведения 
	std::vector <int> Effects; // наложенные эффекты
	std::vector <int> EffectsTime; // время эффектов
	std::list <int> NextStep; // следующее действие
	int CharCode;
	int ColorVisible;
	int ColorNotVisible;
	int MovePoints;
	

public:
	Beast(void);
	~Beast(void);
	void LuaReg (lua_State* L);
	void MakeMove ();
	int MoveCreature (int x, int y, int MyMode=0);

	//----Setters AND Getters
	void SetIsDead (int a);
	int GetIsDead () const;
	void SetID (int ID);
	int GetID () const; 
	void SetCoordX(int a);
	void SetCoordY(int a);
	int GetCoordX () const;
	int GetCoordY () const;
	void SetName (std::string S);
	std::string GetName () const;
	void SetRName (std::string S);
	std::string GetRName () const;
	void SetRDesc (std::string S);
	std::string GetRDesc () const;
	int GetMaxHP () {return MaxHP;};
	void SetMaxHP (int a) {MaxHP = a;};
	void SetHP (int a);
	int GetHP () const;
	void SetEnergy (int a);
	int GetEnergy () const;
	void SetRangeOfSight (int a);
	int GetRangeOfSight () const;
	void SetSpeed (int a);
	int GetSpeed () const;
	void SetRegenHP (int a);
	int GetRegenHp () const;
	void SetRegenEnergy (int a);
	int GetRegenEnergy () const;
	void SetLevelOfBeast (int a);
	int GetLevelOfBeast () const;
	void SetDefense (int a);
	int GetDefence () const;
	void SetDefenseAdvansed (int def, int NumOfDef);
	int GetDefenseAdvansed (int NumOfDef);
	void SetMaxAttack (int a);
	int GetMaxAttack () const;
	void SetMinAttack (int a);
	int GetMinAttack () const;
	void SetAttackType (int a);
	int GetAttackType () const;
	void SetDex (int a);
	int GetDex () const;
	void SetStr (int a);
	int GetStr () const;
	void SetFlyAble (int a);
	int GetFlyAble () const;
	void SetFly (int a);
	int GetFly () const;
	void SetSleep (int a);
	int GetSleep () const;
	void SetActive (int a);
	int GetActive () const;
	void SetMagic (int a);
	int GetMagic () const;
	void SetBehavior (int a);
	int GetBehavior () const;
	void SetEffects (int a);
	int GetNumEffects () const;
	int GetEffectByNum (int a) const;
	int FindEffectById (int ID) const;
	void SetEffectsTime (int time, int NumOfEffect);
	int GetEffectsTime (int NumOfEffect);
	void SetNextStep (int step);
	void ClearAllSteps ();
	int GetNextStep ();
	void RemoveFirstStep ();
	int GetNextStepSize ();
	int GetCharCode () const;
	void SetCharCode (int Code);
	int GetColorVisible () const;
	void SetColorVisible (int Color);
	int GetColorNotVisible () const;
	void SetColorNotVisible (int Color);
	int GetMovePoints () const;
	void SetMovePoints (int Points);
	void SetNumInVector (int Num) {NumInVector = Num;};
	int GetNumInVector () {return NumInVector;};

};

