#pragma once
#include <d3d12.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

namespace pixel_helper
{
	struct command_list_context {
		ComPtr<ID3D12CommandAllocator> command_allocator_;
	};
}