#include "games.h"
#include "fourth.h"
#include "fifth.h"
#include "sixth.h"
#include "seventh.h"
#include "tenth.h"
#include "eleventh.h"

namespace games_page{
	LinearContainer* create_card(std::wstring number, std::wstring game, std::function<LinearContainer*()> func){
	LinearContainer* lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000/3, percent), pointUI(1000/2, percent)), Margin(0,0,0,0, MarginType::CONTENT), Padding(0, 0, 0, 0)));
	lc->is_vert_orientation = 1;
	lc->background = bg;

	ScrollText* game_number = new ScrollText(new SizeBuilder(Size(pointUI(120), pointUI(35)), Margin(5, 0, 0, 0), Padding(0, 3, 0, 0)));
	//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
	game_number->SetText(number);
	game_number->font = createFont(22);
	game_number->background = button;
	game_number->text_color = light_t;
	game_number->resize = right_form;
	lc->add(game_number);

	Button* game_bt = new Button(new SizeBuilder(Size(pointUI(260), pointUI(90)), Margin(5, 0, 95, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	game_bt->click = [=](Button*)->void{win->add(func());};
	game_bt->text = game;
	game_bt->set_font_size(20);
	game_bt->background = out;
	game_bt->text_color = light_t;
	game_bt->resize = right_form;
	lc->add(game_bt);

	return lc;
}

	LinearContainer* create_page(){
		LinearContainer* main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button* back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, pointUI(100, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button*)->void{win->add(create_page_main());};
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;
		main_lc->add(back_bt);

		LinearContainer* firstrow_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | HCENTER), Padding(0)));
		firstrow_lc->is_vert_orientation = 0;
		firstrow_lc->background = bg;

		LinearContainer* secondrow_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | HCENTER), Padding(0)));
		secondrow_lc->is_vert_orientation = 0;
		secondrow_lc->background = bg;
		

		firstrow_lc->add(create_card(L"Игра 1", L"имя функции", fourth_page::create_page));
		firstrow_lc->add(create_card(L"Игра 2", L"существенные и фиктивные переменные", fifth_page::create_page));
		firstrow_lc->add(create_card(L"Игра 3", L"ДНФ", sixth_page::create_page));
		secondrow_lc->add(create_card(L"Игра 4", L"КНФ", seventh_page::create_page));
		secondrow_lc->add(create_card(L"Игра 5", L"предполные классы", tenth_page::create_page));
		secondrow_lc->add(create_card(L"Игра 6", L"полные системы", eleventh_page::create_page));

		main_lc->add(firstrow_lc);
		main_lc->add(secondrow_lc);


		


		return main_lc;
	}

}


