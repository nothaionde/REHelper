#include"application/application.hpp"
#include <sal.h>
#include <Windows.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nShowCmd)
{
	pixel_helper::application application(800, 600);
	return application.run();
}
