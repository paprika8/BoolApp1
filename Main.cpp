#include <Windows.h>
#include "window.h"
#include "LinearContainer.h"
#include "button.h"
#include "Text.h"
#include "Edit.h"


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
	Button* bt = new Button(new SizeBuilder(Size(pointUI(100), pointUI(60)), Margin(5, 5, 5, 5), Padding(0)));
	bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	bt->text = L"dsfdfsfsd fsdfsdf fdsfsdf fsdfsdf";
	bt->set_font_size(16);
	Edit* text = new Edit(new SizeBuilder(Size(pointUI(100), pointUI(60)), Margin(5, 5, 5, 5), Padding(0,0,20,0)));
	text->SetText(L"TEXT УБОГИЙ sdadasdasdasdasdG");
	LinearContainer* lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
	lc->is_vert_orientation = 1;
	lc->add(bt);
	lc->add(text);
	win.add(lc);

	int res = run();
	Gdiplus::GdiplusShutdown ( gdiplusToken );
	return res;
}