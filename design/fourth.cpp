#include "fourth.h"
#include "games.h"
#include <map>
#include "../tasks/task_4/task_4.h"

namespace fourth_page{

	std::wstring int_to_string(int x){
		std::wstring res = L"";
		for(int i = 0; i < 4; i++){
			res = L" " + res;
			res[0] = (x % 2 + L'0');
			x /= 2;
		}
		return res;
	}

	LinearContainer* create_page(){

		//std::map <std::wstring, bool> *answers = new std::map <std::wstring, bool> ();
		Button** ansxer = new Button*();

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

		Button* again_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 5, 5, 5), Padding(pointUI(10, percent), 0, 0, 0)));
		again_bt->click = [&](Button*)->void{win->add(fourth_page::create_page());};
		again_bt->text = L"ЗАНОВО";
		again_bt->set_font_size(35);
		again_bt->background = button;
		again_bt->text_color = light_t;
		again_bt->resize = right_form;

		std::wstring *answer = new std::wstring();
		std::wstring res = task4::main(*answer);

		ScrollText* statement = new ScrollText(new SizeBuilder(Size(pointUI(850), pointUI(110)), Margin(5, 5, 5, 5, MarginType::RIGHT | VCENTER), Padding(pointUI(10, percent), 0, 0, 0)));
		//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
		statement->SetText(L"Дан вектор функции: "+res+L", определите имя: ");
		statement->font = createFont(25);
		statement->background = out;
		statement->text_color = light_t;
		statement->resize = left_form;



		LinearContainer* buttons_lc = new LinearContainer(new SizeBuilder(Size(pointUI(400, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0), Padding(0)));
		buttons_lc->is_vert_orientation = 1;
		buttons_lc->background = bg;
		buttons_lc->add(back_bt);
		buttons_lc->add(again_bt);

		LinearContainer* statement_lc = new LinearContainer(new SizeBuilder(Size(pointUI(600, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | RIGHT), Padding(0)));
		statement_lc->is_vert_orientation = 0;
		statement_lc->background = bg;
		statement_lc->add(statement);

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


		LinearContainer* upper_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(300, percent)), Margin(0, 0, 0, 0, MarginType::RIGHT | VCENTER), Padding(0)));
		upper_lc->is_vert_orientation = 0;
		upper_lc->background = bg;
		upper_lc->add(buttons_lc);
		upper_lc->add(statement_lc);

		LinearContainer* answer_hor_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | HCENTER), Padding(0)));
		answer_hor_lc->is_vert_orientation = 0;
		answer_hor_lc->background = bg;


		
		for(int i = 0; i < 4; i++){

			LinearContainer* answer_ver_lc = new LinearContainer(new SizeBuilder(Size(pointUI(230, percent), pointUI(1000, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | HCENTER), Padding(0)));
			answer_ver_lc->is_vert_orientation = 1;
			answer_ver_lc->background = bg;

			for(int j = 0; j < 4; j++){
				Button* answer_bt = new Button(new SizeBuilder(Size(pointUI(250), pointUI(80)), Margin(5, 10, 5, 10), Padding(pointUI(10, percent), 0, 0, 0)));
				answer_bt->click = [=](Button* but)->void{
					std::wstring this_answer = answer_bt->text;
					if(!but->safe_down)
						answer_bt->background = answer_bt->background - 50;
					//else
						//answer_bt->background = answer_bt->background + 50;

					//(*answers)[this_answer] = but->safe_down;
					if(*ansxer && !(*ansxer)->safe_down){
						(*ansxer)->background = (*ansxer)->background + 50;
						InvalidateRect((*ansxer)->PV->hwnd, 0, 1);
					}
					*ansxer = but;
				};
				answer_bt->text = task4::get_name(j + i*4);//int_to_string(j + i*4);
				answer_bt->set_font_size(25);
				answer_bt->background = in;
				answer_bt->text_color = light_t;
				answer_bt->resize = right_form;

				answer_ver_lc->add(answer_bt);
			}
			answer_hor_lc->add(answer_ver_lc);
		}


		confirm_bt->click = [=](Button*)->void{
			
			// if ответ правильный{
			//   меняем цвет соответст кнопки на зеленый
			//}
			// else
			// меняем цвет на красный
			if((*ansxer)){
				if((*ansxer)->text == *answer)
					(*ansxer)->background = confirm;
				else
					(*ansxer)->background = Gdiplus::Color(192,64,66);
				(*ansxer)->safe_down = 1;
				if((*ansxer)->PV->hwnd)
					InvalidateRect((*ansxer)->PV->hwnd, 0, 1);
			}
		};

		main_lc->add(upper_lc);
		main_lc->add(confirm_lc);
		main_lc->add(answer_hor_lc);

	
		return main_lc;
	}
}

