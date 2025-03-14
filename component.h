#include "oopWin.h"
#include "custom_vector.h"

namespace BoolApp{
	class Component : public View{

		public:
		ProcessView* VConstruct(ProcessView* apview) override{
			child->Construct();
			((PComponent*)PV)->add(child->PV);
			
		}

		~Component(){
			delete child;
		}

		void add (View* aview){
			delete child;
			child = aview;
		}

		void remove (View*){
			delete child;
			child = 0;
		}

		View* getView (int i){
			return child;
		}

		void enable() override{
			child->enable();
			View::enable();
		}

		void disable() override{
			child->disable();
			View::disable();
		}

		void childDeleted(View* aview) override{
			child = 0;
			((PComponent*)PV)->remove(aview->PV);
		}

		private:
		View* child = 0;
	};


	class PComponent : public ProcessView{
		public:

		~PComponent(){
			delete child;
		}

		void add (ProcessView* apview){
			delete apview;
			child = apview;
		}

		void remove (ProcessView* apview){
			delete child;
			child = 0;
		}

		ProcessView* getPView (int i){
			return child;
		}

		private:
		ProcessView* child = 0;
	}
}


