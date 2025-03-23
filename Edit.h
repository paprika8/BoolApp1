#pragma once
#include "Text.h"
#include "custom_wstr.h"

namespace BoolApp {
	class Edit;

	class PEdit : public ProcessView
	{
		friend Edit;
	public:
		int WPos = 0;
		int TextHeight = 0;
		int MaxTextHeight = 0;

		PEdit ( HWND hwnd, View* aModel) : ProcessView ( hwnd, aModel) {
			padding.right = 20;
		};

		void construction() override;
		~PEdit(){

		}
	private:
		int oldY;
		bool isDown = 0;
	};

	class Edit : public View
	{
	public:
		
		Gdiplus::Color background;
		int text_cursor = 0;

		Edit ( Builder* abuilder = 0 ) : View ( abuilder ) {
			background = Gdiplus::Color ( 231 , 237 , 216 );
		};

		ProcessView* VConstruct(ProcessView* apv) override {
			PEdit* pw = new PEdit(apv->hwnd, this);
			pw->construction();
			return pw;
		}

		std::wstring getSzWindowClass() override {
			return L"Text";
		};

		void Register(WNDCLASS& wca) override {
			wca.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(193, 193, 100));
		};
		void paint (HWND) override;
		LRESULT wndProc ( HWND hwnd , UINT uMsg , WPARAM wParam , LPARAM lParam , ProcessView* pData ) override;

		void SetText ( std::wstring atext) {
			text = atext.c_str();
			if ( enabled ) {
				SendMessage ( PV->hwnd , WM_SETSCROLLEDTEXT , 0 , 0 );
			}
		}
		std::wstring GetText () {
			return std::wstring(text.data);
		}

	private:
		custom_wstr text = L"";
		void drawText(HDC hdc, Gdiplus::Rect rect);
		void rect_text(HDC hdc, Gdiplus::Rect rect, Gdiplus::Rect &res);
	};
}