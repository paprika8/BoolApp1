#pragma once
#include "component.h"
#include "composite.h"

namespace BoolApp{

	class PWindow : public PComponent{
		public:
		PWindow(HWND ahwnd, View* aview) : PComponent(ahwnd, aview){
			
		};

		void construction() override {
			hwnd = CreateWindowEx(
				0,
				view->getSzWindowClass().c_str(),
				L"Rect",
				WS_VISIBLE | (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX) | WS_CLIPCHILDREN | WS_BORDER,
				0, 0, 500, 500,
				hwnd,
				0,
				instance,
				0
			);
			SetWindowLongPtr(hwnd, 0, (LONG_PTR) this);
		};
		~PWindow(){
			PostQuitMessage ( 0 );
		}
		private:

	};

	class Window : public Component{
		public:
		Window(Builder *abuilder = new DefaultBuilder()) : Component(abuilder){
			Construct();
		}
		std::wstring getSzWindowClass() override {
			return L"Rect";
		};
		
		void Register(WNDCLASS& wca) override {
			wca.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(193, 193, 193));
		};

		ProcessView* VConstruct(ProcessView* apv) override {
			ProcessView* pw = new PWindow(0, this);
			pw->construction();
			return pw;
		};

		LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView* ptr) override {
			PWindow* pWindow = (PWindow*)ptr;

			return DefWindowProc(ahwnd, message, wparam, lparam);
		};
	};
}