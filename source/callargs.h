//=======================================
// Commandline arguments for SplitString
//=======================================

#include <dos/rdargs.h>

#include "main.h"

#define ARG_STRING     0
#define ARG_SEPARATOR  1
#define ARG_INDEX      2

#define NUM_ARGS       3


class CallArgs
{
	int32 vals[NUM_ARGS];
	RDArgs *args;
	bool Problem();

	public:

	bool ready;
	CallArgs();
	~CallArgs();
	bool Specified(int32 index) const { return vals[index] != NULL; }
	const char* operator[](int32 index) const { return (const char*)vals[index]; }
	int32 operator()(int32 index) const { return *(int32*)vals[index]; }
};
