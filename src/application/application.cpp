#include "application.hpp"
#include "renderer/renderer.hpp"
#include "user_interface/user_interface.hpp"
#include "window/window.hpp"
#include <Windows.h>

namespace pixel_helper
{
	application::application(const int width, const int height)
		:width_(width), height_(height), window_(width_, height_)
	{
	}
	int application::run()
	{
		initialize_modules();

		while (pump_messages())
		{
			renderer_.begin_frame();

			user_interface_.begin_frame();
			user_interface_.draw_frame();
			user_interface_.end_frame();

			renderer_.end_frame();
		}

		return 0;
	}

	void application::initialize_modules()
	{
		renderer_.init(window_.get_window_handle(), window_.get_window_width(), window_.get_window_height());
		user_interface_.init(window_.get_window_handle(), renderer_.device(), renderer_.context());
	}

	bool application::pump_messages()
	{
		MSG msg;
		while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return false;
			}
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
		return true;
	}
}