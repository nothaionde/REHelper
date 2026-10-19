#pragma once
#include <Windows.h>

namespace pixel_helper
{
	struct i_message_sink {
		virtual ~i_message_sink() = default;
		// Return true if handled (skips DefWindowProc).
		virtual bool process_message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual void on_attach(HWND hWnd) = 0;
	};
}