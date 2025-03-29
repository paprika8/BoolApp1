#include "tenth.h"
#include "games.h"
#include <map>
#include "../tasks/task_10/task_10.h"

namespace tenth_page
{
	std::wstring vec_to_wstring(std::vector<bool> &vf)
	{
		std::wstring res;
		for (auto el : vf)
		{
			int buf = int(el);
			res += std::to_wstring(buf);
		}
		return res;
	}

	LinearContainer *create_page()
	{
		LinearContainer *main_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(1000, percent)), Margin(0), Padding(0)));
		main_lc->is_vert_orientation = 1;
		main_lc->background = bg;

		Button *back_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		back_bt->click = [&](Button *) -> void
		{ win->add(games_page::create_page()); };
		back_bt->text = L"НАЗАД";
		back_bt->set_font_size(35);
		back_bt->background = button;
		back_bt->text_color = light_t;
		back_bt->resize = right_form;

		ScrollText *statement = new ScrollText(new SizeBuilder(Size(pointUI(900), pointUI(100)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		// SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);

		// Получаем вектор функции
		std::vector<bool> vf = task10::generate_vf();

		std::wstring vec_of_fun = vec_to_wstring(vf);

		statement->SetText(L"Дан вектор функции, определить каким предполным классам принадлежит функция: " + vec_of_fun);
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;

		std::map<std::wstring, bool> *answers = new std::map<std::wstring, bool>();

		Button *T0_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 25, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		T0_bt->click = [=](Button *) -> void
		{
			if (!(T0_bt->safe_down)) // Не была нажата
			{
				T0_bt->background = T0_bt->background - 50; // Меняем на "нажата"
				T0_bt->safe_down = true;
				(*answers)[L"T0"] = 1;
			}
			else
			{
				T0_bt->background = T0_bt->background + 50; // Меняем на "не нажата"
				T0_bt->safe_down = false;
				(*answers)[L"T0"] = 0;
			}
			InvalidateRect(T0_bt->PV->hwnd, 0, 1);
		};
		T0_bt->text = L"T0";
		T0_bt->set_font_size(40);
		T0_bt->background = in;
		T0_bt->text_color = light_t;
		T0_bt->resize = right_form;

		Button *T1_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		T1_bt->click = [=](Button *) -> void
		{
			if (!(T1_bt->safe_down)) // Не была нажата
			{
				T1_bt->background = T1_bt->background - 50; // Меняем на "нажата"
				T1_bt->safe_down = true;
				(*answers)[L"T1"] = 1;
			}
			else
			{
				T1_bt->background = T1_bt->background + 50; // Меняем на "не нажата"
				T1_bt->safe_down = false;
				(*answers)[L"T1"] = 0;
			}
			InvalidateRect(T1_bt->PV->hwnd, 0, 1);
		};
		T1_bt->text = L"T1";
		T1_bt->set_font_size(40);
		T1_bt->background = in;
		T1_bt->text_color = light_t;
		T1_bt->resize = right_form;

		Button *S_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 25, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		S_bt->click = [=](Button *) -> void
		{
			if (!(S_bt->safe_down)) // Не была нажата
			{
				S_bt->background = S_bt->background - 50; // Меняем на "нажата"
				S_bt->safe_down = true;
				(*answers)[L"S"] = 1;
			}
			else
			{
				S_bt->background = S_bt->background + 50; // Меняем на "не нажата"
				S_bt->safe_down = false;
				(*answers)[L"S"] = 0;
			}
			InvalidateRect(S_bt->PV->hwnd, 0, 1);
		};
		S_bt->text = L"S";
		S_bt->set_font_size(40);
		S_bt->background = in;
		S_bt->text_color = light_t;
		S_bt->resize = right_form;

		Button *M_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		M_bt->click = [=](Button *) -> void
		{
			if (!(M_bt->safe_down)) // Не была нажата
			{
				M_bt->background = M_bt->background - 50; // Меняем на "нажата"
				M_bt->safe_down = true;
				(*answers)[L"M"] = 1;
			}
			else
			{
				M_bt->background = M_bt->background + 50; // Меняем на "не нажата"
				M_bt->safe_down = false;
				(*answers)[L"M"] = 0;
			}
			InvalidateRect(M_bt->PV->hwnd, 0, 1);
		};
		M_bt->text = L"M";
		M_bt->set_font_size(40);
		M_bt->background = in;
		M_bt->text_color = light_t;
		M_bt->resize = right_form;

		Button *L_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		L_bt->click = [=](Button *) -> void
		{
			if (!(L_bt->safe_down)) // Не была нажата
			{
				L_bt->background = L_bt->background - 50; // Меняем на "нажата"
				L_bt->safe_down = true;
				(*answers)[L"L"] = 1;
			}
			else
			{
				L_bt->background = L_bt->background + 50; // Меняем на "не нажата"
				L_bt->safe_down = false;
				(*answers)[L"L"] = 0;
			}
			InvalidateRect(L_bt->PV->hwnd, 0, 1);
		};
		L_bt->text = L"L";
		L_bt->set_font_size(40);
		L_bt->background = in;
		L_bt->text_color = light_t;
		L_bt->resize = right_form;

		Button *confirm_bt = new Button(new SizeBuilder(Size(pointUI(300), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		confirm_bt->text = L"Подтвердить ответ";
		confirm_bt->set_font_size(25);
		confirm_bt->background = confirm;
		confirm_bt->text_color = light_t;
		confirm_bt->resize = left_form;

		LinearContainer *statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(270, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | BOTTOM), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);

		LinearContainer *confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);

		LinearContainer *row1_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(300, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row1_lc->is_vert_orientation = 0;
		row1_lc->background = bg;
		row1_lc->add(T0_bt);
		row1_lc->add(T1_bt);
		LinearContainer *row2_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(300, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row2_lc->is_vert_orientation = 0;
		row2_lc->background = bg;
		row2_lc->add(S_bt);
		row2_lc->add(M_bt);
		LinearContainer *row3_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(300, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row3_lc->is_vert_orientation = 0;
		row3_lc->background = bg;
		row3_lc->add(L_bt);

		LinearContainer *answers_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0, MarginType::LEFT | VCENTER), Padding(0)));
		answers_lc->is_vert_orientation = 1;
		answers_lc->background = bg;
		answers_lc->add(row1_lc);
		answers_lc->add(row2_lc);
		answers_lc->add(row3_lc);

		LinearContainer *bottom_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(570, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		bottom_lc->is_vert_orientation = 0;
		bottom_lc->background = bg;
		bottom_lc->add(answers_lc);
		bottom_lc->add(confirm_lc);

		confirm_bt->click = [=](Button *) -> void
		{
			// map answers с нажатыми кнопками
			std::vector<bool> res = task10::main(vf);
			if ((*answers)[L"T0"])
			{
				if ((*answers)[L"T0"] == res[0])
				{
					T0_bt->background = confirm;
				}
				else
				{
					T0_bt->background = wrong;
				}
			}
			else if(res[0])
				T0_bt->background = out;
			if ((*answers)[L"T1"])
			{
				if ((*answers)[L"T1"] == res[1])
				{
					T1_bt->background = confirm;
				}
				else
				{
					T1_bt->background = wrong;
				}
			}
			else if(res[1])
				T1_bt->background = out;
			if ((*answers)[L"S"])
			{
				if ((*answers)[L"S"] == res[2])
				{
					S_bt->background = confirm;
				}
				else
				{
					S_bt->background = wrong;
				}
			}
			else if(res[2])
				S_bt->background = out;
			if ((*answers)[L"M"])
			{
				if ((*answers)[L"M"] == res[3])
				{
					M_bt->background = confirm;
				}
				else
				{
					M_bt->background = wrong;
				}
			}
			else if(res[3])
				M_bt->background = out;
			if ((*answers)[L"L"])
			{
				if ((*answers)[L"L"] == res[4])
				{
					L_bt->background = confirm;
				}
				else
				{
					L_bt->background = wrong;
				}
			}
			else if(res[4])
				L_bt->background = out;
			InvalidateRect(L_bt->PV->hwnd, 0, 1);
			InvalidateRect(T0_bt->PV->hwnd, 0, 1);
			InvalidateRect(T1_bt->PV->hwnd, 0, 1);
			InvalidateRect(S_bt->PV->hwnd, 0, 1);
			InvalidateRect(M_bt->PV->hwnd, 0, 1);
		};

		main_lc->add(back_bt);
		main_lc->add(statement_lc);
		main_lc->add(bottom_lc);

		return main_lc;
	}
}
