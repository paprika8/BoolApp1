#include "button.h"
namespace BoolApp{
	PButton::PButton(HWND ahwnd, View *aview) : ProcessView(ahwnd, aview)
	{
		resize = [=](Point p, Size s) -> void{
			HRGN rgn = CreateRectRgn(0, 0, 0 + s.width, 0 + s.height);
			HRGN round_rgn = 	CreateEllipticRgn(s.width - s.height * 2, - s.height * 0.5, s.width, s.height * 1.5);
			CombineRgn(rgn, rgn, round_rgn, RGN_AND);
			DeleteObject(round_rgn);
			//HRGN rgn = CreateRectRgn(0, 0, 0 + s.width, 0 + s.height);
			SetWindowRgn(hwnd, rgn, 1);
		};
	};
}