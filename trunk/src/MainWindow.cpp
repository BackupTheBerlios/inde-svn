#include "InDE.h"


//////////////////////////////////////////////////
// Message map


FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_CLOSE,		0,										MainWindow::onCmdQuit),
	FXMAPFUNC(SEL_SIGNAL,		MainWindow::ID_QUIT,					MainWindow::onCmdQuit),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_QUIT,					MainWindow::onCmdQuit),
	
	// File
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_NEW,						MainWindow::onCmdNew),
	
	// Project
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_NEWPROJECT,				MainWindow::onCmdNewProject),
	
	// Settings
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SAVESETTINGS,			MainWindow::onCmdSaveSettings),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_LOADSETTINGS,			MainWindow::onCmdLoadSettings),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTINGS,				MainWindow::onCmdSettings),

	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTINGS_BASEDIR,		MainWindow::onCmdSettingBaseDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTINGS_BASEDIR,		MainWindow::onUpdSettingBaseDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTINGS_SAVEONTAB,		MainWindow::onCmdSettingSaveOnTab),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTINGS_SAVEONTAB,		MainWindow::onUpdSettingSaveOnTab),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTINGS_AUTOSAVE,		MainWindow::onCmdSettingAutosave),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTINGS_AUTOSAVE,		MainWindow::onUpdSettingAutosave),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTINGS_AUTOSAVE_INTERVAL, MainWindow::onCmdSettingAutosaveInterval),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTINGS_AUTOSAVE_INTERVAL, MainWindow::onUpdSettingAutosaveInterval),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_NAME, MainWindow::onCmdProjectName),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_NAME, MainWindow::onUpdProjectName),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_DESCRIPTION, MainWindow::onCmdProjectDescription),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_DESCRIPTION, MainWindow::onUpdProjectDescription),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_TARGET, MainWindow::onCmdProjectTarget),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_TARGET, MainWindow::onUpdProjectTarget),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_VERSION, MainWindow::onCmdProjectVersion),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_VERSION, MainWindow::onUpdProjectVersion),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_SRCDIR, MainWindow::onCmdProjectSrcDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_SRCDIR, MainWindow::onUpdProjectSrcDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_INCLUDEDIR, MainWindow::onCmdProjectIncludeDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_INCLUDEDIR, MainWindow::onUpdProjectIncludeDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_BINDIR, MainWindow::onCmdProjectBinDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_BINDIR, MainWindow::onUpdProjectBinDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_INCLUDEPATHES, MainWindow::onCmdProjectIncludePathes),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_INCLUDEPATHES, MainWindow::onUpdProjectIncludePathes),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LIBRARYPATHES, MainWindow::onCmdProjectLibraryPathes),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_LIBRARYPATHES, MainWindow::onUpdProjectLibraryPathes),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LIBRARIES, MainWindow::onCmdProjectLibraries),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_LIBRARIES, MainWindow::onUpdProjectLibraries),

	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_DEBUG, MainWindow::onCmdProjectDebug),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_DEBUG, MainWindow::onUpdProjectDebug),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_PIC, MainWindow::onCmdProjectPic),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_PIC, MainWindow::onUpdProjectPic),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_WARNINGS, MainWindow::onCmdProjectWarnings),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_WARNINGS, MainWindow::onUpdProjectWarnings),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_DEFINES, MainWindow::onCmdProjectDefines),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_DEFINES, MainWindow::onUpdProjectDefines),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_SWITCHES, MainWindow::onCmdProjectSwitches),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_SWITCHES, MainWindow::onUpdProjectSwitches),
};


//////////////////////////////////////////////////
// Object implementation

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))


//////////////////////////////////////////////////
// Main window constructor

