#pragma once
#include <d3d11.h>
#include <Windows.h>

namespace pixel_helper
{
	class user_interface {
	public:
		user_interface();
		~user_interface();

		bool init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
		void shutdown();

		void begin_frame() const;
		void draw_frame() const;
		void end_frame() const;

	private:
		void draw_header() const;
		static void draw_body();
		static void draw_footer();

		bool initialized_;
		HWND hwnd_;
	};
}