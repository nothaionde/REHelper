#include "renderer.hpp"
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgi.h>
#include <dxgicommon.h>
#include <dxgiformat.h>
#include <dxgitype.h>
#include <Windows.h>

namespace pixel_helper
{
	renderer::renderer()
		: device_(nullptr),
		context_(nullptr),
		swap_chain_(nullptr),
		render_target_view_(nullptr)
	{
	}

	renderer::~renderer()
	{
		cleanup();
	}

	bool renderer::init(HWND hwnd, int width, int height)
	{
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 2;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT create_device_flags = 0;
		D3D_FEATURE_LEVEL feature_level;
		const D3D_FEATURE_LEVEL feature_level_array[2] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_0,
		};

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			create_device_flags,
			feature_level_array,
			2,
			D3D11_SDK_VERSION,
			&sd,
			&swap_chain_,
			&device_,
			&feature_level,
			&context_
		);

		if (FAILED(hr))
			return false;

		create_render_target();
		return true;
	}

	void renderer::cleanup()
	{
		cleanup_render_target();
		if (swap_chain_)
		{
			swap_chain_->Release(); swap_chain_ = nullptr;
		}
		if (context_)
		{
			context_->Release(); context_ = nullptr;
		}
		if (device_)
		{
			device_->Release(); device_ = nullptr;
		}
	}

	void renderer::begin_frame()
	{
		float clear_color[4] = {0.1f, 0.1f, 0.12f, 1.0f};
		context_->OMSetRenderTargets(1, &render_target_view_, nullptr);
		context_->ClearRenderTargetView(render_target_view_, clear_color);
	}

	void renderer::end_frame()
	{
		swap_chain_->Present(1, 0);
	}

	void renderer::create_render_target()
	{
		ID3D11Texture2D* p_back_buffer = nullptr;
		swap_chain_->GetBuffer(0, IID_PPV_ARGS(&p_back_buffer));
		if (p_back_buffer)
		{
			device_->CreateRenderTargetView(p_back_buffer, nullptr, &render_target_view_);
			p_back_buffer->Release();
		}
	}

	void renderer::cleanup_render_target()
	{
		if (render_target_view_)
		{
			render_target_view_->Release();
			render_target_view_ = nullptr;
		}
	}
}
