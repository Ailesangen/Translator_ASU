#include"defs.h"
#include"scaner.h"
#include"semant.h"
#include"syntax.h"
#include<iostream>
#include<stdio.h>
using namespace std;
//endoffile
void Cyntax::Program()
{
	TypeLex l;
	int t;

	int tempPos = sc->GetUK();
	int firstPos = tempPos; //эtо первая позиция для GlobalDataDescr, чтобы вернуть позицию
	t = sc->Scaner(l);
	while (t != TEnd)
	{

		if (t == TInt)	//int'ом мб main или DataDescr
		{
			tempPos = sc->GetUK();
			t = sc->Scaner(l);

			if (t == TMain)
			{
				sc->PutUK(tempPos);

				Tree* i = Tree::GetCur()->SetLeft(Node("main", DATA_TYPE::TYPE_FUNCT, 0, false));
				Tree::SetCur(i);

				Main();
				printf("\n<Main Func>\n");
			}
			else
			{
				//т.к. это глобальные данные, а DataDescr работает с позиции после int/char, то нужно вернуть указатель для него в начало
				sc->PutUK(firstPos);
				DataDescr();
				printf("\n<GlobalDataDesc>\n");
			}

		}
		else if (t == TChar)
		{
			sc->PutUK(tempPos);
			DataDescr();
			printf("\n<DataDesc>\n");
		}
		else if (t == TVoid)
		{

			sc->PutUK(tempPos);
			//Tree* i = Tree::GetCur()->SetLeft(Node(l, DATA_TYPE::TYPE_FUNCT, 0, false));
			//Tree::SetCur(i);
			VoidFunc();
			printf("\n<VoidFunct>\n");
		}
		else
		{
			sc->PrintError("Wrong synt: ", l);
		}
		tempPos = sc->GetUK();
		t = sc->Scaner(l);
	}

}

void Cyntax::DataDescr() //описание данных
{
	TypeLex l; int t;

	t = sc->Scaner(l);
	if ((t != TInt) && (t != TChar))
		sc->PrintError("ожидался символ int или char", l);

	//Тип приобретает в момент описания.
	/*DATA_TYPE {TYPE_UNKNOWN=1, TYPE_INTEGER,
				TYPE_CHAR, TYPE_FUNCT };*/
	DATA_TYPE type = t == TInt ? TYPE_INTEGER : TYPE_CHAR;
	//прочитали тип, int a;
	//cout << type << endl;
	int tempPos;
	do
	{
		t = sc->Scaner(l);
		if (t != TIdent)
			sc->PrintError("ожидался символ ident", l);

		//Должна быть описана только один раз в блоке. Проверка на повторное описание на одном уровне
		Tree::GetCur()->TwiceVarInit(l);

		Tree* i = Tree::GetCur()->SetLeft(Node(l, type, 0, false)); //новый узел с идент
		Tree::SetCur(i);
		std::cout << "DataDescr(int or char)" << std::endl;
		t = sc->Scaner(l);
		if (t == TAssign)
		{
			A1();
			/*t = sc->Scaner(l);
			if (t != TConstInt10 && t != TConstInt8 && t != TConstChar)
				sc->PrintError("ожидалось значение после идентификатора ", l);*/
			t = sc->Scaner(l);

		}
	} while (t == TZpt);
	if (t != TTZ)
		sc->PrintError("ожидался символ ;", l);
}
void Cyntax::Main()
{
	TypeLex l; int t;
	t = sc->Scaner(l);
	if (t != TMain)
		sc->PrintError("ожидался символ Main", l);

	t = sc->Scaner(l);
	if (t != TOBrace) sc->PrintError("Не стоит открывающая скобка", l);

	t = sc->Scaner(l);
	if (t != TCBrace) sc->PrintError("Не стоит закрывающая скобка", l);


	BigOper();
}


