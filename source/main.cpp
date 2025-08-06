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
	const char *separator;
	int32 index;
	char *buffer;

	public:

	App();
	bool Ready() { return args.ready && str; }
	char* ReadLine();
	int32 Run();
	bool Problem(int32 error);
	~App();
};


App::App() : str(NULL), separator(" "), index(0), buffer(NULL)
{
	if (args.Specified(ARG_STRING)) str = args[ARG_STRING];
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
	Printf("%s#\n", str);
	return RETURN_OK;
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
		int32 sl = StrLen(buffer);

		if ((sl == APP_BUFSIZE - 1) && (buffer[APP_BUFSIZE - 2] != 0x0A))
		{
			Problem(ERROR_LINE_TOO_LONG);
			return NULL;
		}
		else
		{
			// strip possible LF at end

			if (buffer[sl - 1] == 0x0A) buffer[sl - 1] = 0x00;
			return buffer;
		}
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
	Printf("System error %ld\n", error);
}


int32 Main(WBStartup *wbmsg)
{
	int32 result = RETURN_OK;
	App app;

	if (app.Ready())
	{
		result = app.Run();
		// Printf("app.Run() completed with result %ld\n", result);
	}
	else result = RETURN_ERROR;

	return result;
}
