#include "stdafx.h"
#include "Log.h"
#include "Game.h"

using namespace std;
Log::Log()
{
	
	MyLog.open(".\\Files\\logs\\log.txt");
	DevLog.open(".\\Files\\logs\\devlog.txt");
	Game *MyGame = Game::GetGameInstance();
	if (MyGame->GetFullLogging() == 1)
		FullLogging = 1;
	else
		FullLogging = 0;

}


Log::~Log()
{
	MyLog.close();
	DevLog.close();
}

void Log::ResetLog()
{
	messages.clear();
	frame_offset = 0;
	dragging_scrollbar = false;
}

int Log::UpdateHeights ()
{
	int total_height = 0;
	for (auto& message : messages)
	{
		message.height = terminal_measure_ext(frame_width, 0, message.text.c_str()).height;
		total_height += message.height;
	}

	// Add blank lines between messages
	total_height += messages.size() - 1;

	return total_height;
}

void Log::UpdateGeometry()
{
	// Save current scroll position
	float current_offset_percentage = frame_offset / (float)total_messages_height;

	// Update frame dimensions
	frame_width = terminal_state(TK_WIDTH) - (padding_left + padding_right + 1);
	frame_height = terminal_state(TK_HEIGHT) - (padding_top + padding_bottom);

	// Calculate new message list height
	total_messages_height = UpdateHeights();

	// Scrollbar
	scrollbar_height = std::min<int>(std::ceil(frame_height * (frame_height / (float)total_messages_height)), frame_height);

	// Try to recover scroll position
	frame_offset = total_messages_height * current_offset_percentage;
	frame_offset = min(frame_offset, total_messages_height - frame_height);
	if (total_messages_height <= frame_height) frame_offset = 0;
}

void Log::ScrollToPixel(int py)
{
	py -= padding_top * terminal_state(TK_CELL_HEIGHT);
	float factor = py / ((float)frame_height * terminal_state(TK_CELL_HEIGHT));
	frame_offset = total_messages_height * factor;
	frame_offset = max(0, min(total_messages_height - frame_height, frame_offset));
}

void Log::PrintLog ()
// честно сперто из чужого решения методом божественного копипаста, лучше не лезть
{
	
	terminal_set("input: filter='keyboard, mouse+', precise-mouse=true");
	UpdateGeometry();

	while (true)
	{
		terminal_clear();
		terminal_color("white");

		// Frame background
		terminal_layer(0);
		terminal_bkcolor("darkest gray");
		terminal_clear_area(padding_left, padding_top, frame_width, frame_height);
		terminal_bkcolor("none");

		// Find topmost visible message
		int index = 0, first_line = 0;
		for (; first_line < total_messages_height; index++)
		{
			auto& message = messages[index];
			if (first_line + message.height >= frame_offset)
			{
				// This message is partially visible
				break;
			}

			first_line += message.height + 1;
		}
		int delta = first_line - frame_offset;

		// Drawing messages (+crop)
		terminal_layer(1);
		for (; index < messages.size() && delta <= frame_height; index++)
		{
			auto& message = messages[index];
			terminal_put(padding_left, padding_top + delta, '>');
			terminal_print_ext(padding_left+1, padding_top + delta, frame_width, 0, TK_ALIGN_DEFAULT, message.text.c_str());
			delta += message.height;// +1;
		}
		terminal_crop(padding_left, padding_top, frame_width, frame_height);

		// Scroll bar
		terminal_layer(0);
		terminal_bkcolor("darker gray");
		terminal_clear_area(padding_left + frame_width, padding_top, 1, frame_height);
		terminal_bkcolor("none");
		terminal_color("dark orange");
		int scrollbar_column = padding_left + frame_width;
		int scrollbar_offset =
			(padding_top + (frame_height - scrollbar_height) * (frame_offset / (float)(total_messages_height - frame_height))) *
			terminal_state(TK_CELL_HEIGHT);
		for (int i = 0; i < scrollbar_height; i++)
		{
			terminal_put_ext(scrollbar_column, i, 0, scrollbar_offset, 0x2588, 0);
		}

		// Render
		terminal_refresh();

		int key = terminal_read();

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
		else if (key == TK_UP)
		{
			frame_offset = max(0, frame_offset - 1);
		}
		else if (key == TK_DOWN)
		{
			frame_offset = min(total_messages_height - frame_height, frame_offset + 1);
		}
		else if (key == TK_MOUSE_SCROLL)
		{
			// Mouse wheel scroll
			frame_offset += mouse_scroll_step * terminal_state(TK_MOUSE_WHEEL);
			frame_offset = max(0, min(total_messages_height - frame_height, frame_offset));
		}
		else if (key == TK_MOUSE_LEFT && terminal_state(TK_MOUSE_X) == scrollbar_column)
		{
			int py = terminal_state(TK_MOUSE_PIXEL_Y);
			if (py >= scrollbar_offset && py <= scrollbar_offset + (scrollbar_height * terminal_state(TK_CELL_HEIGHT)))
			{
				// Clicked on the scrollbar handle: start dragging
				dragging_scrollbar = true;
				dragging_scrollbar_offset = py - scrollbar_offset;
			}
			else
			{
				// Clicked outside of the handle: jump to position
				ScrollToPixel(terminal_state(TK_MOUSE_PIXEL_Y) - scrollbar_height * terminal_state(TK_CELL_HEIGHT) / 2);
			}
		}
		else if (key == (TK_MOUSE_LEFT | TK_KEY_RELEASED))
		{
			dragging_scrollbar = false;
		}
		else if (key == TK_MOUSE_MOVE)
		{
			if (dragging_scrollbar)
				ScrollToPixel(terminal_state(TK_MOUSE_PIXEL_Y) - dragging_scrollbar_offset);

			while (terminal_peek() == TK_MOUSE_MOVE)
				terminal_read();
		}
		else if (key == TK_RESIZED)
		{
			UpdateGeometry();
		}
	}

	
	terminal_set("input: precise-mouse=false;");
}

void Log::AddMessageToLog(string Message)
{
	MyLog << Message << endl;
	AddToDevLog(Message);
	messages.push_back(Message);
	if (messages.size() >= MaxLogSize)
		messages.erase(messages.begin(), messages.begin() + 100);
	return;
}

void Log::AddToDevLog(string Message)
{
	if (FullLogging == 0)
		return;
	DevLog << Message << endl;
	return;
}
