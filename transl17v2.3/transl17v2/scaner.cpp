#include"defs.h"
#include"scaner.h"
#include<string>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
//#define _CRT_SECURE_NO_WARNINGS

using namespace std;
TScaner :: TScaner(const char* FileName) {
	GetData(FileName);
	PutUK(0);
}
TypeLex Keyword[MaxKey]={"char","int","for","void","main"};
int IndexKeyword[MaxKey]={TChar,TInt,TFor,TVoid,TMain};

void TScaner ::PutUK(int i) {uk=i;}

int TScaner ::GetUK(){return uk;}

void TScaner ::PrintError(const char * err,const char *a) {
	for (int i = 0; i < uk; i++)
	{
		printf("%c", t[i]);
	}

	if (a[0] == '\0')
		//print("Ошибка : %s %s\n",err,a);
		cout << "Ошибка : " << err << " " << a << endl;
	else
		//printf("Ошибка : %s. Неверный символ %s\n",err,a);
		cout << "Ошибка : " << err << ". " << "Неверный символ " << a << endl;
	getchar();
	exit(0);
	
}
int TScaner ::Scaner(TypeLex l) 
{
	int i;
	for(i=0;i<MaxLex;i++)
		l[i]=0;
	i=0;
	while (t[uk]==' ' || t[uk]=='\t' || t[uk]=='\n' || t[uk]=='/' && t[uk+1]=='/')
	{	
		if(t[uk]!='/')
			uk++;			
		else
			while(t[uk]!='\n') 
				uk++;
	}
	if(t[uk]=='\0') {
		l[0]='#';
		return TEnd;			
	}

		//check for TIdent
		if((t[uk]>='a')&&(t[uk]<='z') || (t[uk]>='A')&&(t[uk]<='Z')) {
			l[i++]=t[uk++];
			while((t[uk]<='9')&&(t[uk]>='0') ||
				(t[uk]>='a')&&(t[uk]<='z') ||
				(t[uk]>='A')&&(t[uk]<='Z'))
				if(i<MaxLex-1) l[i++]=t[uk++];
				else uk++;
				//check for keyWord
				int j;
				for(j=0;j<MaxKey;j++)
					if(strcmp(l,Keyword[j])==0) return IndexKeyword[j];
					return TIdent;
		}
		//TConstChar
		else if(t[uk]=='\'') 
		{ 	
			uk++;				
			if(t[uk+1]=='\'')
				{
					l[i]=t[uk]; 
					return TConstChar; }
			else
			{
				l[i]=t[uk];
				PrintError("Неверное окончание символьной константы",l);
				return TError;
			}
		}
		//TConstInt8
		else if(t[uk]=='0') 
		{	
			while(t[uk]>='0' && t[uk]<='7') {
				if(i<MaxLex-1) l[i++]=t[uk++]; else uk++;
			}	
			return TConstInt8;
		}
		else if ((t[uk] >'0') && (t[uk] <='9'))
		{
			l[i++] = t[uk++];
			while ((t[uk] >= '0') && (t[uk] <= '9')) {
				if (i<MaxLex - 1) l[i++] = t[uk++]; else uk++;
			}
			return TConstInt10;
		}
			
		else if(t[uk]==',') 
		{
			l[i++]=t[uk++]; return TZpt;
		}
		else if(t[uk]==';') 
		{
			l[i++]=t[uk++]; return TTZ;
		}
		else if(t[uk]=='(') 
		{
			l[i++]=t[uk++]; return TOBrace;
		}
		else if(t[uk]==')') 
		{
			l[i++]=t[uk++]; return TCBrace;
		}
		else if(t[uk]=='{') 
		{
			l[i++]=t[uk++]; return TOCurly;
		}
		else if(t[uk]=='}') 
		{
			l[i++]=t[uk++]; return TCCurly;
		}
		else if(t[uk]=='{') 
		{
			l[i++]=t[uk++]; return TOCurly;
		}
		else if(t[uk]=='+') 
		{
			l[i++]=t[uk++]; return TPlus;
		}
		else if(t[uk]=='-') 
		{
			l[i++]=t[uk++]; return TMinus;
		}
		else if(t[uk]=='*') 
		{
			l[i++]=t[uk++]; return TMult;
		}
		else if(t[uk]=='/') 
		{
			l[i++]=t[uk++]; return TDiv;
		}
		else if(t[uk]=='%') 
		{
			l[i++]=t[uk++]; return TMod;
		}
		else if(t[uk]=='<') 
		{
			l[i++]=t[uk++];
			if(t[uk]=='=') {l[i++]=t[uk++]; return TLE; } //less equal
			return TLess;
		}
		else if(t[uk]=='>') 
		{
				l[i++]=t[uk++];
				if(t[uk]=='=') {l[i++]=t[uk++]; return TME; }
				return TMore;
		}
		else if(t[uk]=='!') 
		{
			l[i++]=t[uk++];
			if(t[uk]=='=') 
			{
				l[i++]=t[uk++]; return TNotEqual; 
			}
			else {PrintError("Неверный символ",l);} //нет символа !
			return TError;
		}
		else if(t[uk]=='=') 
		{
			l[i++]=t[uk++];
			if(t[uk]=='=') 
			{
				l[i++]=t[uk++]; return TEqual; 
			}
			else return TAssign;
		}
		else 
		{
			PrintError("Неверный символ",l);
			uk++;
			return TError;
		}					
}

void TScaner ::GetData(const char* FileName) {
	char aa;

	FILE* in = fopen(FileName, "r");
		
	t = new char(MaxText);
	if(in==NULL) {
		PrintError("Отсутствует входной файл",""); exit(1);
	}
	int i=0;
	while(!feof(in)) {
		fscanf_s(in,"%c",&aa);
		if(!feof(in)) t[i++]=aa;
		if(i>=MaxText-1) {
			PrintError("Большой файл","");
			break;
		}
	}
	t[i]='\0';
	fclose(in);
}
TScaner ::~TScaner() {
	if(t!=NULL) {
		delete(t);
	}
}
