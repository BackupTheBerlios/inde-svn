#ifndef APP_H
#define APP_H

#include "InDE.h"


//////////////////////////////////////////////////
// Application main class

class App : public FXApp
{
	FXDECLARE(App)
	friend class MainWindow;
	
	protected:
		MainWindowList	windows;					// Window list
		FXFileDict*		associations;				// File association table
		FXSyntaxList	syntaxes;					// List of syntax patterns
		SyntaxParser*	syntaxParser;				// Parser for syntax file
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
		
		// Construct application object
		App(const FXString& name);
		
		// Initialize application
		virtual void init(int argc, char** argv, FXbool connect=true);
		
		// Exit application
		virtual void exit(FXint status=0);
		
		// Delete application object
		virtual ~App();
		
		// Load syntax file
		FXbool loadSyntaxFile(const FXString& file);
};

#endif