MainWindow::MainWindow(FXApp* a, const FXString& title)
:	FXMainWindow(a, title, NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{	
	// Status bar
	statusBar = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER|FRAME_RAISED);

	// Dock sites	
	topDock = new FXDockSite(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
	bottomDock = new FXDockSite(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);
	leftDock = new FXDockSite(this, LAYOUT_SIDE_LEFT|LAYOUT_FILL_Y);
	rightDock = new FXDockSite(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y);
	
	// Menu bar with drag shell
	menuBarDragShell = new FXToolBarShell(this, FRAME_NONE);
	menuBar = new FXMenuBar(topDock, menuBarDragShell, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_NONE);
	new FXToolBarGrip(menuBar, menuBar, FXMenuBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);
	
	// Tool bar with drag shell
	toolBarDragShell = new FXToolBarShell(this, FRAME_NONE);
	toolBar = new FXToolBar(topDock, toolBarDragShell, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_NONE);
	new FXToolBarGrip(toolBar, toolBar, FXToolBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);
	
	new FXHorizontalSeparator(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|SEPARATOR_GROOVE);
	
	// About button in status bar
	new FXButton(statusBar, _("\tAbout inDE\tAbout inDE C++ IDE"), NULL, this, ID_ABOUT, LAYOUT_FILL_Y|LAYOUT_RIGHT);

	// File menu	
	fileMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, _("File"), NULL, fileMenu);
	
	// Edit menu
	editMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, _("Edit"), NULL, editMenu);
	
	// Project menu
	projectMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, _("Project"), NULL, projectMenu);
	
	// View menu
	viewMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, _("View"), NULL, viewMenu);
	
	// Preferences menu
	preferencesMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, _("Preferences"), NULL, preferencesMenu);
	
	// Help menu
	helpMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, _("Help"), NULL, helpMenu);
	
	// Menu commands
	new FXMenuCommand(fileMenu, _("New File\tCtrl+N"), NULL, this, ID_NEW);
	new FXMenuCommand(fileMenu, _("Quit\tCtrl+Q\tHallo"), NULL, this, ID_QUIT);
	new FXMenuCommand(projectMenu, _("Create new Project"), NULL, this, ID_NEWPROJECT);
	new FXMenuCommand(preferencesMenu, _("InDE settings"), NULL, this, ID_SETTINGS);
	
	// Splitter
	FXSplitter* splitter = new FXSplitter(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y|SPLITTER_TRACKING);
	FXVerticalFrame* browserFrame = new FXVerticalFrame(splitter, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	// Filesystem/Project tab book
	browser = new FXTabBook(browserFrame, this, ID_BROWSER, LAYOUT_FILL_Y|LAYOUT_FILL_X);
	
	// Filesystem tree
	new FXTabItem(browser, _("Filesystem"));
	FXVerticalFrame* frm1 = new FXVerticalFrame(browser, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	FXVerticalFrame* frm2 = new FXVerticalFrame(frm1, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_LINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	filesystemBrowser = new FXDirList(frm2, this, ID_FILESYSTEMBROWSER, DIRLIST_SHOWFILES|DIRLIST_NO_OWN_ASSOC|TREELIST_BROWSESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES|LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame* filterFrame = new FXHorizontalFrame(frm1, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4);
	new FXLabel(filterFrame, _("Filter:"),NULL,LAYOUT_CENTER_Y);
	filesystemFilter = new FXComboBox(filterFrame, 25, this, ID_FILESYSTEMFILTER, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK);
	filesystemFilter->setNumVisible(4);
	
	// Project tree
	new FXTabItem(browser, _("Project"));
	FXVerticalFrame* frm3 = new FXVerticalFrame(browser, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	FXVerticalFrame* frm4 = new FXVerticalFrame(frm3, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_LINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	projectBrowser = new FXDirList(frm4, this, ID_PROJECTBROWSER, DIRLIST_SHOWFILES|DIRLIST_NO_OWN_ASSOC|TREELIST_BROWSESELECT|TREELIST_SHOWS_BOXES|LAYOUT_FILL_Y|LAYOUT_FILL_X);
	projectBrowser->setDirectory("/home/jannis");
	FXHorizontalFrame* projectFilterFrame = new FXHorizontalFrame(frm3, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4);
	new FXLabel(projectFilterFrame, _("Filter:"), NULL, LAYOUT_CENTER_Y);
	projectFilter = new FXComboBox(projectFilterFrame, 25, this, ID_PROJECTFILTER, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK);
	projectFilter->setNumVisible(4);
	
	// Editor frame
	FXVerticalFrame* editorFrame = new FXVerticalFrame(splitter, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}


void 
MainWindow::create()
{
	FXMainWindow::create();
	loadSettings();
	show(PLACEMENT_SCREEN);
	projectSettingsDirty = FALSE;
}


MainWindow::~MainWindow()
{
	delete fileMenu;
	delete editMenu;
	delete projectMenu;
	delete viewMenu;
	delete helpMenu;
	delete statusBar;
	delete menuBar;
	delete menuBarDragShell;
	delete topDock;
	delete bottomDock;
	delete leftDock;
	delete rightDock;
}


void MainWindow::loadSettings()
{
	this->handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_LOADSETTINGS), NULL);
}


void MainWindow::saveSettings()
{
	this->handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_SAVESETTINGS), NULL);
}


InDESettings* MainWindow::getSettings()
{
	return &settings;
}


long MainWindow::onCmdQuit(FXObject*, FXSelector, void*)
{
	saveSettings();
	getApp()->exit(0);
}


long MainWindow::onCmdNew(FXObject*, FXSelector, void*)
{
	return 1;
}


long MainWindow::onCmdNewProject(FXObject*, FXSelector, void*)
{
	NewProjectWizard wizard(this, _("new InDE project"));
	if (wizard.execute(PLACEMENT_SCREEN))
	{
		//saveSettings();
	}
	//return 1;
}


long MainWindow::onCmdSaveSettings(FXObject*, FXSelector, void*)
{
	getApp()->reg().writeStringEntry("General", "baseDir", settings.general.baseDir.text());
	getApp()->reg().writeIntEntry("Saving", "saveOnTabSwitch", settings.saving.saveOnTabSwitch);
	getApp()->reg().writeIntEntry("Saving", "autosave", settings.saving.autosave);
	getApp()->reg().writeIntEntry("Saving", "autosaveInterval", settings.saving.autosaveInterval);
}


long MainWindow::onCmdLoadSettings(FXObject*, FXSelector, void*)
{
	settings.general.baseDir = getApp()->reg().readStringEntry("General", "baseDir", FXFile::getHomeDirectory().text());
	settings.saving.saveOnTabSwitch = getApp()->reg().readIntEntry("Saving", "saveOnTabSwitch", 0);
	settings.saving.autosave = getApp()->reg().readIntEntry("Saving", "autosave", 0);
	settings.saving.autosaveInterval = getApp()->reg().readIntEntry("Saving", "autosaveInterval", 0);
}


long MainWindow::onCmdSettings(FXObject*, FXSelector, void*)
{
	SettingsDialog dialog(this, _("InDE settings"));
	if (dialog.execute())
	{
		saveSettings();
	}
}


long MainWindow::onCmdSettingBaseDir(FXObject*, FXSelector, void* ptr)
{
	settings.general.baseDir = (FXString)(FXchar*)ptr;
	return 1;
}


long MainWindow::onUpdSettingBaseDir(FXObject* sender, FXSelector sel, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&settings.general.baseDir);
	return 1;
}


long MainWindow::onCmdSettingSaveOnTab(FXObject*, FXSelector, void* ptr)
{
	settings.saving.saveOnTabSwitch = (FXbool)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingSaveOnTab(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.saveOnTabSwitch);
	return 1;
}


long MainWindow::onCmdSettingAutosave(FXObject*, FXSelector, void* ptr)
{
	settings.saving.autosave = (FXbool)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingAutosave(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.autosave);
	return 1;
}


long MainWindow::onCmdSettingAutosaveInterval(FXObject*, FXSelector, void* ptr)
{
	settings.saving.autosaveInterval = (FXint)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingAutosaveInterval(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.autosaveInterval);
	return 1;
}

long MainWindow::onCmdProjectName(FXObject*, FXSelector, void* ptr) 
{
	projectSettings.general.name = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectName(FXObject* sender, FXSelector, void* ptr) 
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.name);
	return 1;
}