void Cyntax::Const()
{
	TypeLex l; int t;
	t = sc->Scaner(l);
	if ((t != TConstInt10) && (t != TConstInt8) && (t != TConstChar))
		sc->PrintError("CONST::ожидался символ constInt10 или constInt10 или constChar", l);

}
void Cyntax::BigOper()
{
	TypeLex l; int t; int tempPos;
	t = sc->Scaner(l);
	if (t != TOCurly)
		sc->PrintError("ожидался символ {", l);

	Tree* spl = Tree::GetCur();
	Tree* i = Tree::GetCur()->SetRight(Node());
	Tree::SetCur(i);

	tempPos = sc->GetUK();
	t = sc->Scaner(l);
	while (t != TCCurly)
	{

		if (t == TInt || t == TChar)
		{
			sc->PutUK(tempPos);
			DataDescr();
		}
		else if (t == TIdent || t == TTZ || t == TOCurly || t == TFor)
		{
			sc->PutUK(tempPos);
			Oper();
		}
		else
			sc->PrintError("Некорректный символ в BigOper", l);

		tempPos = sc->GetUK();
		t = sc->Scaner(l);
		//if (t != TCCurly) sc->PrintError("Не стоит закрывающая фиг.скобка в BigOper", l);

	}
	Tree::SetCur(spl);
}
void Cyntax::Oper()
{
	TypeLex l; int t;
	int tempPos = sc->GetUK();
	t = sc->Scaner(l);
	if (t == TTZ) {}
	else if (t == TFor)
	{
		For();
	}
	else if (t == TOCurly)
	{
		sc->PutUK(tempPos);
		/*Tree* spl = Tree::GetCur();
		Tree* i = Tree::GetCur()->SetRight(Node());
		Tree::SetCur(i);*/
		BigOper();
		//Tree::SetCur(spl);

	}
	else if (t == TIdent)
	{
		t = sc->Scaner(l);
		if (t == TOBrace)
		{
			sc->PutUK(tempPos);
			CallFunct();
		}
		else if (t == TAssign)
		{
			sc->PutUK(tempPos);
			Assign();
		}
		else
		{
			sc->PrintError("ожидался символ Equal or For or ; or CallFunct or BigOper", l);
		}
	}
}
void Cyntax::Assign()
{
	TypeLex l; int t;
	t = sc->Scaner(l);
	if (t != TIdent)
		sc->PrintError("Assign::ожидался символ ident", l);
	t = sc->Scaner(l);
	if (t != TAssign)
		sc->PrintError("Assign::ожидался символ =", l);
	A1();
	t = sc->Scaner(l);
	/*if (t != TTZ)
		sc->PrintError("Assign::ожидался символ ;", l);*/
}
void Cyntax::For()
{
	
	TypeLex l;
	int t = sc->Scaner(l);
	/*if (t != TFor)
		sc->PrintError("ожидался символ for", l);*/
		//t = sc->Scaner(l);
	if (t != TOBrace)
		sc->PrintError("ожидался символ (", l);
	//запоммнить позицию
	//проверка на type или ident
	//уходим в DataDescr или Assign
	//или ; и идем дальше
	int tempPos = sc->GetUK();
	t = sc->Scaner(l);
	if (t == TInt || t == TChar)
	{
		Tree* i = Tree::GetCur()->SetLeft(Node("for", DATA_TYPE::TYPE_FOR, 0, false));
		Tree::SetCur(i);
		i = Tree::GetCur()->SetRight(Node());
		Tree::SetCur(i);
		sc->PutUK(tempPos);
		DataDescr();
		/*Tree* i = Tree::GetCur()->SetLeft(Node("for", DATA_TYPE::TYPE_FOR, 0, false));
		Tree::SetCur(i);*/
		
	}
	else if (t == TIdent) 
	{
		sc->PutUK(tempPos);
		Assign();
	}
	else if(t!=TTZ)
	{
		sc->PrintError("ожидался символ ;", l);
	}
	//выражение
	A1();
	t = sc->Scaner(l);

	
	if (t != TTZ)
	{
		sc->PrintError("ожидался символ ;", l);
	}
	tempPos = sc->GetUK();
	t = sc->Scaner(l);
	sc->PutUK(tempPos);

	if(t==TIdent)
		Assign();
	//t = sc->Scaner(l);
	tempPos = sc->GetUK();
	t = sc->Scaner(l);
	sc->PutUK(tempPos);

	if (t == TOCurly)
		Oper();
	//t = sc->Scaner(l);
	/*if (t != TCCurly)
		sc->PrintError("ожидался символ )", l);*/
}
void Cyntax::CallFunct()
{
	TypeLex l;
	int t = sc->Scaner(l);
	if (t != TIdent)
		sc->PrintError("ожидался символ ident", l);
	
	t = sc->Scaner(l);
	if (t != TOBrace)
		sc->PrintError("ожидался символ (", l);
	t = sc->Scaner(l);
	if (t != TCBrace)
		sc->PrintError("ожидался символ )", l);
	t = sc->Scaner(l);
	if (t != TTZ)
		sc->PrintError("ожидался символ ;", l);
}

