#pragma once
class Beast
{
private:
	int HP;  // ��������
	int Energy;  // ������� - ������ ����
	int Speed; // ��������� ������������
	int RegenHP; //�������� ����������� ��������
	int RegenEnergy;  // �������� ����������� �������
	int LevelOfBeast; //����������� �������
	int Defense;  //������� ������
	int Dex;  // ��������
	int Str;  //����
	int FlyAble:1; //�������� � ������?
	int Fly:1; //������ �� ������?
	int Sleep:1;   // ����?
	int Active:1;  //������� ��� ���
	int Magic:1;  //���������� �� ������
	int Behavior; // ��� ��������� 
	std::vector <int> Effects; // ���������� �������
	std::vector <int> EffectsTime; // ����� ��������
	std::list <int> NextStep; // ��������� ��������

public:
	Beast(void);
	~Beast(void);
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

