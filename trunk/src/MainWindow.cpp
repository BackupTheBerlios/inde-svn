#include "InDE.h"

FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_CLOSE,			0,								MainWindow::onCmdQuit),
	FXMAPFUNC(SEL_SIGNAL,			MainWindow::ID_QUIT,			MainWindow::onCmdQuit),
	FXMAPFUNC(SEL_COMMAND,			MainWindow::ID_QUIT,			MainWindow::onCmdQuit),
	
	// File
	FXMAPFUNC(SEL_COMMAND,			MainWindow::ID_NEW,				MainWindow::onCmdNew),
	
	// Project
	FXMAPFUNC(SEL_COMMAND,			MainWindow::ID_NEWPROJECT,		MainWindow::onCmdNewProject),
	
	// Settings
	FXMAPFUNC(SEL_COMMAND,			MainWindow::ID_SAVESETTINGS,	MainWindow::onCmdSaveSettings),
	FXMAPFUNC(SEL_COMMAND,			MainWindow::ID_LOADSETTINGS,	MainWindow::onCmdLoadSettings),
	FXMAPFUNC(SEL_COMMAND,			MainWindow::ID_SETTINGS,		MainWindow::onCmdSettings),
};

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp* a, const FXString& title)
:	FXMainWindow(a, title, NULL, NULL, DECOR_ALL, 0, 0, 800, 600),
	baseDir(settings.baseDir)
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
	
	//////////////////////////////////////////////
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
	
	// InDE settings dialog
	settingsDialog = new SettingsDialog(this, &settings, _("InDE settings"));
}

void 
MainWindow::create()
{
	FXMainWindow::create();
	loadSettings();	
	show(PLACEMENT_SCREEN);
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
	return 1;
}

void MainWindow::loadSettings()
{
	this->handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_LOADSETTINGS), NULL);
}

void MainWindow::saveSettings()
{
	this->handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_SAVESETTINGS), NULL);
}

long MainWindow::onCmdSaveSettings(FXObject*, FXSelector, void*)
{
	getApp()->reg().writeStringEntry("SETTINGS", "baseDir", settings.baseDir.text());
}

long MainWindow::onCmdLoadSettings(FXObject*, FXSelector, void*)
{
	settings.baseDir = getApp()->reg().readStringEntry("SETTINGS", "baseDir", FXFile::getHomeDirectory().text());
}

long MainWindow::onCmdSettings(FXObject*, FXSelector, void*)
{
	settingsDialog->execute();
}
