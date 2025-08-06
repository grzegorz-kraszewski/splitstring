//==============
// IFFChunkTool
//==============

#include <proto/dos.h>

#include "main.h"
#include "locale.h"
#include "callargs.h"

//=============================================================================
// CallArgs::Problem()
//=============================================================================

bool CallArgs::Problem()
{
	Printf("CallArgs::Problem %ld\n", IoErr());
	#warning Improve error reporting.
}

//=============================================================================
// CallArgs::CallArgs()
//=============================================================================

CallArgs::CallArgs() : ready(FALSE)
{
	for (int16 i = NUM_ARGS - 1; i >= 0; i--) vals[i] = 0;

	if (args = ReadArgs("STRING,SEPARATOR=SEP/K,INDEX/K/N", vals, NULL))
	{
		ready = TRUE;
	}
	else Problem();
}

//=============================================================================
// CallArgs::~CallArgs()
//=============================================================================

CallArgs::~CallArgs()
{
	if (args) FreeArgs(args);
}
