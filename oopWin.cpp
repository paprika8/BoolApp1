#include "oopWin.h"
#include "positioner.h"

namespace BoolApp
{

	template <class T>
	void deleteSafely(T *&ptr)
	{
		T *buff = ptr;
		ptr = 0;
		delete buff;
	}

	HINSTANCE instance = 0;
	std::set<std::wstring> isRegistry = std::set<std::wstring>();

	void init(HINSTANCE ainstance)
	{
		instance = ainstance;
	}

	LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_PAINT:
		{
			PAINTSTRUCT pstruct;
			HDC hdc = BeginPaint(ahwnd, &pstruct);
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			ptr->view->paint(hdc, pstruct);
			EndPaint(ahwnd, &pstruct);
			return 0;
		}
		case WM_NCCREATE:
		{
			SetWindowLongPtr(ahwnd, 0, 0);
			return DefWindowProc(ahwnd, message, wparam, lparam);
		}
		case WM_NCDESTROY:
		{ // конец удаления
			HWND parentHWND = GetParent(ahwnd);
			if (parentHWND)
			{
				InvalidateRect(parentHWND, 0, 0);
			}
		}
		case WM_DESTROY:
		{ // начало удаления
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if (ptr)
			{
				SetWindowLongPtr(ahwnd, 0, 0);
				ptr->hwnd = 0;
				delete ptr;
			}
			return DefWindowProc(ahwnd, message, wparam, lparam);
		}
		case WM_SIZE:
		{
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if (!ptr)
			{
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			if (GetWindowLong(ahwnd, GWL_STYLE) & WS_SIZEBOX)
			{
				ptr->size.height = HIWORD(lparam);
				ptr->size.width = LOWORD(lparam);
			}
			ptr->resize(ptr->point, Size(LOWORD(lparam), HIWORD(lparam)));
		}
		case WM_MOVE:
		{
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if (!ptr)
			{
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			Positioning(ptr);
			ptr->resize(Point(LOWORD(lparam), HIWORD(lparam)), ptr->size);
			return ptr->view->wndProc(ahwnd, message, wparam, lparam, ptr);
		}
		default:
		{
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if (!ptr)
			{
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			return ptr->view->wndProc(ahwnd, message, wparam, lparam, ptr);
		}
		}
		return DefWindowProc(ahwnd, message, wparam, lparam);
	}

	int run()
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return (int)msg.wParam;
	}

	void View::enable()
	{
		if (enabled)
		{
			return;
		}
		enabled = true;
		Construct();
	}

	void View::disable()
	{
		if (!enabled)
		{
			return;
		}
		enabled = false;
		deleteSafely(PV);
	}

	ProcessView::ProcessView(HWND ahwnd, View *aview)
	{
		hwnd = ahwnd;
		view = aview;

		if (!isRegistry.contains(aview->getSzWindowClass()))
		{
			aview->sregister();
			isRegistry.insert(aview->getSzWindowClass());
		}
		if (aview->parent)
		{
			parent = aview->parent->PV;
		}
	}

	ProcessView::~ProcessView()
	{
		if (view)
		{
			view->PV = 0;
			view = 0;
		}

		if (hwnd)
		{
			SetWindowLongPtr(hwnd, 0, 0);
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
	}
	void SizeBuilder::build(ProcessView *apv)
	{
		apv->size = size;
		apv->margin = margin;
		apv->padding = padding;
		Positioning(apv);
	}
}