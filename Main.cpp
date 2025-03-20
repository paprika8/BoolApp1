#include <Windows.h>
#include "window.h"
#include "button.h"

using namespace BoolApp;

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR lpCmdLine, int nshow){
	Window win(new SizeBuilder(Size(500, 500), Margin(0,0,0,0, MarginType::TOP | MarginType::LEFT), Padding(0)));
	win.add(new Button(new SizeBuilder(Size(pointUI(400, percent), pointUI(400, percent)), Margin(100, 100, 100, 100), Padding(0))));

	return run();
}