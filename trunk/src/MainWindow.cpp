#include "MainWindow.h"

FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_CLOSE,		0,											MainWindow::onCmdQuit),
	FXMAPFUNC(SEL_SIGNAL,		MainWindow::ID_QUIT,						MainWindow::onCmdQuit),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_QUIT,						MainWindow::onCmdQuit),
	
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_FILE_NEW,					MainWindow::onCmdNewFile),
	
	// Settings
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_WRITESETTINGS,				MainWindow::onCmdWriteSettings),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_LOADSETTINGS,				MainWindow::onCmdLoadSettings),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_EDITSETTINGS,				MainWindow::onCmdEditSettings),

	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_BASEDIR,				MainWindow::onCmdSettingBaseDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_BASEDIR,				MainWindow::onUpdSettingBaseDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_NUMRECENTPROJECTS,	MainWindow::onCmdSettingNumRecentProjects),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_NUMRECENTPROJECTS,	MainWindow::onUpdSettingNumRecentProjects),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_NUMRECENTFILES,		MainWindow::onCmdSettingNumRecentFiles),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_NUMRECENTFILES,		MainWindow::onUpdSettingNumRecentFiles),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_AUTOLOADLASTPROJECT, MainWindow::onCmdSettingAutoLoadLastProject),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_AUTOLOADLASTPROJECT, MainWindow::onUpdSettingAutoLoadLastProject),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_SAVEONTABSWITCH,		MainWindow::onCmdSettingSaveOnTabSwitch),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_SAVEONTABSWITCH,		MainWindow::onUpdSettingSaveOnTabSwitch),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_AUTOSAVE,			MainWindow::onCmdSettingAutosave),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_AUTOSAVE,			MainWindow::onUpdSettingAutosave),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_AUTOSAVEINTERVAL,	MainWindow::onCmdSettingAutosaveInterval),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_AUTOSAVEINTERVAL, 	MainWindow::onUpdSettingAutosaveInterval),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_BACKUPONSAVE,		MainWindow::onCmdSettingBackupOnSave),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_BACKUPONSAVE,		MainWindow::onUpdSettingBackupOnSave),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_SETTING_BACKUPSUFFIX,		MainWindow::onCmdSettingBackupSuffix),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_SETTING_BACKUPSUFFIX,		MainWindow::onUpdSettingBackupSuffix),

	// Project
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_NEW,					MainWindow::onCmdNewProject),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_CLOSE,				MainWindow::onCmdCloseProject),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_OPEN,				MainWindow::onCmdOpenProject),

	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_WRITECONFIG,			MainWindow::onCmdProjectWriteConfig),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LOADCONFIG,			MainWindow::onCmdProjectLoadConfig),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_EDITCONFIG,			MainWindow::onCmdProjectEditConfig),
	
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_TYPE,				MainWindow::onCmdProjectType),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_TYPE,				MainWindow::onUpdProjectType),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_NAME,				MainWindow::onCmdProjectName),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_NAME,				MainWindow::onUpdProjectName),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_DESCRIPTION,			MainWindow::onCmdProjectDescription),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_DESCRIPTION,			MainWindow::onUpdProjectDescription),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_TARGET,				MainWindow::onCmdProjectTarget),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_TARGET,				MainWindow::onUpdProjectTarget),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_VERSION,				MainWindow::onCmdProjectVersion),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_VERSION,				MainWindow::onUpdProjectVersion),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_SRCDIR,				MainWindow::onCmdProjectSrcDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_SRCDIR,				MainWindow::onUpdProjectSrcDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_INCLUDEDIR,			MainWindow::onCmdProjectIncludeDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_INCLUDEDIR,			MainWindow::onUpdProjectIncludeDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_BUILDDIR,			MainWindow::onCmdProjectBuildDir),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_BUILDDIR,			MainWindow::onUpdProjectBuildDir),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_INCLUDEPATHS,		MainWindow::onCmdProjectIncludePaths),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_INCLUDEPATHS,		MainWindow::onUpdProjectIncludePaths),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LIBRARYPATHS,		MainWindow::onCmdProjectLibraryPaths),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_LIBRARYPATHS,		MainWindow::onUpdProjectLibraryPaths),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LIBRARIES,			MainWindow::onCmdProjectLibraries),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_LIBRARIES,			MainWindow::onUpdProjectLibraries),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_DEBUG, 				MainWindow::onCmdProjectDebug),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_DEBUG, 				MainWindow::onUpdProjectDebug),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_PIC, 				MainWindow::onCmdProjectPic),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_PIC, 				MainWindow::onUpdProjectPic),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_WARNINGS, 			MainWindow::onCmdProjectWarnings),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_WARNINGS, 			MainWindow::onUpdProjectWarnings),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_DEFINES, 			MainWindow::onCmdProjectDefines),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_DEFINES, 			MainWindow::onUpdProjectDefines),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_SWITCHES, 			MainWindow::onCmdProjectSwitches),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_SWITCHES, 			MainWindow::onUpdProjectSwitches),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_AUTHOR, 				MainWindow::onCmdProjectAuthor),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_AUTHOR, 				MainWindow::onUpdProjectAuthor),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LICENSE, 				MainWindow::onCmdProjectLicense),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_LICENSE, 				MainWindow::onUpdProjectLicense),
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_PROJECT_LICENSEHEADER, 				MainWindow::onCmdProjectLicenseHeader),
	FXMAPFUNC(SEL_UPDATE,		MainWindow::ID_PROJECT_LICENSEHEADER, 				MainWindow::onUpdProjectLicenseHeader),
};

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap));


