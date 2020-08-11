#ifndef __SCANER
#define __SCANER
//#include "defs.h"

class TScaner{
private:
	char* t;
	int uk;
public:
	void PutUK(int i);
	int GetUK(void);
	void PrintError(const char *,const char *);
	int Scaner(TypeLex l);
	void GetData(const char *);
	TScaner(const char *);
	~TScaner();
};

#endif