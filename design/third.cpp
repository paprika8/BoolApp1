#include "third.h"
#include "exercises.h"

namespace third_page{
	LinearContainer* create_page(){
		LinearContainer* main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button* back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, pointUI(200, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;

		ScrollText* statement = new ScrollText(new SizeBuilder(Size(pointUI(850), pointUI(110)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		statement->SetText(L"На вход - нулевая и единичная остаточные и номер агрумента, на выходе - вектор функции");
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;

		Button* confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		confirm_bt->text = L"Подтвердить ввод";
		confirm_bt->set_font_size(25);
		confirm_bt->background = confirm;
		confirm_bt->text_color = light_t;
		confirm_bt->resize = left_form;
		LinearContainer* confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(170, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);

		Edit* input1 = new Edit(new SizeBuilder(Size(pointUI(370), pointUI(70)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		input1->SetUnEditText(L"Нулевая остаточная\nфункция: ");
		input1->background = in;
		input1->text_color = light_t;
		input1->set_font_size(25);
		input1->resize = right_form;
		
		Edit* input2 = new Edit(new SizeBuilder(Size(pointUI(370), pointUI(70)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		input2->SetUnEditText(L"Единичная остаточная\nфункция: ");
		input2->background = in;
		input2->text_color = light_t;
		input2->set_font_size(25);
		input2->resize = right_form;

		Edit* input3 = new Edit(new SizeBuilder(Size(pointUI(370), pointUI(60)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		input3->SetUnEditText(L"Номер аргумента: ");
		input3->background = in;
		input3->text_color = light_t;
		input3->set_font_size(25);
		input3->resize = right_form;

		ScrollText* output = new ScrollText(new SizeBuilder(Size(pointUI(800), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		output->SetText(L"*вывод вектора ф-ции*");
		output->font = createFont(25);
		output->background = out;
		output->text_color = light_t;
		output->resize = right_form;

		LinearContainer* statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(170, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);


		main_lc->add(back_bt);
		main_lc->add(statement_lc);
		main_lc->add(confirm_lc);
		main_lc->add(input1);
		main_lc->add(input2);
		main_lc->add(input3);
		main_lc->add(output);


	
		return main_lc;
	}
}

