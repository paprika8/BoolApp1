#include "oopWin.h"
#include "custom_vector.h"

namespace BoolApp{
	class Composite : public View{

		public:
		ProcessView* VConstruct(ProcessView* apview) override{
			for (auto el: children){
				el->Construct();
				((PComposite*)PV)->add(el->PV);
			}
		}

		~Composite(){
			for (auto el: children){
				delete el;
			}
		}

		void add (View* aview){
			children.push(aview);
		}

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

		private:
		custom_vector<View*> children;
	};


	class PComposite : public ProcessView{
		public:

		~PComposite(){
			for (auto el: children){
				delete el;
			}
		}

		void add (ProcessView* apview){
			children.push(apview);
		}

		void remove (ProcessView* apview){
			if(children.remove(apview)){
				delete apview;
			}
		}

		ProcessView* getPView (int i){
			return children[i];
		}

		private:
		custom_vector<ProcessView*> children;
	}
}


