#include <Windows.h>
#include "window.h"
#include "LinearContainer.h"
#include "button.h"
#include "Text.h"
#include "Edit.h"

const Gdiplus::Color white (255, 255, 255);


using namespace BoolApp;

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
	app_name->background = Gdiplus::Color(0, 0, 0, 0);
	app_name->text_color = Gdiplus::Color(255, 255, 255);
	lc->add(app_name);

	Button* exer_bt = new Button(new SizeBuilder(Size(pointUI(200), pointUI(60)), Margin(5, 5, 5, 5), Padding(0)));
	exer_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	exer_bt->text = L"Задачи";
	exer_bt->set_font_size(20);
	lc->add(exer_bt);

	Button* close_bt = new Button(new SizeBuilder(Size(pointUI(200), pointUI(60)), Margin(5, 5, 5, 5), Padding(0)));
	close_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	close_bt->text = L"Выход";
	close_bt->set_font_size(20);
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