#ifndef __SEMAN
#define __SEMAN
#include "defs.h"
#include "scaner.h"
#define EMPTY (DATA_TYPE)-1
#include <string>

enum DATA_TYPE {
	TYPE_UNKNOWN = 1, TYPE_INTEGER,
	TYPE_CHAR, TYPE_FUNCT, TYPE_FOR
};
struct Node
{
	TypeLex id;
	DATA_TYPE DataType;
	int Param;
	bool FuncFlag;

	Node(const TypeLex lex_lutor, DATA_TYPE _DataType, int _Param, bool _FuncFlag)
	{
		memcpy(this->id, lex_lutor, strlen(lex_lutor) + 1);
		this->DataType = _DataType;
		this->Param = _Param;
		this->FuncFlag = _FuncFlag;
	}

	Node()
	{
		char lex[] = "-1";
		memcpy(this->id, lex, sizeof(char)*2);
		this->id[1] = '\0';

		//std::string t = "0\0";
		//TypeLex _l = 0;
		//strcpy(this->id, t.c_str());
		this->DataType = EMPTY;
		this->Param = 0;
		this->FuncFlag = false;
	}
	Node(const Node& node)
	{
		memcpy(this->id, node.id, strlen(node.id));
		this->id[strlen(node.id)] = '\0';

		this->DataType = node.DataType;
		this->Param = node.Param;
		this->FuncFlag = node.FuncFlag;
	}

};

class Tree {
private:
	Node n;
	Tree * Up, *Left, *Right;
	TScaner *sc;
	static Tree* Cur;

public:
	Tree(Tree * l, Tree * r, Tree * u, Node Data, TScaner * sc);
	Tree();
	~Tree();

	Tree * SetLeft(Node Data);
	Tree * SetRight(Node Data);
	Tree * FindUp(Tree * From, TypeLex id);
	Tree * FindUpOneLevel(Tree * From, TypeLex id);
	void Print(int level);
	bool ExGlobal(TypeLex id);
	bool ExLocal(TypeLex id);
	void UseNoExistVar(TypeLex id);
	void TwiceVarInit(TypeLex id);
	void TwiceFunInit(TypeLex id);
	Tree * GetRight();
	Tree * GetLeft();
	Tree* FindUp(TypeLex id);
	Node& GetNode() {
		return n;
	}
	

	static void SetCur(Tree * a);
	static Tree * GetCur();
	Tree * SemInclude(TypeLex a, DATA_TYPE t);
	void SemSetType(Tree *Addr, DATA_TYPE t);
	void SemSetParam(Tree *Addr, int n);
	void SemControlParam(Tree *Addr, int n);
	//Tree * SemGetType(TypeLex a);
	//Tree * SemGetFunct(TypeLex a);
	int DupControl(TypeLex a);

};

#endif