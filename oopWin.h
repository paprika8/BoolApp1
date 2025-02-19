#include <Windows.h>
#include "UIStructs.h"
#include <set>
#include <string>

namespace BoolApp{

	extern HINSTANCE instance;
	extern std::set<std::string> isRegistry;
	class View;
	class ProcessView;
	void init(HINSTANCE ainstance);
	class View{
		public:
		ProcessView *PV = 0;
		virtual std::string getSzWindowClass() = 0;
		virtual void Register() = 0;
		View(){

		}

		virtual void enable();
		virtual void disable();

		private:
		bool enabled = false;

	};

	class ProcessView{
		public:
		View *view;
		Size size = Size(0,0);
		Margin margin = Margin(0, 0, 0, 0);
		Padding padding = Padding (0, 0, 0, 0);
		ProcessView(HWND ahwnd, View* aview){
			hwnd = ahwnd;

			if ( !isRegistry.contains ( aview->getSzWindowClass () ) ) {
        aview->Register ();
        isRegistry.insert ( aview->getSzWindowClass () );
      }

		}

		virtual void construction() = 0;
		private:
		HWND hwnd;
	};



}