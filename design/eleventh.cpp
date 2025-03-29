#include "eleventh.h"
#include "games.h"
#include <map>
#include "../tasks/task_11/task_11.h"

namespace eleventh_page
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

		// Получаем набор векторов функции
		std::vector<std::vector<bool>> set_of_vec = (task11::gen_system_of_vecs());

		std::wstring str = L"Дан набор векторов функций, определите полон ли он.\nЕсли нет, то определите, каким замкнутым классам он принадлежит:\n";

		for (int i = 0; i < set_of_vec.size(); i++)
		{
			str += vec_to_wstring(set_of_vec[i]) + L'\n';
		}
		statement->SetText(str);
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;

		std::map<std::wstring, bool> *answers = new std::map<std::wstring, bool>();

		Button *full_bt = new Button(new SizeBuilder(Size(pointUI(270), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));

		Button *T0_bt = new Button(new SizeBuilder(Size(pointUI(120), pointUI(100)), Margin(5, 5, 25, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		T0_bt->click = [=](Button *) -> void
		{
			if (!(T0_bt->safe_down)) // Не была нажата
			{
				T0_bt->background = T0_bt->background - 50; // Меняем на "нажата"
				T0_bt->safe_down = true;
				(*answers)[L"T0"] = 1;

				if (full_bt->safe_down)
				{
					full_bt->background = full_bt->background + 50;
					full_bt->safe_down = false;
					(*answers)[L"full"] = 0;
				}
			}
			else
			{
				T0_bt->background = T0_bt->background + 50; // Меняем на "не нажата"
				T0_bt->safe_down = false;
				(*answers)[L"T0"] = 0;
			}
			InvalidateRect(T0_bt->PV->hwnd, 0, 1);
			InvalidateRect(full_bt->PV->hwnd, 0, 1);
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
				if (full_bt->safe_down)
				{
					full_bt->background = full_bt->background + 50;
					full_bt->safe_down = false;
					(*answers)[L"full"] = 0;
				}
			}
			else
			{
				T1_bt->background = T1_bt->background + 50; // Меняем на "не нажата"
				T1_bt->safe_down = false;
				(*answers)[L"T0"] = 0;
			}
			InvalidateRect(T1_bt->PV->hwnd, 0, 1);
			InvalidateRect(full_bt->PV->hwnd, 0, 1);
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
				if (full_bt->safe_down)
				{
					full_bt->background = full_bt->background + 50;
					full_bt->safe_down = false;
					(*answers)[L"full"] = 0;
				}
			}
			else
			{
				S_bt->background = S_bt->background + 50; // Меняем на "не нажата"
				S_bt->safe_down = false;
				(*answers)[L"S"] = 1;
			}
			InvalidateRect(S_bt->PV->hwnd, 0, 1);
			InvalidateRect(full_bt->PV->hwnd, 0, 1);
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
				if (full_bt->safe_down)
				{
					full_bt->background = full_bt->background + 50;
					full_bt->safe_down = false;
					(*answers)[L"full"] = 0;
				}
			}
			else
			{
				M_bt->background = M_bt->background + 50; // Меняем на "не нажата"
				M_bt->safe_down = false;
				(*answers)[L"M"] = 1;
			}
			InvalidateRect(M_bt->PV->hwnd, 0, 1);
			InvalidateRect(full_bt->PV->hwnd, 0, 1);
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

				if (full_bt->safe_down)
				{
					full_bt->background = full_bt->background + 50;
					full_bt->safe_down = false;
					(*answers)[L"full"] = 0;
				}
			}
			else
			{
				L_bt->background = L_bt->background + 50; // Меняем на "не нажата"
				L_bt->safe_down = false;
				(*answers)[L"L"] = 0;
			}
			InvalidateRect(L_bt->PV->hwnd, 0, 1);
			InvalidateRect(full_bt->PV->hwnd, 0, 1);
		};
		L_bt->text = L"L";
		L_bt->set_font_size(40);
		L_bt->background = in;
		L_bt->text_color = light_t;
		L_bt->resize = right_form;

		full_bt->click = [=](Button *) -> void
		{
			if (!(full_bt->safe_down))
			{
				full_bt->background = full_bt->background - 50;
				full_bt->safe_down = true;
				(*answers)[L"full"] = 1;
				if (L_bt->safe_down)
				{
					L_bt->background = L_bt->background + 50; // Меняем на "не нажата"
					L_bt->safe_down = false;
					(*answers)[L"L"] = 0;
				}
				if (T0_bt->safe_down)
				{
					T0_bt->background = T0_bt->background + 50; // Меняем на "не нажата"
					T0_bt->safe_down = false;
					(*answers)[L"T0"] = 0;
				}
				if (T1_bt->safe_down)
				{
					T1_bt->background = T1_bt->background + 50; // Меняем на "не нажата"
					T1_bt->safe_down = false;
					(*answers)[L"T1"] = 0;
				}
				if (M_bt->safe_down)
				{
					M_bt->background = M_bt->background + 50; // Меняем на "не нажата"
					M_bt->safe_down = false;
					(*answers)[L"M"] = 0;
				}
				if (S_bt->safe_down)
				{
					S_bt->background = S_bt->background + 50; // Меняем на "не нажата"
					S_bt->safe_down = false;
					(*answers)[L"S"] = 0;
				}
			}
			else
			{
				full_bt->background = full_bt->background + 50;
				full_bt->safe_down = false;
			}

			InvalidateRect(full_bt->PV->hwnd, 0, 1);
			InvalidateRect(L_bt->PV->hwnd, 0, 1);
			InvalidateRect(T0_bt->PV->hwnd, 0, 1);
			InvalidateRect(T1_bt->PV->hwnd, 0, 1);
			InvalidateRect(S_bt->PV->hwnd, 0, 1);
			InvalidateRect(M_bt->PV->hwnd, 0, 1);
		};
		full_bt->text = L"система полна";
		full_bt->set_font_size(25);
		full_bt->background = in;
		full_bt->text_color = light_t;
		full_bt->resize = right_form;

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

		LinearContainer *confirm_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(500, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | BOTTOM), Padding(0)));
		confirm_lc->is_vert_orientation = 0;
		confirm_lc->background = bg;
		confirm_lc->add(confirm_bt);
		LinearContainer *full_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(500, percent)), Margin(0, 0, 0, 0, MarginType::LEFT | TOP), Padding(0)));
		full_lc->is_vert_orientation = 0;
		full_lc->background = bg;
		full_lc->add(full_bt);

		LinearContainer *row1_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row1_lc->is_vert_orientation = 0;
		row1_lc->background = bg;
		row1_lc->add(full_bt);
		LinearContainer *row2_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row2_lc->is_vert_orientation = 0;
		row2_lc->background = bg;
		row2_lc->add(T0_bt);
		row2_lc->add(T1_bt);
		LinearContainer *row3_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row3_lc->is_vert_orientation = 0;
		row3_lc->background = bg;
		row3_lc->add(S_bt);
		row3_lc->add(M_bt);
		LinearContainer *row4_lc = new LinearContainer(new SizeBuilder(Size(pointUI(300, percent), pointUI(200, percent)), Margin(0, 0, 0, 0), Padding(0)));
		row4_lc->is_vert_orientation = 0;
		row4_lc->background = bg;
		row4_lc->add(L_bt);

		LinearContainer *answers_lc = new LinearContainer(new SizeBuilder(Size(pointUI(500, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0, MarginType::LEFT | VCENTER), Padding(0)));
		answers_lc->is_vert_orientation = 1;
		answers_lc->background = bg;
		answers_lc->add(row1_lc);
		answers_lc->add(row2_lc);
		answers_lc->add(row3_lc);
		answers_lc->add(row4_lc);

		LinearContainer *bottom_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(570, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		bottom_lc->is_vert_orientation = 0;
		bottom_lc->background = bg;
		bottom_lc->add(answers_lc);
		bottom_lc->add(confirm_lc);

		confirm_bt->click = [=](Button *) -> void
		{
			std::vector<bool> classes;
			bool full = 0;
			std::wstring res = task11::main(set_of_vec, classes, full);
			if (full)
			{
				if((*answers)[L"full"])
					full_bt->background = confirm;
				else
					full_bt->background = wrong;
				full_bt->safe_down = 0;
				(*answers)[L"full"] = 0;
			}
			else
			{
				if ((*answers)[L"T0"])
				{
					if ((*answers)[L"T0"] == classes[0])
					{
						T0_bt->background = confirm;
					}
					else
					{
						T0_bt->background = wrong;
					}
					T0_bt->safe_down = 0;
					(*answers)[L"T0"] = 0;
				}
				else if((*answers)[L"T0"] != classes[0])
					T0_bt->background = wrong;
				if ((*answers)[L"T1"])
				{
					if ((*answers)[L"T1"] == classes[1])
					{
						T1_bt->background = confirm;
					}
					else
					{
						T1_bt->background = wrong;
					}
					T1_bt->safe_down = 0;
					(*answers)[L"T1"] = 0;
				}
				else if((*answers)[L"T1"] != classes[1])
					T1_bt->background = wrong;
				if ((*answers)[L"S"])
				{
					if ((*answers)[L"S"] == classes[2])
					{
						S_bt->background = confirm;
					}
					else
					{
						S_bt->background = wrong;
					}
					S_bt->safe_down = 0;
					(*answers)[L"S"] = 0;
				}
				else if((*answers)[L"S"] != classes[2])
					S_bt->background = wrong;
				if ((*answers)[L"M"])
				{
					if ((*answers)[L"M"] == classes[3])
					{
						M_bt->background = confirm;
					}
					else
					{
						M_bt->background = wrong;
					}
					M_bt->safe_down = 0;
					(*answers)[L"M"] = 0;
				}
				else if((*answers)[L"M"] != classes[3])
					M_bt->background = wrong;
				if ((*answers)[L"L"])
				{
					if ((*answers)[L"L"] == classes[4])
					{
						L_bt->background = confirm;
					}
					else
					{
						L_bt->background = wrong;
					}
					L_bt->safe_down = 0;
					(*answers)[L"L"] = 0;
				}
				else if((*answers)[L"L"] != classes[4])
					L_bt->background = wrong;
			}
			InvalidateRect(full_bt->PV->hwnd, 0, 1);
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