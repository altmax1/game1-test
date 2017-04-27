#pragma once
class Equipment
{
private:
	int HeadEq;
	int BodyEq;
	int ArmsEq;
	int GlovesEq;
	int LegsEq;
	int BootsEq;
	int LeftArmWeapon;
	int RightArmWeapon;
	int MenuX;
	int MenuY;
	int DeltaXName;
	int *Ptr [8];

public:
	Equipment(void);
	~Equipment(void);
	void PrintItems ();
	void PrintEquipment ();
	void SelectEquipment ();
	void PrintBorder (int MenuState);
	void MakeChoise (int MenuState);
	void WearItem (int MenuState);
	void UnWearItem (int MenuState);
};