long MainWindow::onCmdProjectDescription(FXObject*, FXSelector, void* ptr) 
{
	projectSettings.general.description = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectDescription(FXObject* sender, FXSelector, void* ptr) 
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.description);
	return 1;
}


long MainWindow::onCmdProjectTarget(FXObject*, FXSelector, void* ptr) 
{
	projectSettings.general.target = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectTarget(FXObject* sender, FXSelector, void* ptr) 
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.target);
	return 1;
}


long MainWindow::onCmdProjectVersion(FXObject*, FXSelector, void* ptr) 
{
	projectSettings.general.version = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectVersion(FXObject* sender, FXSelector, void* ptr) 
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.version);
	return 1;
}


long MainWindow::onCmdProjectSrcDir(FXObject*, FXSelector, void* ptr)
{
	projectSettings.dirs.srcDir = (FXString)(FXchar*)ptr;
	if (projectSettings.dirs.srcDir[projectSettings.dirs.srcDir.length()-1] != '/')
		projectSettings.dirs.srcDir.append('/');
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectSrcDir(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.dirs.srcDir);
	return 1;
}


long MainWindow::onCmdProjectIncludeDir(FXObject*, FXSelector, void* ptr)
{
	projectSettings.dirs.includeDir = (FXString)(FXchar*)ptr;
	if (projectSettings.dirs.includeDir[projectSettings.dirs.includeDir.length()-1] != '/')
		projectSettings.dirs.includeDir.append('/');
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectIncludeDir(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.dirs.includeDir);
	return 1;
}


