#include "Main.h"
#include "exercises.h"

LinearContainer* create_page_exercises(){
	LinearContainer* lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
	lc->is_vert_orientation = 1;
	lc->background = bg;
	//win.add(lc);

	Button* exer_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	exer_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	exer_bt->text = L"ЗАДАЧИ";
	exer_bt->set_font_size(35);
	exer_bt->background = button;
	exer_bt->text_color = light_t;
	lc->add(exer_bt);

	Button* games_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	games_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	games_bt->text = L"ИГРЫ";
	games_bt->set_font_size(35);
	games_bt->background = button;
	games_bt->text_color = light_t;
	lc->add(games_bt);

	Button* close_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	close_bt->click = [](Button*)->void{PostQuitMessage ( 0 );};
	close_bt->text = L"ВЫХОД";
	close_bt->set_font_size(35);
	close_bt->background = button;
	close_bt->text_color = light_t;
	lc->add(close_bt);

}

