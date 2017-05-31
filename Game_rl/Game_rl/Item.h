#pragma once
using namespace std;

class Item
{
protected:
	int ID;
	int Weight;
	bool Unique;
	string Name;
	string RName;
public:
	int GetItemID ();
	void SetItemId (int Id);
	int GetWeight ();
	void SetWeight (int W);
	bool GetUnique ();
	void SetUnique (int a);
	string GetName ();
	void SetName (string s);
	string GetRName ();
	void SetRName (string s);
	Item(void);
	~Item(void);
};

