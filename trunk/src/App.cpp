#include "InDE.h"


//////////////////////////////////////////////////
// Message map

FXDEFMAP(App) AppMap[] = {
	FXMAPFUNC(SEL_SIGNAL,	App::ID_CLOSEALL,	App::onCmdCloseAll),
	FXMAPFUNC(SEL_COMMAND,	App::ID_CLOSEALL,	App::onCmdCloseAll),
};


//////////////////////////////////////////////////
// Object implementation

FXIMPLEMENT(App, FXApp, AppMap, ARRAYNUMBER(AppMap))


//////////////////////////////////////////////////
// Constructor

App::App(const FXString& name)
:	FXApp(name)
{
#ifndef DEBUG
	addSignal(SIGINT, this, ID_CLOSEALL);
#ifndef WIN32
	addSignal(SIGQUIT, this, ID_CLOSEALL);
	addSignal(SIGHUP, this, ID_CLOSEALL);
	addSignal(SIGPIPE, this, ID_CLOSEALL);
#endif
#endif
	
	associations = new FXFileDict(this);
	syntaxParser = new SyntaxParser();
}



//////////////////////////////////////////////////
// Initialisation

void App::init(int argc, char** argv, FXbool connect)
{
	// Init and load registry
	FXApp::init(argc, argv, connect);
	
	// Load icon path
	associations->setIconPath(reg().readStringEntry("SETTINGS", "iconPath", FXIconDict::defaultIconPath));
	
	// Search syntax file
	FXString syntaxFile;
#ifndef WIN32
	syntaxFile = FXFile::search(FXFile::getHomeDirectory()+"/."+getAppName(), "syntax.stx");
#else
	syntaxFile = FXFile::search(FXFile::getHomeDirectory()+"\\"+getAppName(), "syntax.stx");
#endif
	if (syntaxFile.empty())
	{
#ifndef WIN32
		syntaxFile = FXFile::search("/usr/share/"+getAppName(), "syntax.stx");
		if (syntaxFile.empty())
		{
			syntaxFile = FXFile::search("/usr/local/share/"+getAppName(), "syntax.stx");
		}
#endif
	}
	
	if (!syntaxFile.empty())
	{
		loadSyntaxFile(syntaxFile);
	}
	FXTRACE((1, "Application initialized.\n"));
}


//////////////////////////////////////////////////
// Exit application

void App::exit(FXint code)
{
	// Write registry and quit
	FXApp::exit(code);
}


//////////////////////////////////////////////////
// Close all windows

long App::onCmdCloseAll(FXObject*, FXSelector, void*)
{
	while (windows.no() > 0 && windows[0]->close(true));
	return 1;
}


//////////////////////////////////////////////////
// Application destructor

App::~App()
{
	for (int i = 0; i < syntaxes.no(); i++)
	{
		delete syntaxes[i];
	}
	
	FXASSERT(windows.no() == 0);
}


//////////////////////////////////////////////////
// Load syntax file

FXbool App::loadSyntaxFile(const FXString& file)
{
	syntaxParser->setFile(file);
	return syntaxParser->parse(syntaxes);
}
