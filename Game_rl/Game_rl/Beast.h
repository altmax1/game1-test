#pragma once
class Beast
{
private:

	int CoordX;
	int CoordY;
	std::string Name;
	std::string RName;
	std::string RDesc;
	int HP;  // «доровье
	int Energy;  // Ёнерги€ - аналог маны
	int Speed; // —короость передвижени€
	int RegenHP; //—корость регенерации здоровь€
	int RegenEnergy;  // —корость регенерации энергии
	int LevelOfBeast; //виртуальный уровень
	int Defense;  //уровень защиты
	int Dex;  // ловкость
	int Str;  //сила
	int FlyAble:1; //способен к полету?
	int Fly:1; //летает ли сейчас?
	int Sleep:1;   // спит?
	int Active:1;  //активен или ждЄт
	int Magic:1;  //пользуетс€ ли магией
	int Behavior; // тип поведени€ 
	std::vector <int> Effects; // наложенные эффекты
	std::vector <int> EffectsTime; // врем€ эффектов
	std::list <int> NextStep; // следующее действие

public:
	Beast(void);
	~Beast(void);
	void LuaReg ();
	void SetCoordX(int a);
	void SetCoordY(int a);
	int GetCoordX ();
	int GetCoordY ();
	void SetName (std::string S);
	std::string GetName ();
	void SetRName (std::string S);
	std::string GetRName ();
	void SetRDesc (std::string S);
	std::string GetRDesc ();
	void SetHP (int a);
	int GetHP ();
	void SetEnergy (int a);
	int GetEnergy ();
	void SetSpeed (int a);
	int GetSpeed ();
	void SetRegenHP (int a);
	int GetRegenHp ();
	void SetRegenEnergy (int a);
	int GetRegenEnergy ();
	void SetLevelOfBeast (int a);
	int GetLevelOfBeast ();
	void SetDefense (int a);
	int GetDefence ();
	void SetDex (int a);
	int GetDex ();
	void SetStr (int a);
	int GetStr ();
	void SetFlyAble (int a);
	int GetFlyAble ();
	void SetFly (int a);
	int GetFly ();
	void SetSleep (int a);
	int GetSleep ();
	void SetActive (int a);
	int GetActive ();
	void SetMagic (int a);
	int GetMagic ();
	void SetBehavior (int a);
	int GetBehavior ();
	void SetEffects (int a);
	int GetNumEffects ();
	int GetEffectByNum (int a);
	int FindEffectById (int ID);
	void SetEffectsTime (int time, int NumOfEffect);
	int GetEffectsTime (int NumOfEffect);
	void SetNextStep (int step);
	void ClearAllSteps ();
	int GetNextStep ();

};