MainWindow::MainWindow(App* a, const FXString& title)
:	FXMainWindow(a, title, NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{
	// Status bar
	statusBar = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER|FRAME_RAISED);
	new FXButton(statusBar, "\tAbout InDE\tAbout InDE C++ IDE", NULL, this, ID_ABOUT, LAYOUT_FILL_Y|LAYOUT_RIGHT);
	
	// Docksites for menus and toolbars
	topDock = new FXDockSite(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
	bottomDock = new FXDockSite(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);
	leftDock = new FXDockSite(this, LAYOUT_SIDE_LEFT|LAYOUT_FILL_Y);
	rightDock = new FXDockSite(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y);
	
	// Menu bar with drag shell
	menuDragShell = new FXToolBarShell(this, FRAME_NONE);
	menuBar = new FXMenuBar(topDock, menuDragShell, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);
	new FXToolBarGrip(menuBar, menuBar, FXMenuBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);
	
	// Tool bar with drag shell
	toolDragShell = new FXToolBarShell(this, FRAME_NONE);
	toolBar = new FXToolBar(topDock, toolDragShell, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);
	new FXToolBarGrip(toolBar, toolBar, FXToolBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);
	
	// File menu
	fileMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, "File", NULL, fileMenu);
	
	// Edit menu
	editMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, "Edit", NULL, editMenu);
	
	// Project menu
	projectMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, "Project", NULL, projectMenu);
	
	// View menu
	viewMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, "View", NULL, viewMenu);
	
	// Preferences menu
	preferencesMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, "Preferences", NULL, preferencesMenu);
	
	// Help menu
	helpMenu = new FXMenuPane(this);
	new FXMenuTitle(menuBar, "Help", NULL, helpMenu);
	
	// Menu commands
	new FXMenuCommand(fileMenu, "New File\tCtrl+N", NULL, this, ID_FILE_NEW);
	new FXMenuCommand(fileMenu, "Quit\tCtrl+Q\tHallo", NULL, this, ID_QUIT);
	new FXMenuCommand(projectMenu, "Create new project", NULL, this, ID_PROJECT_NEW);
	new FXMenuCommand(projectMenu, "Open project", NULL, this, ID_PROJECT_OPEN);
	new FXMenuCommand(preferencesMenu, "InDE settings", NULL, this, ID_EDITSETTINGS);
	
	// Splitter
	FXSplitter* splitter = new FXSplitter(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y|SPLITTER_TRACKING);
	
	// Browser frame
	FXVerticalFrame* browserFrame = new FXVerticalFrame(splitter, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	tabBrowser = new FXTabBook(browserFrame, NULL, 0, LAYOUT_FILL_Y|LAYOUT_FILL_X);
	
	// Filesystem browser
	new FXTabItem(tabBrowser, "Filesystem");	
	FXVerticalFrame* frm1 = new FXVerticalFrame(tabBrowser, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	FXVerticalFrame* frm2 = new FXVerticalFrame(frm1, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_LINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	fileBrowser = new FXDirList(frm2, NULL, 0, DIRLIST_SHOWFILES|DIRLIST_NO_OWN_ASSOC|TREELIST_BROWSESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES|LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame* filterFrame = new FXHorizontalFrame(frm1, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4);
	new FXLabel(filterFrame, "Filter:",NULL,LAYOUT_CENTER_Y);
	fileFilter = new FXComboBox(filterFrame, 25, NULL, 0, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK);
	fileFilter->setNumVisible(4);
	
	// Project browser
	new FXTabItem(tabBrowser, "Project");
	FXVerticalFrame* frm3 = new FXVerticalFrame(tabBrowser, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	FXVerticalFrame* frm4 = new FXVerticalFrame(frm3, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_LINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	projectBrowser = new FXDirList(frm4, NULL, 0, DIRLIST_SHOWFILES|DIRLIST_NO_OWN_ASSOC|TREELIST_BROWSESELECT|TREELIST_SHOWS_BOXES|LAYOUT_FILL_Y|LAYOUT_FILL_X);
	FXHorizontalFrame* projectFilterFrame = new FXHorizontalFrame(frm3, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4);
	new FXLabel(projectFilterFrame, "Filter:", NULL, LAYOUT_CENTER_Y);
	projectFilter = new FXComboBox(projectFilterFrame, 25, NULL, 0, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK);
	projectFilter->setNumVisible(4);
	
	// Class browser
	new FXTabItem(tabBrowser, "Classes");
	
	// Editor frame
	FXVerticalFrame* editorFrame = new FXVerticalFrame(splitter, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}


void MainWindow::create()
{
	FXMainWindow::create();
	handle(this, FXSEL(SEL_COMMAND, ID_LOADSETTINGS), NULL);
	show(PLACEMENT_SCREEN);
	maximize();
	update();
}


MainWindow::~MainWindow()
{
	delete fileMenu;
	delete editMenu;
	delete projectMenu;
	delete viewMenu;
	delete helpMenu;
	delete preferencesMenu;
	delete menuDragShell;
	delete toolDragShell;
	delete menuBar;
	delete toolBar;
	delete statusBar;
	delete fileBrowser;
	delete fileFilter;
	delete projectBrowser;
	delete projectFilter;
	delete tabBrowser;
	delete topDock;
	delete bottomDock;
	delete rightDock;
	delete leftDock;
	//delete clock;
	//delete syntax;
}

InDESettings* MainWindow::getSettings()
{
	return &settings;
}


long MainWindow::onCmdQuit(FXObject*, FXSelector, void*)
{
	handle(this, FXSEL(SEL_COMMAND, ID_WRITESETTINGS), NULL);
	getApp()->exit(0);
}


long MainWindow::onCmdNewFile(FXObject*, FXSelector, void*)
{
	return 1;
}


long MainWindow::onCmdNewProject(FXObject*, FXSelector, void*)
{
	NewProjectWizard wizard(this, "New InDE project");
	do 
	{
		if (!wizard.execute(PLACEMENT_OWNER))
		{
			return 1;
		}
	}
	while (!wizard.check());
	
	// Values ok, create project
	FXString dirname = settings.general.baseDir + "/" + wizard.name;
	if (FXFile::exists(dirname))
	{
		if (FXMessageBox::question(this, MBOX_OK, "Warning", FXString("Project directory '"+dirname+"' already exists. Overwrite?").text()) == MBOX_CLICKED_NO)
			return 1;
		if (!FXFile::remove(dirname))
		{
			FXMessageBox::error(this, MBOX_OK, "Error", "Old directory could not be removed and thus, your project could not be created.");
			return 1;
		}
	}
	if (!FXFile::createDirectory(dirname, 0777))
	{
		FXMessageBox::error(this, MBOX_OK, "Error", "Project directory could not be created.");
		return 1;
	}
	
	// Write project config
	FXSettings config;
	config.writeStringEntry("General", "type", wizard.type.text());
	config.writeStringEntry("General", "name", wizard.name.text());
	config.writeStringEntry("General", "description", wizard.description.text());
	config.writeStringEntry("General", "target", wizard.target.text());
	config.writeStringEntry("General", "version", wizard.version.text());
	config.writeStringEntry("Directories", "source", wizard.srcDir.text());
	config.writeStringEntry("Directories", "include", wizard.includeDir.text());
	config.writeStringEntry("Directories", "build", wizard.buildDir.text());
	config.writeStringEntry("Libraries", "includePaths", wizard.includePaths.text());
	config.writeStringEntry("Libraries", "libraryPaths", wizard.libraryPaths.text());
	config.writeStringEntry("Libraries", "libraries", wizard.libraries.text());
	config.writeIntEntry("Compiler", "debug", wizard.debug);
	config.writeIntEntry("Compiler", "PIC", wizard.pic);
	config.writeStringEntry("Compiler", "warnings", wizard.warnings.text());
	config.writeStringEntry("Compiler", "defines", wizard.defines.text());
	config.writeStringEntry("Compiler", "switches", wizard.switches.text());
	config.unparseFile(dirname+"/project.cfg");

	FXMessageBox::information(this, MBOX_OK, "Success", FXString("Project '"+wizard.name+"' successfully created.").text());

	// Close current project
	handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_PROJECT_CLOSE), NULL);

	// Open new project
	openProject(dirname);

	return 1;
}


long MainWindow::onCmdWriteSettings(FXObject*, FXSelector, void*)
{
	getApp()->reg().writeStringEntry("General", "baseDir", settings.general.baseDir.text());
	getApp()->reg().writeIntEntry("Saving", "saveOnTabSwitch", settings.saving.saveOnTabSwitch);
	getApp()->reg().writeIntEntry("Saving", "autosave", settings.saving.autosave);
	getApp()->reg().writeIntEntry("Saving", "autosaveInterval", settings.saving.autosaveInterval);
	return 1;
}


long MainWindow::onCmdLoadSettings(FXObject*, FXSelector, void*)
{
	settings.general.baseDir = getApp()->reg().readStringEntry("General", "baseDir", FXFile::getHomeDirectory().text());
	settings.saving.saveOnTabSwitch = getApp()->reg().readIntEntry("Saving", "saveOnTabSwitch", 0);
	settings.saving.autosave = getApp()->reg().readIntEntry("Saving", "autosave", 0);
	settings.saving.autosaveInterval = getApp()->reg().readIntEntry("Saving", "autosaveInterval", 0);
	return 1;
}


long MainWindow::onCmdEditSettings(FXObject*, FXSelector, void*)
{
	SettingsDialog dialog(this, "InDE settings");
	do 
	{
		if (!dialog.execute(PLACEMENT_OWNER))
		{
			return 1;
		}
	}
	while (!dialog.check());
	handle(this, FXSEL(SEL_COMMAND, ID_WRITESETTINGS), NULL);
	return 1;
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


long MainWindow::onCmdSettingSaveOnTabSwitch(FXObject*, FXSelector, void* ptr)
{
	settings.saving.saveOnTabSwitch = (FXbool)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingSaveOnTabSwitch(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.saveOnTabSwitch);
	return 1;
}


long MainWindow::onCmdSettingAutosave(FXObject*, FXSelector, void* ptr)
{
	settings.saving.autosave = (FXbool)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingAutosave(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.autosave);
	return 1;
}


long MainWindow::onCmdSettingAutosaveInterval(FXObject*, FXSelector, void* ptr)
{
	settings.saving.autosaveInterval = (FXint)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingAutosaveInterval(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.autosaveInterval);
	return 1;
}


long MainWindow::onCmdSettingNumRecentProjects(FXObject*, FXSelector, void* ptr)
{
	settings.general.numRecentProjects = (FXuint)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingNumRecentProjects(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.general.numRecentProjects);
	return 1;
}


long MainWindow::onCmdSettingNumRecentFiles(FXObject*, FXSelector, void* ptr)
{
	settings.general.numRecentFiles = (FXuint)(FXuval)ptr;
	return 1;
}


long MainWindow::onUpdSettingNumRecentFiles(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXuval)&settings.general.numRecentFiles);
	return 1;
}


long MainWindow::onCmdSettingAutoLoadLastProject(FXObject*, FXSelector, void* ptr)
{
	settings.general.autoLoadLastProject = (FXbool)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingAutoLoadLastProject(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.general.autoLoadLastProject);
	return 1;
}


long MainWindow::onCmdSettingBackupOnSave(FXObject*, FXSelector, void* ptr)
{
	settings.saving.backupOnSave = (FXbool)(FXival)ptr;
	return 1;
}


long MainWindow::onUpdSettingBackupOnSave(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void*)(FXival)&settings.saving.backupOnSave);
	return 1;
}


long MainWindow::onCmdSettingBackupSuffix(FXObject*, FXSelector, void* ptr)
{
	settings.saving.backupSuffix = (FXString)(FXchar*)ptr;
	return 1;
}


long MainWindow::onUpdSettingBackupSuffix(FXObject* sender, FXSelector, void*)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&settings.saving.backupSuffix);
	return 1;
}


