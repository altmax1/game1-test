#pragma once
class MiniGame
{
private:
	int IntState[6]; // входные интерфейсы
	int Wire[20]; // провода
	int Switcher; //переключатель
	int Invertor[6]; // инверторы
	int LogicElements[6];// логические элементы
	int ColorOn;
	int ColorOff;
	int CursorPosition;
	int TempCursorPosition;
	int A[14];
	int Variants;
	


public:
	MiniGame();
	~MiniGame();
	void PrintInterface();
	void PrintElementBorder(int x, int y);
	void MiniGameInit();
	void PrintElements();
	std::string GetTypeOfElement(int Num);
	void PrintInputInterfaces();
	void SetTerminalColor(int State);
	void PrintWires1Level();
	void PrintWires2Level();
	void PrintWires3Level();
	void PrintInvertors();
	void PrintSwitcher();
	void PrintCursor();
	void PrintCursorBorder(int x, int y);
	void PrintBigCursorBorder(int x, int y);
	void MoveCursor(int a);
	void ChangeState();
	void Calculate();
	int LogicElementCalculate(int WireIn1, int WireIn2, int Num);
	int InvertorCalculate(int WireIn, int Num);
	void CalculateAllVariants();
	void CalculateInterfaces(std::ofstream &fout);
	void InitFromFile();
};

