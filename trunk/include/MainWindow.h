#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fx.h>
#include <FXArray.h>
#include "Hilite.h"
#include "ProjectSettings.h"
#include "NewProjectWizard.h"
#include "InDESettings.h"
#include "SettingsDialog.h"
#include "App.h"

class App;

typedef FXArray<FXHiliteStyle> FXHiliteArray;

class MainWindow : public FXMainWindow
{
	FXDECLARE(MainWindow)

	protected:
		MainWindow() {};
		MainWindow(const MainWindow&);
		MainWindow& operator=(const MainWindow&);
		
	private:
		FXDockSite*			topDock;
		FXDockSite*			bottomDock;
		FXDockSite*			rightDock;
		FXDockSite*			leftDock;
		FXStatusBar*		statusBar;
		FXToolBarShell*		toolDragShell;
		FXToolBarShell*		menuDragShell;
		FXToolBar*			toolBar;
		FXMenuBar*			menuBar;
		FXMenuPane*			fileMenu;
		FXMenuPane*			editMenu;
		FXMenuPane*			projectMenu;
		FXMenuPane*			viewMenu;
		FXMenuPane*			preferencesMenu;
		FXMenuPane*			helpMenu;
		FXTabBook*			tabBrowser;
		FXDirList*			fileBrowser;
		FXComboBox*			fileFilter;
		FXDirList*			projectBrowser;
		FXComboBox*			projectFilter;
		FXTextField*		clock;
		
		FXbool				settingsDirty;
		FXbool				projectSettingsDirty;
		FXSyntax*			syntax;
		FXHiliteArray		styles;
		FXint				style;
		// TabEditor*			tabEditor;
		
	public:
		InDESettings		settings;
		ProjectSettings		projectSettings;
		FXString			projectConfigFile;
		
	public:
		enum {
			ID_SELF = FXMainWindow::ID_LAST,
			ID_FILE_NEW,
			ID_QUIT,
			ID_NEWPROJECT,
			
			ID_LOADSETTINGS,
			ID_WRITESETTINGS,
			ID_EDITSETTINGS,
			
			ID_SETTING_BASEDIR,
			ID_SETTING_NUMRECENTPROJECTS,
			ID_SETTING_NUMRECENTFILES,
			ID_SETTING_AUTOLOADLASTPROJECT,
			ID_SETTING_SAVEONTABSWITCH,
			ID_SETTING_AUTOSAVE,
			ID_SETTING_AUTOSAVEINTERVAL,
			ID_SETTING_BACKUPONSAVE,
			ID_SETTING_BACKUPSUFFIX,
			
			ID_PROJECT_NEW,
			ID_PROJECT_CLOSE,
			ID_PROJECT_OPEN,
			ID_PROJECT_WRITECONFIG,
			ID_PROJECT_LOADCONFIG,
			ID_PROJECT_EDITCONFIG,
			
			ID_PROJECT_TYPE,
			ID_PROJECT_NAME,
			ID_PROJECT_DESCRIPTION,
			ID_PROJECT_TARGET,
			ID_PROJECT_VERSION,
			ID_PROJECT_SRCDIR,
			ID_PROJECT_INCLUDEDIR,
			ID_PROJECT_BUILDDIR,
			ID_PROJECT_INCLUDEPATHS,
			ID_PROJECT_LIBRARYPATHS,
			ID_PROJECT_LIBRARIES,
			ID_PROJECT_DEBUG,
			ID_PROJECT_PIC,
			ID_PROJECT_WARNINGS,
			ID_PROJECT_DEFINES,
			ID_PROJECT_SWITCHES,
			ID_PROJECT_AUTHOR,
			ID_PROJECT_LICENSE,
			ID_PROJECT_LICENSEHEADER,
			
			ID_ABOUT,
			ID_LAST,
		};
	
	public:
		long onCmdQuit(FXObject*, FXSelector, void*);
		
		long onCmdNewFile(FXObject*, FXSelector, void*);
		long onCmdDeleteFile(FXObject*, FXSelector, void*);
		
		long onCmdWriteSettings(FXObject*, FXSelector, void*);
		long onCmdLoadSettings(FXObject*, FXSelector, void*);
		long onCmdEditSettings(FXObject*, FXSelector, void*);

		long onCmdNewProject(FXObject*, FXSelector, void*);
		long onCmdDeleteProject(FXObject*, FXSelector, void*);
		long onCmdCloseProject(FXObject*, FXSelector, void*);
		long onCmdOpenProject(FXObject*, FXSelector, void*);

		long onCmdProjectWriteConfig(FXObject*, FXSelector, void*);
		long onCmdProjectLoadConfig(FXObject*, FXSelector, void*);
		long onCmdProjectEditConfig(FXObject*, FXSelector, void*);
		
		long onCmdSettingBaseDir(FXObject*, FXSelector, void*);
		long onUpdSettingBaseDir(FXObject*, FXSelector, void*);
		long onCmdSettingNumRecentProjects(FXObject*, FXSelector, void*);
		long onUpdSettingNumRecentProjects(FXObject*, FXSelector, void*);
		long onCmdSettingNumRecentFiles(FXObject*, FXSelector, void*);
		long onUpdSettingNumRecentFiles(FXObject*, FXSelector, void*);
		long onCmdSettingAutoLoadLastProject(FXObject*, FXSelector, void*);
		long onUpdSettingAutoLoadLastProject(FXObject*, FXSelector, void*);
		long onCmdSettingSaveOnTabSwitch(FXObject*, FXSelector, void*);
		long onUpdSettingSaveOnTabSwitch(FXObject*, FXSelector, void*);
		long onCmdSettingAutosave(FXObject*, FXSelector, void*);
		long onUpdSettingAutosave(FXObject*, FXSelector, void*);
		long onCmdSettingAutosaveInterval(FXObject*, FXSelector, void*);
		long onUpdSettingAutosaveInterval(FXObject*, FXSelector, void*);
		long onCmdSettingBackupOnSave(FXObject*, FXSelector, void*);
		long onUpdSettingBackupOnSave(FXObject*, FXSelector, void*);
		long onCmdSettingBackupSuffix(FXObject*, FXSelector, void*);
		long onUpdSettingBackupSuffix(FXObject*, FXSelector, void*);

		long onCmdProjectType(FXObject*, FXSelector, void*);
		long onUpdProjectType(FXObject*, FXSelector, void*);
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
		long onCmdProjectBuildDir(FXObject*, FXSelector, void*);
		long onUpdProjectBuildDir(FXObject*, FXSelector, void*);
		long onCmdProjectIncludePaths(FXObject*, FXSelector, void*);
		long onUpdProjectIncludePaths(FXObject*, FXSelector, void*);
		long onCmdProjectLibraryPaths(FXObject*, FXSelector, void*);
		long onUpdProjectLibraryPaths(FXObject*, FXSelector, void*);
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
		long onCmdProjectAuthor(FXObject*, FXSelector, void*);
		long onUpdProjectAuthor(FXObject*, FXSelector, void*);
		long onCmdProjectLicense(FXObject*, FXSelector, void*);
		long onUpdProjectLicense(FXObject*, FXSelector, void*);
		long onCmdProjectLicenseHeader(FXObject*, FXSelector, void*);
		long onUpdProjectLicenseHeader(FXObject*, FXSelector, void*);
		
	public:
	
		MainWindow(App* a, const FXString& title);
		
		virtual void create();
		
		virtual ~MainWindow();
		
		InDESettings* getSettings();		
		
		FXbool openProject(const FXString& location);
		
};

#endif // MAINWINDOW_H
