#pragma once
#include "component.h"
#include "composite.h"

namespace BoolApp
{

	class PLContainer : public PComposite
	{
	public:
		PLContainer(HWND ahwnd, View *aview) : PComposite(ahwnd, aview) {

		};

		void construction() override;

		virtual Size GetContentSize ( Size size ) {
			if(!(margin.type & MarginType::CONTENT))
				return this->size;
			Size res;
			Size asize;
			Margin amargin ( 0 , 0 , 0 , 0 );
			for ( int i = 0; i < len (); i++ ) {
				asize = getPView ( i )->GetContentSize(getPView ( i )->size).toAbsolut ( size );
				amargin = getPView ( i )->margin.toAbsolut ( size );
				if ( !is_vert_orientation )
					res = res.plusRight ( asize, amargin );
				else
					res = res.plusBottom ( asize , amargin );
			}
			return res;
		}

		~PLContainer()
		{
			
		}
	};

	class LinearContainer : public Composite
	{
	public:
		LinearContainer(Builder *abuilder = new DefaultBuilder()) : Composite(abuilder)
		{
		}

		std::wstring getSzWindowClass() override {
			return L"LinCont";
		};
		
		void Register(WNDCLASS& wca) override {
			wca.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 244, 204));
		};

		ProcessView* VConstruct(ProcessView* apv) override {
			PLContainer* pw = new PLContainer(apv->hwnd, this);
			PV = pw;
			pw->construction();
			pw->is_vert_orientation = is_vert_orientation;
			ChildsConstruct(apv);
			return pw;
		};

		LRESULT wndProc(HWND ahwnd, UINT message, WPARAM wparam, LPARAM lparam, ProcessView* ptr) override;

	private:
	};
}