long MainWindow::onCmdProjectType(FXObject*, FXSelector, void* ptr) 
{
	projectSettings.general.type = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectType(FXObject* sender, FXSelector, void* ptr) 
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.type);
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
	projectSettings.directories.source = (FXString)(FXchar*)ptr;
	if (projectSettings.directories.source[projectSettings.directories.source.length()-1] != '/')
		projectSettings.directories.source.append('/');
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectSrcDir(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.directories.source);
	return 1;
}


long MainWindow::onCmdProjectIncludeDir(FXObject*, FXSelector, void* ptr)
{
	projectSettings.directories.include = (FXString)(FXchar*)ptr;
	if (projectSettings.directories.include[projectSettings.directories.include.length()-1] != '/')
		projectSettings.directories.include.append('/');
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectIncludeDir(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.directories.include);
	return 1;
}


long MainWindow::onCmdProjectBuildDir(FXObject*, FXSelector, void* ptr)
{
	projectSettings.directories.build = (FXString)(FXchar*)ptr;
	if (projectSettings.directories.build[projectSettings.directories.build.length()-1] != '/')
		projectSettings.directories.build.append('/');
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectBuildDir(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.directories.build);
	return 1;
}


long MainWindow::onCmdProjectIncludePaths(FXObject*, FXSelector, void* ptr)
{
	projectSettings.libraries.includePaths = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectIncludePaths(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.libraries.includePaths);
	return 1;
}


