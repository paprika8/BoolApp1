#pragma once
#include "component.h"
#include "composite.h"

namespace BoolApp{

	class PWindow : public PComponent{
		public:
		PWindow(HWND ahwnd, View* aview) : PComponent(ahwnd, aview){
			
		};

		void construction() override;
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

		LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView* ptr) override;
	};
}