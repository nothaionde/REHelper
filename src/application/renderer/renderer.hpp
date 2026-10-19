#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

namespace pixel_helper
{
	class renderer {
	public:
		renderer();
		~renderer();

		bool init(HWND hwnd, int width, int height);
		void cleanup();

		void begin_frame();
		void end_frame();

		ID3D11Device* device() const
		{
			return device_;
		}
		ID3D11DeviceContext* context() const
		{
			return context_;
		}
		IDXGISwapChain* swap_chain() const
		{
			return swap_chain_;
		}

	private:
		ID3D11Device* device_;
		ID3D11DeviceContext* context_;
		IDXGISwapChain* swap_chain_;
		ID3D11RenderTargetView* render_target_view_;

		void create_render_target();
		void cleanup_render_target();
	};
}