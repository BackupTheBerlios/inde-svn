#ifndef APP_H
#define APP_H

#include <fx.h>
#include <FXArray.h>
#include <signal.h>
#include "SyntaxParser.h"
#include "MainWindow.h"

class MainWindow;

typedef FXObjectListOf<MainWindow> MainWindowList;

class App : public FXApp
{
	FXDECLARE(App)
	
	protected:
		MainWindowList	windows;
		FXSyntaxList	syntaxes;
		FXFileDict*		assocs;
		SyntaxParser*	syntaxParser;
	
	private:
		App(){};
		App(const App&);
		App& operator=(const App&);
		
	public:
		enum {
			ID_CLOSEALL = FXApp::ID_LAST,
			ID_LAST,
		};
		
	public:
		long onCmdCloseAll(FXObject*, FXSelector, void*);
		
	public:
		App(const FXString& appKey);
		virtual void init(int argc, char** argv, FXbool connect=true);
		virtual void exit(FXint status=0);
		virtual ~App();
		FXbool loadSyntaxFile(const FXString& file);
		
};

#endif // APP_H
