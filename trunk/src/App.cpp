#include "App.h"

FXDEFMAP(App) AppMap[] = {
	FXMAPFUNC(SEL_SIGNAL,	App::ID_CLOSEALL,	App::onCmdCloseAll),
	FXMAPFUNC(SEL_COMMAND,	App::ID_CLOSEALL,	App::onCmdCloseAll),
};

FXIMPLEMENT(App, FXApp, AppMap, ARRAYNUMBER(AppMap))


App::App(const FXString& appKey)
:	FXApp(appKey)
{
#ifndef DEBUG
	addSignal(SIGINT, this, ID_CLOSEALL);
	addSignal(SIGQUIT, this, ID_CLOSEALL);
	addSignal(SIGHUP, this, ID_CLOSEALL);
	addSignal(SIGPIPE, this, ID_CLOSEALL);
#endif
	assocs = new FXFileDict(this);
	syntaxParser = new SyntaxParser();
}


void App::init(int argc, char** argv, FXbool connect)
{
	FXApp::init(argc, argv, connect);
	
	assocs->setIconPath(reg().readStringEntry("Settings", "iconPath", FXIconDict::defaultIconPath));
	
	// Syntax file to load
	FXString file;
	
	// Paths to search after syntax file
	FXArray<FXString> paths;
	
	// Most important: Users home directory
	paths.append(FXFile::getHomeDirectory() + "/." + getAppName());
	
	// Shared directory in /usr
	paths.append("/usr/share/" + getAppName() + "/syntax");
	
	// Shared directory in /usr/local
	paths.append("/usr/local/share/" + getAppName() + "/syntax");
	
	for (FXuint i = 0; i < paths.no(); i++)
	{
		if (file.empty())
			file = FXFile::search(paths[i], "syntax.stx");
	}
	
	if (!file.empty())
	{
		loadSyntaxFile(file);
	}
}


void App::exit(FXint status)
{
	FXApp::exit(status);
}


App::~App()
{
	while (syntaxes.no())
	{
		delete syntaxes[0];
	}
	
	delete syntaxParser;
	
	FXASSERT(windows.no() == 0);
}


FXbool App::loadSyntaxFile(const FXString& file)
{
	syntaxParser->setFile(file);
	return syntaxParser->parse(syntaxes);
}


long App::onCmdCloseAll(FXObject*, FXSelector, void*)
{
	while (windows.no() > 0 && windows[0]->close(true));
	return 1;
}
