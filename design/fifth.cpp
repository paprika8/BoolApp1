#pragma once 
#include "fifth.h"
#include "games.h"
#include "../tasks/task_5/task_5.h"

namespace fifth_page
{
	LinearContainer *create_page()
	{
		LinearContainer *main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button *back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, pointUI(200, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button *) -> void{ 
			win->add(games_page::create_page()); 
		};
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;

		ScrollText *statement = new ScrollText(new SizeBuilder(Size(pointUI(800), pointUI(100)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		// SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);

		// Получаем вектор функции и фиктивность переменных
		std::wstring res = task5::main();
		// std::vector<bool> *vec_of_fun = new std::vector<bool>();
		std::wstring vec_of_fun;	  //= new std::wstring();
		std::vector<bool> vars(1, 0); //= new std::vector<bool>();
		int vars_cnt = 0;
		int i = 0;
		while (res[i] != L' ') {
			vec_of_fun += res[i];
			// vec_of_fun->push_back((*res)[i] == L'1' ? true : false);
			i++;
		}
		i++;
		for (; i < res.size(); i++)
		{
			int buf = int(res[i] - L'0');
			vars_cnt += buf;
			vars.push_back(buf);
		}

		statement->SetText(L"Дан вектор функции, определить существенные и фиктивные переменные: " + vec_of_fun);
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;

		Edit *input = new Edit(new SizeBuilder(Size(pointUI(450), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		input->SetUnEditText(L"Перечислите\nсущественные переменные: ");
		input->background = in;
		input->text_color = light_t;
		input->set_font_size(25);
		input->resize = right_form;

		Button *confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, pointUI(200, percent)), Padding(pointUI(10, percent), 0, 0, 0)));
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

		confirm_bt->click = [=](Button *but) -> void
		{
			std::wstring answer = input->GetText();
			// std::wstring res = task5::main();
			int vars_cnt2 = 0;
			bool ans_status = true;
			for (auto ch : answer)
			{
				if (ch > L'9' || ch < L'1')
				{
					continue;
				}
				if (int(ch - L'0') >= vars.size())
				{
					ans_status = false;
					break;
				}
				if (!vars[int(ch - L'0')]) // В один индексации
				{
					ans_status = false;
					break;
				}
				else
				{
					vars_cnt2++;
				}
			}
			if (ans_status && vars_cnt2 >= vars_cnt)
			{
				input->background = confirm;
			}
			else
			{
				input->background = (192, 64, 66);
			}
		};

		main_lc->add(back_bt);
		main_lc->add(statement_lc);
		main_lc->add(input);
		main_lc->add(confirm_lc);

		return main_lc;
	}
}
