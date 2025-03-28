#include "twelfth.h"
#include "exercises.h"

namespace twelfth_page{
	LinearContainer* create_page(){
		LinearContainer* main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button* back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;

		ScrollText* statement = new ScrollText(new SizeBuilder(Size(pointUI(800), pointUI(100)), Margin(5, 5, 5, 5, MarginType::RIGHT | TOP), Padding(pointUI(10, percent), 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		statement->SetText(L"ДНФ вашей функции: ");
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;

		Edit* input = new Edit(new SizeBuilder(Size(pointUI(550), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		input->SetUnEditText(L"Введите вектор функции: ");
		input->background = in;
		input->text_color = light_t;
		input->set_font_size(25);
		input->resize = left_form;

		LinearContainer* input_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		input_lc->is_vert_orientation = 0;
		input_lc->background = bg;
		input_lc->add(input);

		Button* confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		confirm_bt->text = L"Подтвердить ввод";
		confirm_bt->set_font_size(25);
		confirm_bt->background = confirm;
		confirm_bt->text_color = light_t;
		confirm_bt->resize = left_form;

		Button* random_bt = new Button(new SizeBuilder(Size(pointUI(150), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		random_bt->text = L"случайный вектор";
		random_bt->set_font_size(25);
		random_bt->background = button;
		random_bt->text_color = light_t;
		random_bt->resize = left_form;

		ScrollText* table = new ScrollText(new SizeBuilder(Size(pointUI(580), pointUI(580)), Margin(5, 5, 5, 5, MarginType::RIGHT | TOP), Padding(pointUI(10, percent), 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		table->SetText(L"");
		table->font = createFont(25);
		table->background = out;
		table->text_color = light_t;

	
	
		LinearContainer* statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);
		LinearContainer* confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);
		LinearContainer* random_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		random_lc->is_vert_orientation = 0;
		random_lc->background = bg;
		random_lc->add(random_bt);

		LinearContainer* upper_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(330, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		upper_lc->is_vert_orientation = 1;
		upper_lc->background = bg;
		upper_lc->add(random_lc);
		upper_lc->add(input_lc);

		LinearContainer* bot_vert_lc1 = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(1000, percent)), Margin(0, 0, 0, 5, MarginType::LEFT | TOP), Padding(0)));
		bot_vert_lc1->is_vert_orientation = 1;
		bot_vert_lc1->background = bg;
		bot_vert_lc1->add(table);
		LinearContainer* bot_vert_lc2 = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(900, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | TOP), Padding(0)));
		bot_vert_lc2->is_vert_orientation = 1;
		bot_vert_lc2->background = bg;
		bot_vert_lc2->add(statement_lc);
		bot_vert_lc2->add(confirm_lc);

		LinearContainer* bottom_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(670, percent)), Margin(0, 0, 0, 5, MarginType::RIGHT | VCENTER), Padding(0)));
		bottom_lc->is_vert_orientation = 0;
		bottom_lc->background = button;
		bottom_lc->add(bot_vert_lc1);
		bottom_lc->add(bot_vert_lc2);


		main_lc->add(back_bt);
		main_lc->add(upper_lc);
		main_lc->add(bottom_lc);

	
		return main_lc;
	}
}

