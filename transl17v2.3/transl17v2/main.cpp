#pragma once
#include"defs.h"
#include"scaner.h"
#include"syntax.h"
#include<iostream>
//#include<Windows.h>
#include <fstream>
#include<Windows.h>
using namespace std;



int main()
{
	setlocale(LC_ALL, "rus");
	TScaner* sc;
	Cyntax* cs;
	int type;
	TypeLex l;

	sc = new TScaner("aa.txt");
	cs = new Cyntax(sc);
	cs->Program();
	//	sc = new TScaner("F:\trans2\trans2\file.txt");
	//type = sc->Scaner(l);
	/*do
	{
		type = sc->Scaner(l);
		printf("%s - тип %d \n", l, type);
	} while (type != TEnd);*/
	cs->GetTree()->Print(0);
	getchar();
	return 0;
}