long MainWindow::onCmdProjectLibraryPaths(FXObject*, FXSelector, void* ptr)
{
	projectSettings.libraries.libraryPaths = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectLibraryPaths(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.libraries.libraryPaths);
	return 1;
}


long MainWindow::onCmdProjectLibraries(FXObject*, FXSelector, void* ptr)
{
	projectSettings.libraries.libraries = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectLibraries(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.libraries.libraries);
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
	projectSettings.compiler.switches = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectSwitches(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.compiler.switches);
	return 1;
}

long MainWindow::onCmdProjectAuthor(FXObject*, FXSelector, void* ptr)
{
	projectSettings.general.author = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectAuthor(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.author);
	return 1;
}


long MainWindow::onCmdProjectLicense(FXObject*, FXSelector, void* ptr)
{
	projectSettings.general.license = (FXint)(FXival)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectLicense(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXival)&projectSettings.general.license);
	return 1;
}


long MainWindow::onCmdProjectLicenseHeader(FXObject*, FXSelector, void* ptr)
{
	projectSettings.general.licenseHeader = (FXString)(FXchar*)ptr;
	projectSettingsDirty = TRUE;
	return 1;
}


long MainWindow::onUpdProjectLicenseHeader(FXObject* sender, FXSelector, void* ptr)
{
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void*)(FXchar*)&projectSettings.general.licenseHeader);
	return 1;
}


