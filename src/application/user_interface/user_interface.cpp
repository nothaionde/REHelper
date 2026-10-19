#include "user_interface.hpp"
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <d3d11.h>
#include <imgui.h>
#include <Windows.h>

namespace pixel_helper
{
	user_interface::user_interface()
		: initialized_(false), hwnd_(nullptr)
	{
	}

	user_interface::~user_interface()
	{
		shutdown();
	}

	bool user_interface::init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
	{
		hwnd_ = hwnd;
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		if (!ImGui_ImplWin32_Init(hwnd)) return false;
		if (!ImGui_ImplDX11_Init(device, context)) return false;

		initialized_ = true;
		return true;
	}

	void user_interface::shutdown()
	{
		if (initialized_)
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
			initialized_ = false;
		}
	}

	void user_interface::begin_frame() const
	{
		if (!initialized_) return;
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void user_interface::draw_frame() const
	{
		if (!initialized_) return;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);

		constexpr ImGuiWindowFlags window_flags =
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));

		ImGui::Begin("MainFullscreenOverlay", nullptr, window_flags);
		ImGui::PopStyleVar(3);

		draw_header();
		ImGui::Separator();
		draw_body();
		ImGui::Separator();
		draw_footer();

		ImGui::End();
	}

	void user_interface::draw_header() const
	{
		ImGui::Text("Pixel Helper - World Visualizer");

		ImGui::SameLine(ImGui::GetWindowWidth() - 45.0f);
		if (ImGui::Button(" X ", ImVec2(30, 0)))
		{
			ImGui::Text("PixelBob");
			if (hwnd_)
			{
				::PostMessage(hwnd_, WM_CLOSE, 0, 0);
			}
		}
	}

	void user_interface::draw_body()
	{
		ImGui::BeginChild("MainBodyContent", ImVec2(0, -35.0f), true);
		ImGui::Text("Main content area. Waiting for memory hooks and navigation data...");
		ImGui::EndChild();
	}

	void user_interface::draw_footer()
	{
		ImGui::TextColored(ImVec4(0.4f, 0.8f, 0.4f, 1.0f), "Status: Idle");
		ImGui::SameLine(ImGui::GetWindowWidth() - 150.0f);
		ImGui::Text("v0.1-alpha");
	}

	void user_interface::end_frame() const
	{
		if (!initialized_) return;
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}