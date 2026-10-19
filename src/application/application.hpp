#pragma once
#include "renderer/renderer.hpp"
#include "user_interface/user_interface.hpp"
#include "window/window.hpp"
namespace pixel_helper
{
	class application {
	public:
		application(int width, int height);
		int run();
	private:
		void initialize_modules();
		static bool pump_messages();
	private:
		int width_;
		int height_;
		window window_;
		renderer renderer_;
		user_interface user_interface_;
	};
}