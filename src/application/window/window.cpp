#include "window.hpp"
#include <application/utils/interfaces/i_message_sink.hpp>
#include <Windows.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace pixel_helper
{

	window::window(const int width, const int height)
		:window_width_(width), window_height_(height)
	{
		static bool s_register_window_class = true;
		if (s_register_window_class)
		{
			WNDCLASSEX window_class;
			window_class.cbSize = sizeof(WNDCLASSEX);
			window_class.style = CS_CLASSDC;
			window_class.lpfnWndProc = static_window_procedure;
			window_class.cbClsExtra = 0L;
			window_class.cbWndExtra = 0L;
			window_class.hInstance = GetModuleHandle(nullptr);
			window_class.hIcon = nullptr;
			window_class.hCursor = nullptr;
			window_class.hbrBackground = nullptr;
			window_class.lpszMenuName = nullptr;
			window_class.lpszClassName = "Pixel Helper";
			window_class.hIconSm = nullptr;

			RegisterClassEx(&window_class);
			s_register_window_class = false;
		}

		window_handle_ = ::CreateWindowExA(
			0L,
			"Pixel Helper",
			"Pixel Helper",
			WS_POPUP | WS_VISIBLE,
			100,
			100,
			window_width_,
			window_height_,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			this
		);

		::UpdateWindow(window_handle_);
		::ShowWindow(window_handle_, SW_SHOW);
		::SendMessage(window_handle_, WM_ERASEBKGND, 0, 0);
	}

	window::~window()
	{
		if (window_handle_)
		{
			::DestroyWindow(window_handle_);
		}
	}

	LRESULT APIENTRY window::static_window_procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			const auto data = reinterpret_cast<LPCREATESTRUCT>(lParam);
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data->lpCreateParams));
			window* window_instance = static_cast<window*>(data->lpCreateParams);
			window_instance->window_handle_ = hWnd;
		}

		auto window_instance = reinterpret_cast<window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (window_instance)
		{
			return window_instance->window_procedure(hWnd, uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	LRESULT window::window_procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		{
			return true;
		}

		for (auto* sink : message_sinks_)
		{
			if (sink->process_message(hWnd, uMsg, wParam, lParam))
			{
				return 0;
			}
		}
		switch (uMsg)
		{
			case WM_DESTROY:
			{
				::SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
				::PostQuitMessage(0);
				return 0;
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
