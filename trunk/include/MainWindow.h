#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fx.h>
#include "InDE.h"
#include "Settings.h"
#include "FileBrowser.h"
#include "TabEditor.h"

class InDE;
class FileBrowser;
class TabEditor;

/*
	Class: MainWindow

	Main application window
*/
class MainWindow : public FXMainWindow
{
	FXDECLARE(MainWindow)

	protected:
		MainWindow() {};
		MainWindow(const MainWindow&);
		MainWindow& operator=(const MainWindow&);

	public:
		/*
			Variable: settings

			Application-wide settings (<Settings>)
		*/
		Settings*						settings;

	private:
		FXObjectListOf<FXString>*		projects;
		FXSettings*						projectSettings;

		FXDockSite*						topDock;
		FXDockSite*						leftDock;
		FXDockSite*						rightDock;
		FXDockSite*						bottomDock;

		FXToolBarShell*					menuDragShell;
		FXMenuBar*						menuBar;
		FXMenuPane*						fileMenu;
		FXMenuPane*						editMenu;
		FXMenuPane*						projectMenu;
		FXMenuPane*						viewMenu;
		FXMenuPane*						optionMenu;
		FXMenuPane*						helpMenu;
		FXMenuPane*						newMenu;
		FXMenuPane*						highlightMenu;

		FXStatusBar*					statusBar;
		FXTabBook*						browserFrame;
		FileBrowser*					fileBrowser;
		FXComboBox*						fileFilter;
		FXDirList*						projectBrowser;
		FXComboBox*						projectFilter;

		TabEditor*						editor;

	public:
		enum {
			ID_QUIT = FXMainWindow::ID_LAST,

			// File commands
			ID_NEW_FILE,
			ID_NEW_CLASS,
			ID_OPEN_FILE,
			ID_SAVE_FILE,
			ID_SAVE_FILE_AS,
			ID_SAVE_FILES,
			ID_CLOSE_FILE,
			ID_CLOSE_FILES,

			// Edit commands
			ID_UNDO,
			ID_REDO,
			ID_COPY,
			ID_CUT,
			ID_PASTE,
			ID_DELETE,
			ID_SEARCH,
			ID_SEARCH_REPLACE,
			ID_GOTO,
			ID_SHIFT_LEFT,
			ID_SHIFT_RIGHT,

			// Project commands
			ID_NEW_PROJECT,
			ID_OPEN_PROJECT,
			ID_CLOSE_PROJECT,
			ID_CLOSE_PROJECTS,
			ID_PROJECT_SETTINGS,

			// Option commands
			ID_SETTINGS,
			ID_RESET_SETTINGS,

			ID_LAST,
		};

	public:
		long onQuit(FXObject*, FXSelector, void*);
		long onFileCmd(FXObject*, FXSelector, void*);
		long onEditCmd(FXObject*, FXSelector, void*);
		long onProjectCmd(FXObject*, FXSelector, void*);
		long onOptionCmd(FXObject*, FXSelector, void*);

	public:

		/*
			Constructor: MainWindow


		*/
		MainWindow(InDE* app, const FXString& title);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~MainWindow
		*/
		virtual ~MainWindow();

		/*
			Function: getApp
			
			Returns:
				The application object
		*/
		InDE* getApp() { return (InDE*)FXMainWindow::getApp(); }

	public:

		/*
			Function: editSettings
			
			Opens a dialog (<SettingsDialog>) where the user can edit
			the application-wide settings
		*/
		void editSettings();

		/*
			Function: readSettings
			
			Reads settings from settings file
		*/
		void readSettings();

		/*
			Function: resetSettings
			
			Resets InDE settings to defaults
		*/
		void resetSettings();

		/*
			Functon: applySettings
			
			Applies settings to all widgets which make use of them
		*/
		void applySettings();

		/*
			Function: getEditor
			
			Returns a pointer to the tabbed editor widget
		*/
		TabEditor* getEditor() { return editor; }

	private:

		void buildMenu();

		void buildContent();
};

#endif // MAINWINDOW_H
