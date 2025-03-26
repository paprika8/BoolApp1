#pragma once
#include "oopWin.h"
#include <functional>
namespace BoolApp
{

	class PButton : public ProcessView
	{
	public:
		bool isDown = 0;
		PButton(HWND ahwnd, View *aview);

		void construction() override;

	private:
	};

	class Button : public View
	{
	public:
		std::wstring text = L"";
		int flag_format = 0;
		std::function<void(Button *)> click = [](Button *) -> void {};
		HFONT font = CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
								 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

		Button(Builder *abuilder = new DefaultBuilder()) : View(abuilder)
		{
		}

		void set_font_size(int size)
		{
			DeleteObject(font);
			font = CreateFontA(
				size,
				0,
				0,
				0,
				FW_NORMAL,
				FALSE,
				FALSE,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_ROMAN,
				"Times New Roman");
			if (PV)
				SendMessage(PV->hwnd, WM_SETFONT, font, true);
		}

		std::wstring getSzWindowClass() override
		{
			return L"Button";
		};

		void Register(WNDCLASS &wca) override
		{
			wca.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(225, 60, 60));
		};

		ProcessView *VConstruct(ProcessView *apv) override
		{
			PButton *pb = new PButton(apv->hwnd, this);
			pb->construction();
			return pb;
		};

		virtual void paint(HWND hwnd);

		void Click()
		{
			click(this);
		}

		LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView *ptr) override
		{
			PButton *pButton = (PButton *)ptr;
			switch (message)
			{
			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK:
			{
				pButton->isDown = true;
				InvalidateRect(ahwnd, 0, 0);

				SetCapture(ahwnd);
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			case LBN_KILLFOCUS:
			case WM_MOUSEMOVE:
			{
				LPPOINT point = new POINT();
				if (pButton->isDown && GetCursorPos(point) && WindowFromPoint(*point) == ahwnd)
				{
					delete point;
					return DefWindowProc(ahwnd, message, wparam, lparam);
				}
				delete point;
				pButton->isDown = false;
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			case WM_LBUTTONUP:
			{
				if (pButton->isDown)
					Click();
				pButton->isDown = false;
				InvalidateRect(ahwnd, 0, 0);

				ReleaseCapture();
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
			default:
				return DefWindowProc(ahwnd, message, wparam, lparam);
			}
		};

	private:
	};
}