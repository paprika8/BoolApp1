#include "nineth.h"
#include "exercises.h"
#include "../tasks/task_9/task_9.h"

namespace nineth_page{
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

		ScrollText* statement = new ScrollText(new SizeBuilder(Size(pointUI(700), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		statement->SetText(L"СКНФ функции: ");
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = right_form;

		Edit* input = new Edit(new SizeBuilder(Size(pointUI(700), pointUI(100)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		input->SetUnEditText(L"Введите вектор функции для получения его СКНФ:\n ");
		input->background = in;
		input->text_color = light_t;
		input->set_font_size(25);
		input->resize = left_form;

		LinearContainer* input_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		input_lc->is_vert_orientation = 0;
		input_lc->background = bg;
		input_lc->add(input);

		Button* confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		confirm_bt->click = [=](Button*)->void{
			statement->SetText(task9::main(input->GetText()));
		};
		confirm_bt->text = L"Подтвердить ввод";
		confirm_bt->set_font_size(25);
		confirm_bt->background = confirm;
		confirm_bt->text_color = light_t;
		confirm_bt->resize = left_form;

		LinearContainer* confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(170, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);


		// confirm_bt->click = [=](Button*)->void{
		// 	std::wstring in = input->GetText();
		// 	...


		// };


		main_lc->add(back_bt);
		main_lc->add(input_lc);
		main_lc->add(confirm_lc);
		main_lc->add(statement);


	
		return main_lc;
	}
}

