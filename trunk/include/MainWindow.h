#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "InDE.h"


/////////////////////////////////////////////////
// FXHiliteArray

typedef FXArray<FXHiliteStyle> FXHiliteArray;


//////////////////////////////////////////////////
// Main window class

class MainWindow : public FXMainWindow
{
	FXDECLARE(MainWindow)

	protected:

		MainWindow() {};
		MainWindow(const MainWindow&);
		MainWindow& operator=(const MainWindow&);

	private:
	
		// Widgets
		FXDockSite*				topDock;
		FXDockSite*				bottomDock;
		FXDockSite*				leftDock;
		FXDockSite*				rightDock;
		FXStatusBar*			statusBar;
		FXToolBarShell*			toolBarDragShell;
		FXToolBar*				toolBar;
		FXToolBarShell*			menuBarDragShell;
		FXMenuBar*				menuBar;
		FXMenuPane*				fileMenu;
		FXMenuPane*				editMenu;
		FXMenuPane*				projectMenu;
		FXMenuPane*				viewMenu;
		FXMenuPane*				preferencesMenu;
		FXMenuPane*				helpMenu;
		FXTabBook*				browser;
		FXComboBox*				filesystemFilter;
		FXComboBox*				projectFilter;
		FXDirList*				filesystemBrowser;
		FXDirList*				projectBrowser;
		FXTextField*			clock;
		
		// Settings
		InDESettings			settings;
		ProjectSettings			projectSettings;
		FXbool					projectSettingsDirty;
		
		// Syntax
		FXSyntax*				syntax;
		FXHiliteArray			styles;
		FXint					style;
		
		// Misc
		FXUndoList				undoList;
		
	public:
	
		enum {
			ID_SELF = FXMainWindow::ID_LAST,
			ID_NEW,
			ID_QUIT,
			ID_BROWSER,
			ID_FILESYSTEMBROWSER,
			ID_PROJECTBROWSER,
			ID_FILESYSTEMFILTER,
			ID_PROJECTFILTER,
			ID_NEWPROJECT,
			ID_LOADSETTINGS,
			ID_SAVESETTINGS,
			ID_SETTINGS,
			ID_SETTINGS_BASEDIR,
			ID_SETTINGS_SAVEONTAB,
			ID_SETTINGS_AUTOSAVE,
			ID_SETTINGS_AUTOSAVE_INTERVAL,
			ID_PROJECT_NAME,
			ID_PROJECT_DESCRIPTION,
			ID_PROJECT_TARGET,
			ID_PROJECT_VERSION,
			ID_PROJECT_SRCDIR,
			ID_PROJECT_INCLUDEDIR,
			ID_PROJECT_BINDIR,
			ID_PROJECT_INCLUDEPATHES,
			ID_PROJECT_LIBRARYPATHES,
			ID_PROJECT_LIBRARIES,
			ID_PROJECT_DEBUG,
			ID_PROJECT_PIC,
			ID_PROJECT_WARNINGS,
			ID_PROJECT_DEFINES,
			ID_PROJECT_SWITCHES,
			ID_ABOUT,
			ID_LAST,
		};
	
	public:
	
		long onCmdQuit(FXObject*, FXSelector, void*);
		long onCmdNew(FXObject*, FXSelector, void*);
		long onCmdNewProject(FXObject*, FXSelector, void*);
		
		long onCmdSaveSettings(FXObject*, FXSelector, void*);
		long onCmdLoadSettings(FXObject*, FXSelector, void*);
		long onCmdSettings(FXObject*, FXSelector, void*);
		
		long onCmdSettingBaseDir(FXObject*, FXSelector, void*);
		long onUpdSettingBaseDir(FXObject*, FXSelector, void*);
		long onCmdSettingSaveOnTab(FXObject*, FXSelector, void*);
		long onUpdSettingSaveOnTab(FXObject*, FXSelector, void*);
		long onCmdSettingAutosave(FXObject*, FXSelector, void*);
		long onUpdSettingAutosave(FXObject*, FXSelector, void*);
		long onCmdSettingAutosaveInterval(FXObject*, FXSelector, void*);
		long onUpdSettingAutosaveInterval(FXObject*, FXSelector, void*);

		long onCmdProjectName(FXObject*, FXSelector, void*);
		long onUpdProjectName(FXObject*, FXSelector, void*);
		long onCmdProjectDescription(FXObject*, FXSelector, void*);
		long onUpdProjectDescription(FXObject*, FXSelector, void*);
		long onCmdProjectTarget(FXObject*, FXSelector, void*);
		long onUpdProjectTarget(FXObject*, FXSelector, void*);
		long onCmdProjectVersion(FXObject*, FXSelector, void*);
		long onUpdProjectVersion(FXObject*, FXSelector, void*);
		long onCmdProjectSrcDir(FXObject*, FXSelector, void*);
		long onUpdProjectSrcDir(FXObject*, FXSelector, void*);
		long onCmdProjectIncludeDir(FXObject*, FXSelector, void*);
		long onUpdProjectIncludeDir(FXObject*, FXSelector, void*);
		long onCmdProjectBinDir(FXObject*, FXSelector, void*);
		long onUpdProjectBinDir(FXObject*, FXSelector, void*);
		long onCmdProjectIncludePathes(FXObject*, FXSelector, void*);
		long onUpdProjectIncludePathes(FXObject*, FXSelector, void*);
		long onCmdProjectLibraryPathes(FXObject*, FXSelector, void*);
		long onUpdProjectLibraryPathes(FXObject*, FXSelector, void*);
		long onCmdProjectLibraries(FXObject*, FXSelector, void*);
		long onUpdProjectLibraries(FXObject*, FXSelector, void*);
		long onCmdProjectDebug(FXObject*, FXSelector, void*);
		long onUpdProjectDebug(FXObject*, FXSelector, void*);
		long onCmdProjectPic(FXObject*, FXSelector, void*);
		long onUpdProjectPic(FXObject*, FXSelector, void*);
		long onCmdProjectWarnings(FXObject*, FXSelector, void*);
		long onUpdProjectWarnings(FXObject*, FXSelector, void*);
		long onCmdProjectDefines(FXObject*, FXSelector, void*);
		long onUpdProjectDefines(FXObject*, FXSelector, void*);
		long onCmdProjectSwitches(FXObject*, FXSelector, void*);
		long onUpdProjectSwitches(FXObject*, FXSelector, void*);
	
	public:
	
		// Constructor
		MainWindow(FXApp*, const FXString&);
		
		// Create window object and show it
		virtual void create();
		
		// Destructor
		virtual ~MainWindow();
		
		// Load settings
		void loadSettings();
		
		// Save settings
		void saveSettings();
		
		// Get pointer to the settings struct
		InDESettings* getSettings();
		
};


//////////////////////////////////////////////////
// MainWindowList

typedef FXObjectListOf<MainWindow> MainWindowList;

#endif
