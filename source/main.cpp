#include <proto/exec.h>
#include <workbench/startup.h>

#include <proto/dos.h>

#include "main.h"
#include "callargs.h"

#define APP_BUFSIZE              1024
#define ERROR_NO_INPUT_DATA       784

int32 StrLen(const char *s)
{
	const char *v = s;

	while (*v) v++;
	return (int32)(v - s);
}


class App
{
	CallArgs args;
	char *str;
	int32 stringLength;
	const char *separator;
	int32 index;
	char *buffer;
	void StripBufferEndOfLine();
	char* FindStringPartForward(int32 index);
	char* FindStringPartBackward(int32 index);

	public:

	App();
	bool Ready() { return args.ready && str; }
	char* ReadLine();
	int32 Run();
	bool Problem(int32 error);
	~App();
};


void App::StripBufferEndOfLine()
{
	char *lastCharPtr = &buffer[stringLength - 1];

	if (*lastCharPtr == 0x0A)
	{
		*lastCharPtr = 0x00;
		stringLength--;
	}
}

// Algorithm of FindStringForward()
// 1. Pointer 'start' is set to the start of string.
// 2. Current index 'i' is set 0.
// 3. Slice[0] starts at 'start'.
// 4. Search for separator. Set 'end' to the first character of separator, or string zero terminator if separator not found.
// 5. If 'i' == 'index' characters are printed from 'start' to 'end' excluding, then exit.
// 6. Increment 'i'. Go to 4.


char* App::FindStringPartForward(int32 index)
{
	return NULL;
}


char* App::FindStringPartBackward(int32 index)
{
	return NULL;
}


App::App() : str(NULL), separator(" "), index(0), buffer(NULL)
{
	if (args.Specified(ARG_STRING))
	{
		str = args[ARG_STRING];
		stringLength = StrLen(str);
	}
	else str = ReadLine();

	if (args.Specified(ARG_SEPARATOR)) separator = args[ARG_SEPARATOR];
	if (args.Specified(ARG_INDEX)) index = args(ARG_INDEX); 
}


App::~App()
{
	if (buffer) delete buffer;
}


int32 App::Run()
{
	int32 result = RETURN_OK;
	char *stringPart;

	if (index >= 0) stringPart = FindStringPartForward(index);
	else stringPart = FindStringPartBackward(-index - 1);

	if (stringPart) Printf("%s\n", stringPart);
	else result = RETURN_WARN;
	return result;
}


char* App::ReadLine()
{
	char *readResult;

	if (!(buffer = new char[APP_BUFSIZE])) return NULL;
	buffer[0] = 0x00;
	SetIoErr(0);
	readResult = FGets(Input(), buffer, APP_BUFSIZE);

	if (readResult)
	{
		stringLength = StrLen(buffer);
		StripBufferEndOfLine();
		return buffer;
	}
	else
	{
		int32 doserr = IoErr();
		if (doserr) Problem(doserr);
		else Problem(ERROR_NO_INPUT_DATA);
		return NULL;
	}
}


bool App::Problem(int32 error)
{
	#warning Improve error reporting.
	Printf("System error %ld\n", error);
}


int32 Main(WBStartup *wbmsg)
{
	int32 result = RETURN_OK;
	App app;

	if (app.Ready())
	{
		result = app.Run();
		Printf("app.Run() completed with result %ld\n", result);
	}
	else result = RETURN_ERROR;

	return result;
}
