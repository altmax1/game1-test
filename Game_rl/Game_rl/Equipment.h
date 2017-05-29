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
	void SelectEqToWear (std::vector<int> &temp);
	void PrintEqToWear (std::vector <int> &temp, int MenuState);
	void WearThisItem (int Num);
	void PrintBorder (int MenuState);
	void MakeChoise (int MenuState);
	void WearItem (int MenuState);
	void NothingToWear ();
	void UnWearItem (int MenuState);
	int GetHeadDef();
	int GetBodyDef();
	int GetArmsDef();
	int GetGlovesDef();
	int GetLegsDef();
	int GetBootsDef();
	int GetDefBySlot (int Num);
	int GetDef2BySlot (int Num);
	int GetDef3BySlot (int Num);
	int GetDef4BySlot (int Num);
	int GetDef5BySlot (int Num);
	void LuaMakeSumOfDef ();

};

