#include "oopWin.h"
#include <functional>
namespace BoolApp{

	class PButton : public ProcessView{
		public:
		bool isDown = 0;
		PButton(HWND ahwnd, View* aview) : ProcessView(ahwnd, aview){
			
		};

		void construction() override {
			hwnd = CreateWindowExA(
				0,
				view->getSzWindowClass().c_str(),
				"",
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				0, 0, 0, 0,
				hwnd,
				0,
				instance,
				0
			);
			SetWindowLongPtr(hwnd, 0, (LONG_PTR) this);
		};

		private:

	};

	class Button : public View{
		public:
		std::function <void(Button*)> click = [](Button*)->void{};

		std::string getSzWindowClass() override {
			return "Button";
		};
		
		void Register(WNDCLASSA& wca) override {
			wca.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(103, 192, 103));
		};

		ProcessView* VConstruct(ProcessView* apv) override {
			return new PButton(apv->hwnd, this);
		};

		void Click(){
			click(this);
		}

		LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView* ptr) override {
			PButton* pButton = (PButton*)ptr;
			switch(message){
				case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        {
            pButton->isDown = true;
            InvalidateRect ( ahwnd , 0 , 0 );

            SetCapture ( ahwnd );
            return DefWindowProc ( ahwnd , message , wparam , lparam );
        }
        case LBN_KILLFOCUS:
        case WM_MOUSEMOVE: 
        {
            LPPOINT point = new POINT ();
            if ( pButton->isDown && GetCursorPos ( point ) && WindowFromPoint ( *point ) == ahwnd ) {
                delete point;
                return DefWindowProc ( ahwnd , message , wparam , lparam );
            }
            delete point;
            pButton->isDown = false;
            return DefWindowProc ( ahwnd , message , wparam , lparam );
        }
        case WM_LBUTTONUP:
        {
            if ( pButton->isDown )
                Click ();
            pButton->isDown = false;
            InvalidateRect ( ahwnd , 0 , 0 );
            
            ReleaseCapture ( );
            return DefWindowProc ( ahwnd , message , wparam , lparam );
        }
				default:
				DefWindowProc(ahwnd, message, wparam, lparam);
			}

		};


		private:
		

	};
}