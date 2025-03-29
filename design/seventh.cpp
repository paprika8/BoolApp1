#include "seventh.h"
#include "games.h"
#include "../tasks/task_7/task_7.h"

namespace seventh_page
{
	LinearContainer *create_page()
	{
		LinearContainer *main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button *back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, pointUI(200, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button *) -> void
		{ win->add(games_page::create_page()); };
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;

		ScrollText *statement = new ScrollText(new SizeBuilder(Size(pointUI(800), pointUI(100)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		// SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);

		// Получаем вектор функции
		std::vector<bool> vf = task7::generate_vf();
		std::wstring vec_of_fun;
		for (auto el : vf)
		{
			if (el)
				vec_of_fun += L'1';
			else
				vec_of_fun += L'0';
		}

		statement->SetText(L"Дан вектор функции, определить КНФ: ");
		statement->SetText(vec_of_fun); // Дописываем вектор функции
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;

		Edit *input = new Edit(new SizeBuilder(Size(pointUI(450), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		input->SetUnEditText(L"Введите КНФ: ");
		input->background = in;
		input->text_color = light_t;
		input->set_font_size(25);
		input->resize = right_form;

		Button *confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, pointUI(200, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
		// confirm_bt->click = [&](Button*)->void{win->add(exercises_page::create_page());};   ПРАВИЛЬНО НЕПРАВИЛЬНО ПОДСВЕТКА КНОПКИ
		confirm_bt->text = L"Подтвердить ответ";
		confirm_bt->set_font_size(25);
		confirm_bt->background = confirm;
		confirm_bt->text_color = light_t;
		confirm_bt->resize = left_form;

		LinearContainer *statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);

		LinearContainer *confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);

		confirm_bt->click = [=](Button *) -> void
		{
			std::wstring in = input->GetText();
			std::wstring res = task7::main(in, vf);
			if (res == L"1")
			{
				// Действия при правильном ответе
				input->background = confirm;
			}
			else if (res == L"0")
			{
				// Действия при неправильном ответе
				input->background = wrong;
			}
			else if (res == L"2")
			{
				// Действия при пустом вводе
				input->background = wrong;
			}
			else if (res == L"3")
			{
				// Действия при вводе не днф
				input->background = wrong;
			}
			InvalidateRect(input->PV->hwnd, 0, 1);
		};

		main_lc->add(back_bt);
		main_lc->add(statement_lc);
		main_lc->add(input);
		main_lc->add(confirm_lc);

		return main_lc;
	}
}
