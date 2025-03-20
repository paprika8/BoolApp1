#pragma once
#include <Windows.h>
#include "UIStructs.h"
#include <set>
#include <string>
#include <functional>

namespace BoolApp
{

	extern HINSTANCE instance;
	extern std::set<std::wstring> isRegistry;
	class View;
	class ProcessView;
	void init(HINSTANCE ainstance);
	int run();
	LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam);
	class PComposite;
	class PComponent;
	class Composite;
	class Component;

	class Builder
	{
	public:
		virtual void build(ProcessView *apv) = 0;
	};
	class ProcessView
	{
	public:
		std::function<void(Point, Size)> resize = [](Point, Size) -> void{};

		HWND hwnd;
		View *view;
		ProcessView *parent = 0;
		Point point = Point ( 0 , 0 );
		Size size = Size(0, 0);
		Margin margin = Margin(0, 0, 0, 0);
		Padding padding = Padding(0, 0, 0, 0);
		ProcessView(HWND ahwnd, View *aview);
		virtual ~ProcessView();

		virtual void construction() = 0;

		virtual Size GetContentSize ( Size size ) {
			return size;
		}

		Size getAbsoluteSize () {
			LPRECT buf = ( LPRECT ) malloc ( sizeof ( RECT ) );
			GetClientRect ( hwnd , buf );
			Size size = Size ( buf->right , buf->bottom );
			free ( buf );
			return size;
		}

		void Move ( Point apoint , Size asize ) {
			point = apoint;
			MoveWindow ( hwnd , point.x , point.y , asize.width , asize.height , 1 );
		}
	protected:
		
	};

	class SizeBuilder : public Builder
	{
	public:
		void build(ProcessView *apv) override;

		SizeBuilder(Size asize, Margin amargin, Padding apadding)
		{
			size = asize;
			margin = amargin;
			padding = apadding;
		}

	private:
		Size size;
		Margin margin;
		Padding padding;
	};

	class DefaultBuilder : public Builder
	{
	public:
		void build(ProcessView *apv) override
		{
			apv->size = (100, 100);
		}
	};

	class View
	{
	public:
		ProcessView *PV = 0;
		View *parent = 0;
		virtual std::wstring getSzWindowClass() = 0;
		virtual void Register(WNDCLASS&){};
		virtual void paint(HDC&, PAINTSTRUCT&){};
		virtual LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView *ptr){};
		virtual void childDeleted(View*){};
		void setBuilder(Builder* abuilder){
			delete builder;
			builder = abuilder;
		}
		void Construct()
		{
			if (PV != 0)
			{
				return;
			}
			if(parent)
				PV = VConstruct(parent->PV);
			else
				PV = VConstruct(0);
			builder->build(PV);
			enabled = true;
		}

		virtual ProcessView *VConstruct(ProcessView *apv) = 0;

		void sregister()
		{
			WNDCLASS wca = {0};
			// адрес ф-ции обработки сообщений
			wca.lpfnWndProc = (WNDPROC)BoolApp::wndProc;
			// стиль окна
			wca.style = CS_HREDRAW | CS_VREDRAW;
			// дискриптор экземпляра приложения
			// название класса
			wca.hInstance = instance;
			wca.lpszClassName = getSzWindowClass().c_str();
			// загрузка курсора
			wca.hCursor = LoadCursor(NULL, IDC_ARROW);
			// загрузка цвета окон
			wca.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
			// резерв места для указателя на PV
			wca.cbWndExtra = sizeof(void *);
			Register(wca);
			// регистрация класса
			RegisterClass(&wca);
		}

		virtual ~View()
		{
			if (parent)
			{
				parent->childDeleted(this);
			}
			if(PV)
				PV->view = 0;
			disable();
		}

		View(Builder *abuilder = new DefaultBuilder())
		{
			builder = abuilder;
		}

		virtual void enable();
		virtual void disable();

	protected:
		bool enabled = false;
		Builder *builder;
		
	};

}