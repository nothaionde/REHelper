#pragma once
#include <application/utils/interfaces/i_message_sink.hpp>
#include <vector>
#include <Windows.h>
namespace pixel_helper
{
	class window {
	public:
		window(int width, int height);
		~window();

		window(const window&) = delete;
		window& operator=(const window&) = delete;

		window(window&&) = delete;
		window& operator=(window&&) = delete;

		[[nodiscard]] HWND get_window_handle() const
		{
			return window_handle_;
		}

		[[nodiscard]] int  get_window_width() const
		{
			return window_width_;
		}

		[[nodiscard]] int  get_window_height() const
		{
			return window_height_;
		}
	private:
		HWND window_handle_ = nullptr;
		std::vector<i_message_sink*> message_sinks_;
		int window_width_ = 800;
		int window_height_ = 600;
	private:
		static LRESULT APIENTRY static_window_procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT window_procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const;
	};
}