#pragma once
using namespace std;

struct Message
{
	Message() :
		height(0)
	{ }

	Message(const std::string& text) :
		text(text),
		height(0)
	{ }

	std::string text;
	int height;
};

class Log
{
private:
	const int padding_left = 4;
	const int padding_right = 4;
	const int padding_top = 2;
	const int padding_bottom = 2;
	const int mouse_scroll_step = 2; // 2 text rows per mouse wheel step.

	std::vector<Message> messages;
	int frame_offset = 0;
	int frame_width = 0;
	int frame_height = 0;
	int total_messages_height = 1;
	int scrollbar_height = 0;
	bool dragging_scrollbar = false;
	int dragging_scrollbar_offset = 0;
	int MaxLogSize = 500;
	ofstream MyLog;
	ofstream DevLog;
	int FullLogging;
	

public:
	void ResetLog();
	int UpdateHeights();
	void UpdateGeometry();
	void ScrollToPixel(int py);
	void PrintLog();
	void AddMessageToLog(string Message);
	void AddToDevLog(string Message);
	Log();
	~Log();
};

