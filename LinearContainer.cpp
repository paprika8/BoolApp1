#include "LinearContainer.h"

namespace BoolApp
{
	void PLContainer::construction()
	{
		hwnd = CreateWindowEx(
			WS_EX_TRANSPARENT,
			view->getSzWindowClass().c_str(),
			L"",
			WS_VISIBLE | WS_CHILD,
			0, 0, 100, 100,
			hwnd,
			0,
			instance,
			0
		);
		SetWindowLongPtr(hwnd, 0, (LONG_PTR) this);
	}
	LRESULT LinearContainer::wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView *ptr)
	{
		return DefWindowProc(ahwnd, message, wparam, lparam);
	}
}