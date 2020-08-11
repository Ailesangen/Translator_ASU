#include <string.h>
#include "defs.h"
#include "scaner.h"
#include "semant.h"
#define max(a,b) a<b ? b : a
Tree* Tree::Cur=(Tree*)NULL;

void Tree::SetCur(Tree * a) { Cur = a; }

//два конструктора Tree::Tree();
Tree::Tree()
{
	//char t[] = {'0'};
	n=Node();
	/*n->id=0;
	n->DataType=EMPTY;
	n->FuncFlag=false;
	n->Param=0;*/
	sc=0;
	this->Left=this->Right=this->Up=NULL;
}

Tree * Tree::GetCur() { return Cur; }

Tree::Tree(Tree * l,Tree * r, Tree * u,Node Data, TScaner * sc)
{
	this->Left=l;
	this->Right=r;
	this->Up=u;
	this->n=Data;
	this->sc=sc;
}



/*Tree * Tree::SemInclude(TypeLex a,DATA_TYPE t)
{
	if (DupControl(Cur,a))	//проверка на повторное описание
		sc->PrintError("Повторное описание идент. ", a);
	Tree * v; Node b;
	if (t!=TYPE_FUNCT) 
	{
		memcpy(b.id,a,strlen(a)+1);
		b.Param=0;
		Cur->SetLeft(&b);
		Cur=Cur->Left;
		return Cur;
	}
	else
	{
		memcpy(b.id,a,strlen(a)+1);
		b.DataType = t;

		Cur->SetLeft(&b);
		Cur = Cur -> Left;
		v = Cur;

		memcpy(&b.id,&"",2);
		b.DataType = EMPTY;
		b.Param=0;
		Cur->SetRight(&b);
		return v;
	}
}*/

/*void Tree::SemSetType(Tree* Addr,DATA_TYPE t)
{
	Addr->n->DataType=t;
}*/
/*void Tree::SemSetParam(Tree* Addr,int num) 
{
	Addr->n->Param=num;
}*/
/*void Tree::SemControlParam(Tree *Addr,int num)
{
	if(num!=Addr->n->Param)
		sc->PrintError("Неверное число параметров у функции ",Addr->n->id);
}*/
/*Tree * Tree::SemGetType(TypeLex a) //find var "a" and return node's ref
{
	Tree * v=FindUp(Cur,a);
	if(v==NULL)
		sc->PrintError("Отсутствует описание идент. ",a);
	if(v->n->DataType==TYPE_FUNCT)
		sc->PrintError("Неверное использование функции ",a);
	return v;
}*/

/*Tree * Tree::SemGetFunct(TypeLex a)
{
	Tree * v=FindUp(Cur,a);
	if(v==NULL)
		sc->PrintError("Отсутствует описание функции ", a);
	if(v->n->DataType!=TYPE_FUNCT)
		sc->PrintError("Не является функцией идентификатор ",a);
	return v;
}*/

int Tree::DupControl(TypeLex a) 
{
	Tree* i = Tree::GetCur()->FindUp(a);

	return i != nullptr;
}
Tree* Tree::SetLeft(Node Data) 
{
	Tree * a=new Tree(NULL,NULL,this,Data,sc);
	Left=a;

	return a;
}
Tree* Tree::SetRight(Node Data) 
{
	Tree * a=new Tree(NULL,NULL,this,Data,sc);
	Right=a;

	return a;
}

Tree* Tree::FindUp(TypeLex id)
{
	return FindUp(this, id);
}
Tree * Tree::FindUp(Tree * from,TypeLex id) 
{
	Tree* i=from;
	//&& (memcmp(id, i->n->id, max(strlen(i->n->id), strlen(id))) != 0)
	while (i != NULL) {
		if (strcmp(id, i->n.id) != 0)
			i = i->Up;
		else
			break;
	}
	return i;
}
Tree * Tree::FindUpOneLevel(Tree * from,TypeLex id) {
	Tree* i = from;
	while (i->n.DataType != EMPTY)
	{
		if (strcmp(id, i->n.id) != 0)
			i = i->Up;
		else
			break;
	}
	return i;
}


void Tree::Print(int level)
{
	const char* types[] = { "NONE", "TYPE_UNKNOWN", "TYPE_INTEGER", "TYPE_CHAR", "TYPE_FUNC", "TYPE_FUN" };

	printf("Tree node: %s of type %s", n.id, n.DataType == -1 ? "UNKNOWN" : types[n.DataType]);
	//if (Left != nullptr) printf("Left data: %s", Left->node.id);
	//if (Right != nullptr) printf("Right data: %s", Right->node.id);
	printf("\n");
	if (Right != nullptr)
	{
		for (int i = 0; i < level + 1; ++i)
			printf("  ");
		Right->Print(level + 1);
	}

	if (Left != nullptr)
	{
		for (int i = 0; i < level; ++i)
			printf("  ");
		Left->Print(level);
	}

}

bool Tree::ExGlobal(TypeLex id)
{
	Tree* i = Tree::GetCur()->FindUp(id);

	return i != nullptr;
}

bool Tree::ExLocal(TypeLex id)
{
	Tree* i = Tree::GetCur()->FindUpOneLevel(this, id);

	return i->n.DataType != EMPTY; //DataType у root -1, если дойдет до root то -1!=-1 то вернет false
}

//семантики
void Tree::UseNoExistVar(TypeLex id)//использование несущ. переменннной
{
	if (!ExGlobal(id))
		sc->PrintError("СЕМАНТИКА: нет переменной", id);
}

void Tree::TwiceVarInit(TypeLex id)
{
	if (ExLocal(id))
		sc->PrintError("СЕМАНТИКА: такая переменнная уже есть: ", id);
}
void Tree::TwiceFunInit(TypeLex id)
{
	Tree* i = Tree::GetCur()->FindUp(this,id);
	if (i!=NULL && i->GetNode().DataType == DATA_TYPE::TYPE_FUNCT)
		sc->PrintError("СЕМАНТИКА: такая переменнная уже есть: ", id);
}

Tree* Tree::GetRight() {
	return Right;
}
Tree* Tree::GetLeft() {
	return Left;
}
