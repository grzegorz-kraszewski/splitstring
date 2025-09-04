/*-------------------------------------*/
/* Minimal C++ startup for AmigaOS 3.x */
/* RastPort, 2025                      */
/*-------------------------------------*/

#include <proto/exec.h>
#include <proto/dos.h>

#include <exec/types.h>
#include <workbench/startup.h>

#include "main.h"

Library *SysBase;
Library *DOSBase;

extern int32 Main(WBStartup *wbmsg);

extern void (*__CTOR_LIST__[])(void);
extern void (*__DTOR_LIST__[])(void);
void Globals(void (**ptr)());


__attribute__((saveds)) int32 Start(void)
{
	Process *myproc = NULL;
	WBStartup *wbmsg = NULL;
	bool have_shell = FALSE;
	int32 result = RETURN_OK;

	SysBase = *(Library**)4L;
	myproc = (Process*)FindTask(NULL);

	if (myproc->pr_CLI) have_shell = TRUE;

	if (!have_shell)
	{
		WaitPort(&myproc->pr_MsgPort);
		wbmsg = (WBStartup*)GetMsg(&myproc->pr_MsgPort);
	}

	result = RETURN_FAIL;

	if (DOSBase = OpenLibrary("dos.library", 39))
	{
		Globals(&__CTOR_LIST__[1]);
		result = Main(wbmsg);
		Globals(&__DTOR_LIST__[1]);
		CloseLibrary(DOSBase);
	}

	if (wbmsg)
	{
		Forbid();
		ReplyMsg(&wbmsg->sm_Message);
	}

	return result;
}


__attribute__((section(".text"))) UBYTE VString[] = "$VER: SplitString 0.1 (05.08.2025)\r\n";


void* operator new(uint32 size) throw()
{
	APTR p = AllocVec(size, MEMF_ANY);
	return p;
}


void* operator new[](uint32 size)
{
	return operator new(size);
}


void operator delete(void* memory)
{
	FreeVec(memory);
}


void operator delete[](void* memory)
{
	operator delete(memory);
}


void Globals(void (**ptr)())
{
	while (*ptr) (*ptr++)();
}
