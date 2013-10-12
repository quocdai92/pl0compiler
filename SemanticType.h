#ifndef S_T

#include <string>
#include <string.h>
using namespace std;

#define MAXITEM 20
enum SemanticType
{
	Constant,
	SubProc,
	Variable,
	Parameter,
	Array,
	None
};

struct ItemSym
{
	string Name;
	SemanticType Property;
	//int Size;
};

struct ItemTable
{
	ItemSym *ListItem[MAXITEM];
	int Tx;
	//int Size;
	ItemTable *PtrParent;
	ItemTable *PtrSubproc;
};

#endif