long MainWindow::onCmdProjectWriteConfig(FXObject*, FXSelector, void*)
{
	FXSettings config;
	config.writeStringEntry("General", "type", projectSettings.general.type.text());
	config.writeStringEntry("General", "name", projectSettings.general.name.text());
	config.writeStringEntry("General", "description", projectSettings.general.description.text());
	config.writeStringEntry("General", "target", projectSettings.general.target.text());
	config.writeStringEntry("General", "version", projectSettings.general.version.text());
	config.writeStringEntry("Directories", "source", projectSettings.directories.source.text());
	config.writeStringEntry("Directories", "include", projectSettings.directories.include.text());
	config.writeStringEntry("Directories", "build", projectSettings.directories.build.text());
	config.writeStringEntry("Libraries", "includePaths", projectSettings.libraries.includePaths.text());
	config.writeStringEntry("Libraries", "libraryPaths", projectSettings.libraries.libraryPaths.text());
	config.writeStringEntry("Libraries", "libraries", projectSettings.libraries.libraries.text());
	config.writeIntEntry("Compiler", "debug", projectSettings.compiler.debug);
	config.writeIntEntry("Compiler", "PIC", projectSettings.compiler.pic);
	config.writeStringEntry("Compiler", "warnings", projectSettings.compiler.warnings.text());
	config.writeStringEntry("Compiler", "defines", projectSettings.compiler.defines.text());
	config.writeStringEntry("Compiler", "switches", projectSettings.compiler.switches.text());
	config.writeStringEntry("General", "author", projectSettings.general.author.text());
	config.writeIntEntry("General", "license", projectSettings.general.license);
	config.writeStringEntry("General", "licenseHeader", projectSettings.general.licenseHeader.text());
	config.unparseFile(projectConfigFile);
	return 1;
}


