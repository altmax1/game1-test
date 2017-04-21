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

public:
	Equipment(void);
	~Equipment(void);
	void PrintItems ();
	void PrintEquipment ();
};

