#include "button.h"
namespace BoolApp{
	PButton::PButton(HWND ahwnd, View *aview) : ProcessView(ahwnd, aview)
	{
		resize = [=](Point p, Size s) -> void{
			HRGN rgn = CreateRectRgn(0, 0, 0 + s.width, 0 + s.height);
			HRGN rgn2 = CreateRectRgn(0, 0, 0 + s.width - s.height, 0 + s.height);
			HRGN round_rgn = 	CreateEllipticRgn(s.width - s.height * 2, - s.height * 0.5, s.width, s.height * 1.5);
			CombineRgn(rgn, rgn, round_rgn, RGN_AND);
			CombineRgn(rgn, rgn, rgn2, RGN_OR);
			DeleteObject(round_rgn);
			padding.right = s.width / 8;
			//HRGN rgn = CreateRectRgn(0, 0, 0 + s.width, 0 + s.height);
			SetWindowRgn(hwnd, rgn, 1);
		};
	}
	void PButton::construction() 
	{
		hwnd = CreateWindowEx(
			WS_EX_TRANSPARENT,
			view->getSzWindowClass().c_str(),
			L"",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			0, 0, 0, 0,
			hwnd,
			0,
			instance,
			0);
		SetWindowLongPtr(hwnd, 0, (LONG_PTR)this);
		int res = SendMessage(hwnd, WM_SETFONT, ((Button*)view)->font, true);
	};
}