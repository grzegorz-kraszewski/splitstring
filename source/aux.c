#include <proto/dos.h>

extern struct Library *DOSBase;

// The last resort function called when pure virtual method is attempted.

void __pure_virtual(void)
{
	PutStr("pure virtual\n");
}

// Default tables for global constructors and destructors.
// Used when there are no compiler generated ones.

void (*__CTOR_LIST__[2])() = { 0, 0 };
void (*__DTOR_LIST__[2])() = { 0, 0 };
