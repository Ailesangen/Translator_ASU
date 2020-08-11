//описание лексем
#ifndef __DEFS
#define __DEFS


#define MaxText 100000
#define MaxLex	100
#define MaxKey 5

#define TIdent 1

#define TConstInt10   10
#define TConstInt8   11
#define TConstChar   12

#define TInt   20
#define TChar   21
#define TFor   22
#define TVoid   23
#define TMain   24

#define TAssign   50
#define TEqual   51
#define TNotEqual   52
#define TLess   53
#define TMore   54
#define TME   55
#define TLE   56
#define TPlus   57
#define TMinus   58
#define TMult   59
#define TDiv   60
#define TMod   61


#define TZpt   101
#define TTZ   102
#define TOBrace   103
#define TCBrace   104
#define TOCurly   105
#define TCCurly   106


#define TEnd   800
#define TError 900
typedef char TypeLex[MaxLex];


#endif