long MainWindow::onCmdProjectLoadConfig(FXObject*, FXSelector, void*)
{
	FXSettings config;
	config.parseFile(projectConfigFile, FALSE);
	projectSettings.general.type = config.readStringEntry("General", "type", PROJECT_TYPE_CPP);
	projectSettings.general.name = config.readStringEntry("General", "name", "");
	projectSettings.general.description = config.readStringEntry("General", "description", "");
	projectSettings.general.target = config.readStringEntry("General", "target", PROJECT_BUILD_EXECUTABLE);
	projectSettings.general.version = config.readStringEntry("General", "version", "");
	projectSettings.directories.source = config.readStringEntry("Directories", "source", "");
	projectSettings.directories.include = config.readStringEntry("Directories", "include", "");
	projectSettings.directories.build = config.readStringEntry("Directories", "build", "");
	projectSettings.libraries.includePaths = config.readStringEntry("Libraries", "includePaths", "");
	projectSettings.libraries.libraryPaths = config.readStringEntry("Libraries", "libraryPaths", "");
	projectSettings.libraries.libraries = config.readStringEntry("Libraries", "libraries", "");
	projectSettings.compiler.debug = config.readIntEntry("Compiler", "debug", 0);
	projectSettings.compiler.pic = config.readIntEntry("Compiler", "PIC", 0);
	projectSettings.compiler.warnings = config.readStringEntry("Compiler", "warnings", "");
	projectSettings.compiler.defines = config.readStringEntry("Compiler", "defines", "");
	projectSettings.compiler.switches = config.readStringEntry("Compiler", "switches", "");
	projectSettings.general.author = config.readStringEntry("General", "author", "");
	projectSettings.general.license = config.readIntEntry("General", "license", 0);
	projectSettings.general.licenseHeader = config.readStringEntry("General", "licenseHeader", "");
}


long MainWindow::onCmdProjectEditConfig(FXObject*, FXSelector, void*)
{
}


long MainWindow::onCmdCloseProject(FXObject*, FXSelector, void*)
{
	// - Close (and ask to save) all files
	// Write project config
	handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_PROJECT_WRITECONFIG), NULL);
	return 1;
}


long MainWindow::onCmdOpenProject(FXObject*, FXSelector, void*)
{
	FXDirDialog dialog(this, "Select project by directory");
	dialog.setDirectory(settings.general.baseDir);
	if (dialog.execute())
	{
		if (!FXFile::exists(dialog.getDirectory()))
		{
			FXMessageBox::error(this, MBOX_OK, "Error", "Directory doesn't exist.");
			return 1;
		}
		
		handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_PROJECT_CLOSE), NULL);
		if (!openProject(dialog.getDirectory()))
		{
			FXMessageBox::error(this, MBOX_OK, "Error", "Directory doesn't seem to contain a InDE project. Doesn't a project.cfg exist?");
		}
	}
	return 1;
}


FXbool MainWindow::openProject(const FXString& location)
{
	FXString target = location;
	if (FXFile::isDirectory(target+"/"))
	{
		target += "/project.cfg";
	}
	if (!FXFile::isFile(target))
	{
		return false;
	}
	
	projectConfigFile = target;
	handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_PROJECT_LOADCONFIG), NULL);
	return true;
}