void Cyntax::VoidFunc()
{
	TypeLex l; int t;
	t = sc->Scaner(l);
	if (t != TVoid)
		sc->PrintError("ожидался символ void", l);
	t = sc->Scaner(l);
	if (t != TIdent)
		sc->PrintError("ожидался символ ident", l);
	//semant
	Tree::GetCur()->TwiceFunInit(l);
	Tree* i = Tree::GetCur()->SetLeft(Node(l, DATA_TYPE::TYPE_FUNCT, 0, false));
	Tree::SetCur(i);
	t = sc->Scaner(l);
	if (t != TOBrace)
		sc->PrintError("ожидался символ (", l);
	t = sc->Scaner(l);
	if (t != TCBrace)
		sc->PrintError("ожидался символ )", l);
	BigOper();
	/*t = sc->Scaner(l);
	if (t != TTZ)
		sc->PrintError("ожидался символ ;", l);*/
}
void Cyntax::A1()
{
	TypeLex l; int t;
	A2();
	int tempPos = sc->GetUK();
	t = sc->Scaner(l);
	while (t == TEqual || t == TNotEqual)
	{
		A2();
		tempPos = sc->GetUK();
		t = sc->Scaner(l);
	}
	sc->PutUK(tempPos);
}
void Cyntax::A2()
{
	TypeLex l; int t;
	A3();
	int tempPos = sc->GetUK();
	t = sc->Scaner(l);
	while (t == TME || t == TLE || t == TLess || t == TMore)
	{
		A3();
		tempPos = sc->GetUK();
		t = sc->Scaner(l);
	}
	sc->PutUK(tempPos);
}
void Cyntax::A3()
{
	TypeLex l; int t;
	A4();
	int tempPos = sc->GetUK();
	t = sc->Scaner(l);
	while (t == TPlus || t == TMinus)
	{
		A4();
		tempPos = sc->GetUK();
		t = sc->Scaner(l);
	}
	sc->PutUK(tempPos);

}
void Cyntax::A4()
{
	TypeLex l; int t;
	A5();
	int tempPos = sc->GetUK();
	t = sc->Scaner(l);
	while (t == TMult || t == TDiv || t == TMod)
	{
		A5();
		tempPos = sc->GetUK();
		t = sc->Scaner(l);
	}
	sc->PutUK(tempPos);

}
void Cyntax::A5()
{
	TypeLex l;
	int t = sc->Scaner(l);
	if (t == TIdent)
	{
		Tree::GetCur()->UseNoExistVar(l);
	}
	else if (t == TOBrace)
	{
		A1();
		t = sc->Scaner(l);
		if (t != TCBrace)
			sc->PrintError("A5::ожидался символ )", l);
	}
	else if ((t != TConstInt10) && (t != TConstInt8) && (t != TConstChar))
	{
		sc->PrintError("A5::ожидался символ constInt10 или constInt10 или constChar", l);
	}
}
