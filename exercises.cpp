#include "exercises.h"
#include "first.h"

namespace exercises_page{
	LinearContainer* create_card(std::wstring number, std::wstring exercise, std::function<LinearContainer*()> func){
	LinearContainer* lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000/3, percent), pointUI(1000/2, percent)), Margin(0,0,0,0, MarginType::CONTENT), Padding(0, 0, 0, 0)));
	lc->is_vert_orientation = 1;
	lc->background = bg;

	ScrollText* exer_number = new ScrollText(new SizeBuilder(Size(pointUI(120), pointUI(35)), Margin(5, 0, 0, 0), Padding(0, 3, 0, 0)));
	//SetWindowLongPtr(app_name->PV->hwnd, GWL_STYLE, WS_VISIBLE + WS_CHILD + BS_OWNERDRAW);
	exer_number->SetText(number);
	exer_number->font = createFont(22);
	exer_number->background = button;
	exer_number->text_color = light_t;
	lc->add(exer_number);

	Button* exer_bt = new Button(new SizeBuilder(Size(pointUI(260), pointUI(90)), Margin(5, 0, 95, 5), Padding(pointUI(10, percent), 0, 0, 0)));
	exer_bt->click = [=](Button*)->void{win->add(func());};
	exer_bt->text = exercise;
	exer_bt->set_font_size(20);
	exer_bt->background = out;
	exer_bt->text_color = light_t;
	lc->add(exer_bt);

	return lc;
}

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
		

		LinearContainer* firstrow_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | HCENTER), Padding(0)));
		firstrow_lc->is_vert_orientation = 0;
		firstrow_lc->background = bg;

		LinearContainer* secondrow_lc = new LinearContainer(new SizeBuilder(Size(pointUI(1000, percent), pointUI(370, percent)), Margin(0, 0, 0, 0, MarginType::VCENTER | HCENTER), Padding(0)));
		secondrow_lc->is_vert_orientation = 0;
		secondrow_lc->background = bg;
		


		main_lc->add(back_bt);
		firstrow_lc->add(create_card(L"Задача 1", L"булевая функция от n аргументов", first_page::create_page));
		firstrow_lc->add(create_card(L"Задача 2", L"нулевая/единичная остаточная", first_page::create_page));
		firstrow_lc->add(create_card(L"Задача 3", L"вектор функции по нулевой и единичной остаточным функциям по аргументу", first_page::create_page));
		secondrow_lc->add(create_card(L"Задача 4", L"СДНФ", first_page::create_page));
		secondrow_lc->add(create_card(L"Задача 5", L"СКНФ", first_page::create_page));
		secondrow_lc->add(create_card(L"Задача 6", L"ДНФ", first_page::create_page));

		main_lc->add(firstrow_lc);
		main_lc->add(secondrow_lc);


		


		return main_lc;
	}
}



