#include "eleventh.h"
#include "games.h"

namespace eleventh_page{
	LinearContainer* create_page(){
		LinearContainer* main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button* back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button*)->void{win->add(games_page::create_page());};
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;

		ScrollText* statement = new ScrollText(new SizeBuilder(Size(pointUI(900), pointUI(100)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		statement->SetText(L"Дан вектор функции, определить каким предполным классам принадлежит функция: ");
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;



		Button* T0_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 25, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		T0_bt->text = L"T0";
		T0_bt->set_font_size(40);
		T0_bt->background = in;
		T0_bt->text_color = light_t;
		T0_bt->resize = right_form;

		Button* T1_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		T1_bt->text = L"T1";
		T1_bt->set_font_size(40);
		T1_bt->background = in;
		T1_bt->text_color = light_t;
		T1_bt->resize = right_form;

		Button* S_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 25, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		S_bt->text = L"S";
		S_bt->set_font_size(40);
		S_bt->background = in;
		S_bt->text_color = light_t;
		S_bt->resize = right_form;

		Button* M_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		M_bt->text = L"M";
		M_bt->set_font_size(40);
		M_bt->background = in;
		M_bt->text_color = light_t;
		M_bt->resize = right_form;

		Button* L_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		L_bt->text = L"L";
		L_bt->set_font_size(40);
		L_bt->background = in;
		L_bt->text_color = light_t;
		L_bt->resize = right_form;


		Button* full_bt = new Button(new SizeBuilder(Size(pointUI(270), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		full_bt->text = L"система полна";
		full_bt->set_font_size(25);
		full_bt->background = in;
		full_bt->text_color = light_t;
		full_bt->resize = right_form;


		Button* confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		confirm_bt->text = L"Подтвердить ответ";
		confirm_bt->set_font_size(25);
		confirm_bt->background = confirm;
		confirm_bt->text_color = light_t;
		confirm_bt->resize = left_form;


		LinearContainer* statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(270, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | BOTTOM), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);

		LinearContainer* confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(500, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | BOTTOM), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);
		LinearContainer* full_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(500, percent)), Margin(0, 0, 0, 0, MarginType::LEFT | TOP), Padding(0)));
		full_lc->is_vert_orientation = 0;
		full_lc->background = bg;
		full_lc->add(full_bt);


		LinearContainer* row1_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row1_lc->is_vert_orientation = 0;
		row1_lc->background = bg;
		row1_lc->add(full_bt);
		LinearContainer* row2_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row2_lc->is_vert_orientation = 0;
		row2_lc->background = bg;
		row2_lc->add(T0_bt);
		row2_lc->add(T1_bt);
		LinearContainer* row3_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row3_lc->is_vert_orientation = 0;
		row3_lc->background = bg;
		row3_lc->add(S_bt);
		row3_lc->add(M_bt);
		LinearContainer* row4_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row4_lc->is_vert_orientation = 0;
		row4_lc->background = bg;
		row4_lc->add(L_bt);


		LinearContainer* answers_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0, MarginType::LEFT | VCENTER), Padding(0)));
		answers_lc->is_vert_orientation = 1;
		answers_lc->background = bg;
		answers_lc->add(row1_lc);
		answers_lc->add(row2_lc);
		answers_lc->add(row3_lc);
		answers_lc->add(row4_lc);

		LinearContainer* bottom_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(570, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		bottom_lc->is_vert_orientation = 0;
		bottom_lc->background = bg;
		bottom_lc->add(answers_lc);
		bottom_lc->add(confirm_lc);




		main_lc->add(back_bt);
		main_lc->add(statement_lc);
		main_lc->add(bottom_lc);



	
		return main_lc;
	}
}

