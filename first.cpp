#include "first.h"
#include "exercises.h"

namespace first_page{
	LinearContainer* create_page(){
		LinearContainer* main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button* back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, pointUI(200, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button*)->void{win->add(create_page_main());};
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		main_lc->add(back_bt);

		ScrollText* statement = new ScrollText(new SizeBuilder(Size(pointUI(600), pointUI(100)), Margin(0), Padding(0, 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		statement->SetText(L"На вход - число n, на выходе - булевая функция от n аргументов");
		statement->font = createFont(30);
		statement->background = out;
		statement->text_color = light_t;
		main_lc->add(statement);

		Edit* input = new Edit(new SizeBuilder(Size(pointUI(100), pointUI(60)), Margin(5, 5, 5, 5), Padding(0,0,0,0)));
		input->SetUnEditText(L"Введите n:");
		input->background = in;
		//input->font_color = light_t;
		main_lc->add(input);

		ScrollText* output = new ScrollText(new SizeBuilder(Size(pointUI(600, percent), pointUI(100)), Margin(0), Padding(0, 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		output->SetText(L"На вход - число n, на выходе - булевая функция от n аргументов");
		output->font = createFont(30);
		output->background = out;
		output->text_color = light_t;
		main_lc->add(output);

		LinearContainer* statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);


		main_lc->add(back_bt);
		main_lc->add(statement_lc);
		main_lc->add(input);
		main_lc->add(output);


	
		return main_lc;
	}
}

