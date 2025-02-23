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
	LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam);
	class pcomposite;
	class pcomponent;
	class composite;
	class component;
	
	class View{
		public:
		ProcessView *PV = 0;
		virtual std::string getSzWindowClass() = 0;
		virtual void Register(WNDCLASSA&){};
		virtual LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView *ptr){};

		void sregister(){
			WNDCLASSA wca = {0};
			//адрес ф-ции обработки сообщений
			wca.lpfnWndProc = (WNDPROC)BoolApp::wndProc;
			//стиль окна
			wca.style = CS_HREDRAW|CS_VREDRAW;
			//дискриптор экземпляра приложения
			//название класса
			wca.hInstance = instance;
			wca.lpszClassName = getSzWindowClass().c_str();
			//загрузка курсора
			wca.hCursor = LoadCursor(NULL, IDC_ARROW);
			//загрузка цвета окон
			wca.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
			//резерв места для указателя на PV
			wca.cbWndExtra = sizeof(void*);
			Register(wca);
			//регистрация класса
			RegisterClassA(&wca);
		}

		~View(){
			PV->view = 0;
			disable();
		}

		View(){

		}

		virtual void enable();
		virtual void disable();

		private:
		bool enabled = false;
	};

	class ProcessView{
		public:
		HWND hwnd;
		View *view;
		Size size = Size(0,0);
		Margin margin = Margin(0, 0, 0, 0);
		Padding padding = Padding (0, 0, 0, 0);
		ProcessView(HWND ahwnd, View* aview){
			hwnd = ahwnd;

			if ( !isRegistry.contains ( aview->getSzWindowClass () ) ) {
        aview->sregister ();
        isRegistry.insert ( aview->getSzWindowClass () );
      }

		}
		~ProcessView(){
			if(view){
				view->PV = 0;
				view = 0;
			}
			
			if(hwnd){
				SetWindowLongPtr(hwnd, 0, 0);
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}
		}

		virtual void construction() = 0;
		private:
	};



}