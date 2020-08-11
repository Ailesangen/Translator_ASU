#ifndef __CYNTAX
#define __CYNTAX
#include"defs.h"
#include"scaner.h"
#include"semant.h"
class Cyntax
{
	private:
		TScaner *sc;
		Tree *tr;
	public:
		Cyntax(TScaner *s)
		{
			sc=s;
			tr=new Tree(NULL, NULL, NULL, Node(), s);
			Tree::SetCur(tr);
		}
		~Cyntax(){}
		void Program();
		void DataDescr();
		void Main();
		void Void();
		void Expr();
		void Const();
		void BigOper();
		void Oper();
		void Assign();
		void For();
		void CallFunct();
		void VoidFunc();
		void A1();
		void A2();
		void A3();
		void A4();
		void A5();
		Tree* GetTree()
		{ 
			return tr;
		}

};
#endif
