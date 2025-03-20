#include "oopWin.h"
#include "positioner.h"

template<class T>
void deleteSafely(T*& ptr) {
    T* buff = ptr;
    ptr = 0;
    delete buff;
}


HINSTANCE instance = 0;
std::set<std::string> isRegistry = std::set<std::string>();

void BoolApp::init(HINSTANCE ainstance)
{
	instance = ainstance;
}

LRESULT BoolApp::wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message){
		case WM_PAINT:{
			PAINTSTRUCT pstruct;
			HDC hdc = BeginPaint(ahwnd, &pstruct);
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			ptr->view->paint(hdc, pstruct);
			EndPaint(ahwnd, &pstruct);
			return 0;
		}
		case WM_NCCREATE:{
			SetWindowLongPtr(ahwnd, 0, 0);
			return DefWindowProc(ahwnd, message, wparam, lparam);
		}
		case WM_NCDESTROY:{ //конец удаления
			HWND parentHWND = GetParent(ahwnd);
			if(parentHWND){
				InvalidateRect (parentHWND, 0, 0);
			}
		}
		case WM_DESTROY:{ //начало удаления
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if(ptr){
				SetWindowLongPtr(ahwnd, 0, 0);
				ptr->hwnd = 0;
				delete ptr;
			}
			return DefWindowProc(ahwnd, message, wparam, lparam);
		}
		case WM_SIZE:{
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if(!ptr){
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			if(GetWindowLong(ahwnd, GWL_STYLE) & WS_SIZEBOX){
				ptr->size.height = HIWORD(lparam);
				ptr->size.width = LOWORD(lparam);
			}
			
		}
		case WM_MOVE:{
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if(!ptr){
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			Positioning(ptr);
		}
		default:{
			ProcessView *ptr = GetWindowLongPtr(ahwnd, 0);
			if(!ptr){
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			ptr->view->wndProc(ahwnd, message, wparam, lparam, ptr);
		}
	}
	return DefWindowProc(ahwnd, message, wparam, lparam);
}

void BoolApp::View::enable()
{
	if(enable){
		return;
	}
	enabled = true;
	Construct();
}

void BoolApp::View::disable()
{
	if(!enable){
		return;
	}
	enabled = false;
	deleteSafely(PV);
}
