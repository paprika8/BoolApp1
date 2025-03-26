#include <Windows.h>
#include "window.h"
#include "LinearContainer.h"
#include "button.h"
#include "Text.h"
#include "Edit.h"

const Gdiplus::Color bg (255, 244, 204);
const Gdiplus::Color confirm (127, 176, 105);
const Gdiplus::Color in (230, 170, 104);
const Gdiplus::Color button (183, 54, 34);
const Gdiplus::Color out (29, 26, 5);
const Gdiplus::Color trans (0, 0, 0, 0);

const Gdiplus::Color dark_t = out;
const Gdiplus::Color light_t (255, 255, 255);





using namespace BoolApp;

const Padding but_pad = Padding(pointUI(10, percent), 0, 0, 0);



ULONG_PTR gdiplusToken = 0;

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR lpCmdLine, int nshow) {

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	Gdiplus::Status st = Gdiplus::GdiplusStartup ( &gdiplusToken , &gdiplusStartupInput , NULL );
	if ( st != Gdiplus::Ok )
	{
		MessageBox ( NULL ,
			L"Call to GdiplusStartup failed!" ,
			L"GdiplusStartup ist kaputt" ,
			NULL );
		return -1;
	}

	Window win(new SizeBuilder(Size(500, 500), Margin(0,0,0,0, MarginType::TOP | MarginType::LEFT), Padding(0)));
	win.Show(ShowType::MAXIMIZE);

	LinearContainer* lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
	lc->is_vert_orientation = 1;
	win.add(lc);

	ScrollText* app_name = new ScrollText(new SizeBuilder(Size(pointUI(400, percent), pointUI(350, percent)), Margin(0), Padding(pointUI(150, percent), pointUI(100, percent), 0, 0)));
	//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
	app_name->SetText(L"B001App");
	app_name->font = createFont(100);
	app_name->background = trans;
	app_name->text_color = dark_t;
	lc->add(app_name);

	Button* exer_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	exer_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	exer_bt->text = L"ЗАДАЧИ";
	exer_bt->set_font_size(35);
	exer_bt->background = button;
	//exer_bt->font color
	lc->add(exer_bt);

	Button* close_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	close_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	close_bt->text = L"ВЫХОД";
	close_bt->set_font_size(35);
	close_bt->background = button;
	lc->add(close_bt);

	/*
	Edit* text = new Edit(new SizeBuilder(Size(pointUI(100), pointUI(60)), Margin(5, 5, 5, 5), Padding(0,0,20,0)));
	text->SetText(L"TEXT УБОГИЙ");
	lc->add(text);
	*/


	int res = run();
	Gdiplus::GdiplusShutdown ( gdiplusToken );
	return res;
}