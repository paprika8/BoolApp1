#include "button.h"
namespace BoolApp{
	PButton::PButton(HWND ahwnd, View *aview) : ProcessView(ahwnd, aview)
	{
		resize = [=](Point p, Size s) -> void{
			HRGN rgn = CreateRoundRectRgn(0, 0, 0 + s.width, 0 + s.height, 30, 30);
			//HRGN rgn = CreateRectRgn(0, 0, 0 + s.width, 0 + s.height);
			SetWindowRgn(hwnd, rgn, 1);
		};
	};
}