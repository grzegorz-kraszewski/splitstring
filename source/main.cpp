#include <proto/exec.h>
#include <workbench/startup.h>

#include <proto/dos.h>

#include "main.h"
#include "callargs.h"

class App
{
	CallArgs args;
	char *str;
	const char *separator;
	int32 index;

	public:

	App();
	bool Ready() { return args.ready; }
	int32 Run();
	~App();
};


App::App() : str(NULL), separator(" "), index(0)
{

}


App::~App()
{

}


int32 App::Run()
{
	return RETURN_OK;
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