long MainWindow::onCmdProjectBinDir(FXObject*, FXSelector, void* ptr)
{
	projectSettings.dirs.binDir = (FXString)(FXchar*)ptr;
	if (projectSettings.dirs.binDir[projectSettings.dirs.binDir.length()-1] != '/')
		projectSettings.dirs.binDir.append('/');
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectBinDir(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.dirs.binDir);
	return 1;
}


long MainWindow::onCmdProjectIncludePathes(FXObject*, FXSelector, void* ptr)
{
	projectSettings.libs.includePathes = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectIncludePathes(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.libs.includePathes);
	return 1;
}


long MainWindow::onCmdProjectLibraryPathes(FXObject*, FXSelector, void* ptr)
{
	projectSettings.libs.libraryPathes = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectLibraryPathes(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.libs.libraryPathes);
	return 1;
}


long MainWindow::onCmdProjectLibraries(FXObject*, FXSelector, void* ptr)
{
	projectSettings.libs.libraries = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectLibraries(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.libs.libraries);
	return 1;
}


long MainWindow::onCmdProjectDebug(FXObject*, FXSelector, void* ptr)
{
	projectSettings.compiler.debug = (FXbool)(FXival)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectDebug(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&projectSettings.compiler.debug);
	return 1;
}


long MainWindow::onCmdProjectPic(FXObject*, FXSelector, void* ptr)
{
	projectSettings.compiler.pic = (FXbool)(FXival)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectPic(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&projectSettings.compiler.pic);
	return 1;
}


long MainWindow::onCmdProjectWarnings(FXObject*, FXSelector, void* ptr)
{
	projectSettings.compiler.warnings = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectWarnings(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.compiler.warnings);
	return 1;
}


long MainWindow::onCmdProjectDefines(FXObject*, FXSelector, void* ptr)
{
	projectSettings.compiler.defines = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectDefines(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.compiler.defines);
	return 1;
}


long MainWindow::onCmdProjectSwitches(FXObject*, FXSelector, void* ptr)
{
	projectSettings.compiler.additionalSwitches = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectSwitches(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.compiler.additionalSwitches);
	return 1;
}


