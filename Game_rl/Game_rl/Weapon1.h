#pragma once
#include "item.h"
class Weapon1 :
	public Item
{
private:
	int Type;
	int MaxDamage;
	int MinDamage;
	bool NeedsAmmo; //����� �� �������
	bool IsAmmo; //�������� �� �������/��������
	int Caliber; //������
	int AmmoQuantity; // max ���������� �������� � ������
	vector <int> Ammo; //������� ����� - ������ �� ID
	int Quality; //�������� - ����� ��, ���� �������, �� �����.
	bool Destroyed; //���� ��������� ������, ������ 1. � not unique �� ���������.
	int Range;  // ��������� ��������� (��������)
	int BlastRadius; //������ ���������


public:
	Weapon1(void);
	~Weapon1(void);
	int GetType();
	void SetType (int Type);
	int GetMaxDamage ();
	void SetMaxDamage (int a);
	int GetMinDamage ();
	void SetMinDamage (int a);
	bool GetNeedsAmmo ();
	void SetNeedsAmmo (int a);
	bool GetIsAmmo ();
	void SetIsAmmo (int a);
	int GetCaliber ();
	void SetCaliber (int a);
	int GetAmmoQuantity ();
	void SetAmmoQuantity (int a);
	void ReloadAmmo	();
	void UnloadAmmo ();
	int GetQuality ();
	void SetQuality (int a);
	bool GetDestroyed ();
	void SetDestroyed (int a);
	int GetRange ();
	void SetRange (int a);
	int GetBlastRadius ();
	void SetBlastRadius (int a);

};

