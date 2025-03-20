#pragma once
#include "oopWin.h"
#include "custom_vector.h"

namespace BoolApp{
	
	class PComposite : public ProcessView{
		public:
		bool is_vert_orientation = 0;
		~PComposite(){
			for (auto el: children){
				delete el;
			}
		}

		void add (ProcessView* apview);

		void remove (ProcessView* apview){
			if(children.remove(apview)){
				delete apview;
			}
		}

		ProcessView* getPView (int i){
			return children[i];
		}
		int len(){
			return children.len();
		}

		private:
		custom_vector<ProcessView*> children;
	};

	class Composite : public View{

		public:
		ProcessView* VConstruct(ProcessView* apview) override{
			for (auto el: children){
				el->Construct();
				((PComposite*)PV)->add(el->PV);
			}
		}
		Composite(Builder *abuilder = new DefaultBuilder()) : View(abuilder)
		{

		}

		~Composite(){
			for (auto el: children){
				delete el;
			}
		}

		void add (View* aview);

		void remove (View* aview){
			if(children.remove(aview)){
				delete aview;
			}
		}

		View* getView (int i){
			return children[i];
		}

		void enable() override{
			for (auto el: children){
				el->enable();
			}
			View::enable();
		}

		void disable() override{
			for (auto el: children){
				el->disable();
			}
			View::disable();
		}

		void childDeleted(View* aview) override{
			children.remove(aview);
			((PComposite*)PV)->remove(aview->PV);
		}

		void paint(HDC& hdc, PAINTSTRUCT& pstruct) override {
			for(auto child : children)
				child->paint(hdc, pstruct);
		};

		private:
		custom_vector<View*> children;
	};


}


