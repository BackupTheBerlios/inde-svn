#include "MainWindow.h"
#include "SettingsDialog.h"
#include "AboutDialog.h"
#include "NewProjectWizard.h"
#include "ProjectSettingsDialog.h"
#include "FileSystem.h"
#include "NewClassDialog.h"

FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_COMMAND,		MainWindow::ID_QUIT,				MainWindow::onQuit),
	FXMAPFUNC(SEL_CLOSE,		0,									MainWindow::onQuit),
	FXMAPFUNC(SEL_SIGNAL,		MainWindow::ID_QUIT,				MainWindow::onQuit),
	FXMAPFUNCS(SEL_COMMAND,		MainWindow::ID_NEW_FILE,
								MainWindow::ID_CLOSE_FILES,			MainWindow::onFileCmd),
	FXMAPFUNCS(SEL_COMMAND,		MainWindow::ID_UNDO,
								MainWindow::ID_SHIFT_RIGHT,			MainWindow::onEditCmd),
	FXMAPFUNCS(SEL_COMMAND,		MainWindow::ID_NEW_PROJECT,
								MainWindow::ID_PROJECT_SETTINGS,	MainWindow::onProjectCmd),
	FXMAPFUNCS(SEL_COMMAND,		MainWindow::ID_PREV_TAB,
								MainWindow::ID_NEXT_TAB,			MainWindow::onViewCmd),
	FXMAPFUNCS(SEL_COMMAND,		MainWindow::ID_SETTINGS,
								MainWindow::ID_RESET_SETTINGS,		MainWindow::onOptionCmd),
	FXMAPFUNCS(SEL_COMMAND,		MainWindow::ID_HELP,
								MainWindow::ID_ABOUT,				MainWindow::onHelpCmd),
};

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(InDE* app, const FXString& title)
:	FXMainWindow(app, title, NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{
	settings = new Settings(FXFile::getHomeDirectory() + FS::dirSeparator() + FS::hiddenName("InDE") + FS::dirSeparator() + FS::configFilename("settings"));
	readSettings();
	buildMenu();
	statusBar = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER|FRAME_RAISED);
	buildContent();
	applySettings();
}

void MainWindow::create()
{
	FXMainWindow::create();
	show(PLACEMENT_SCREEN);
}

MainWindow::~MainWindow()
{
	delete settings;
	delete editor;

	delete highlightMenu;
	delete newMenu;
	delete fileMenu;
	delete editMenu;
	delete projectMenu;
	delete viewMenu;
	delete optionMenu;
	delete helpMenu;
	delete menuBar;
	delete menuDragShell;
	delete topDock;
	delete leftDock;
	delete rightDock;
	delete bottomDock;

	delete fileBrowser;
	delete fileFilter;
	delete projectBrowser;
	delete projectFilter;

	delete statusBar;
	delete browserFrame;
}

long MainWindow::onQuit(FXObject*, FXSelector, void*)
{
	FXTRACE((1, "MainWindow::onQuit()\n"));
	editor->closeAll();
	settings->write();
	getApp()->exit(0);
	return 1;
}

void MainWindow::buildMenu()
{
	topDock 		= new FXDockSite(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
	bottomDock 		= new FXDockSite(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);
	leftDock 		= new FXDockSite(this, LAYOUT_SIDE_LEFT|LAYOUT_FILL_Y);
	rightDock		= new FXDockSite(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y);

	menuDragShell 	= new FXToolBarShell(this, FRAME_NONE);

	menuBar			= new FXMenuBar(topDock, menuDragShell, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);
	new FXToolBarGrip(menuBar, menuBar, FXMenuBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);

	fileMenu 		= new FXMenuPane(this);
	editMenu 		= new FXMenuPane(this);
	projectMenu 	= new FXMenuPane(this);
	viewMenu 		= new FXMenuPane(this);
	optionMenu 		= new FXMenuPane(this);
	helpMenu 		= new FXMenuPane(this);
	newMenu 		= new FXMenuPane(this);
	highlightMenu	= new FXMenuPane(this);

	new FXMenuTitle(menuBar, "&File", NULL, fileMenu);
	new FXMenuTitle(menuBar, "&Edit", NULL, editMenu);
	new FXMenuTitle(menuBar, "&Project", NULL, projectMenu);
	new FXMenuTitle(menuBar, "&View", NULL, viewMenu);
	new FXMenuTitle(menuBar, "&Options", NULL, optionMenu);
	new FXMenuTitle(menuBar, "&Help", NULL, helpMenu);

	new FXMenuCascade(fileMenu, "&New ...", NULL, newMenu);
	new FXMenuSeparator(fileMenu);
	new FXMenuCommand(fileMenu, "&Open ...\tCtrl+O", NULL, this, ID_OPEN_FILE);
	new FXMenuSeparator(fileMenu);
	new FXMenuCommand(fileMenu, "&Save\tCtrl+S", NULL, this, ID_SAVE_FILE);
	new FXMenuCommand(fileMenu, "S&ave as ...", NULL, this, ID_SAVE_FILE_AS);
	new FXMenuCommand(fileMenu, "Save all", NULL, this, ID_SAVE_FILES);
	new FXMenuSeparator(fileMenu);
	new FXMenuCommand(fileMenu, "&Close\tCtrl+W", NULL, this, ID_CLOSE_FILE);
	new FXMenuCommand(fileMenu, "Close &all", NULL, this, ID_CLOSE_FILES);
	new FXMenuSeparator(fileMenu);
	new FXMenuCommand(fileMenu, "&Quit\tCtrl+Q\tExit InDE", NULL, this, ID_QUIT);

	new FXMenuCommand(editMenu, "&Undo\tCtrl+Z", NULL, this, ID_UNDO);
	new FXMenuCommand(editMenu, "&Redo\tCtrl+Y", NULL, this, ID_REDO);
	new FXMenuSeparator(editMenu);
	new FXMenuCommand(editMenu, "&Copy\tCtrl+C", NULL, this, ID_COPY);
	new FXMenuCommand(editMenu, "Cu&t\tCtrl+X", NULL, this, ID_CUT);
	new FXMenuCommand(editMenu, "&Paste\tCtrl+V", NULL, this, ID_PASTE);
	new FXMenuCommand(editMenu, "&Delete", NULL, this, ID_DELETE);
	new FXMenuSeparator(editMenu);
	new FXMenuCommand(editMenu, "&Search ...\tCtrl+F", NULL, this, ID_SEARCH);
	new FXMenuCommand(editMenu, "Search and &Replace ...\tCtrl+R", NULL, this, ID_SEARCH_REPLACE);
	new FXMenuCommand(editMenu, "&Goto line ...\tCtrl+G", NULL, this, ID_GOTO);
	new FXMenuSeparator(editMenu);
	new FXMenuCommand(editMenu, "Shift left"+FXString("\t"), NULL, this, ID_SHIFT_LEFT);
	new FXMenuCommand(editMenu, "Shift right"+FXString("\t"), NULL, this, ID_SHIFT_RIGHT);

	new FXMenuCommand(projectMenu, "&New ...", NULL, this, ID_NEW_PROJECT);
	new FXMenuSeparator(projectMenu);
	new FXMenuCommand(projectMenu, "&Open ...", NULL, this, ID_OPEN_PROJECT);
	new FXMenuSeparator(projectMenu);
	new FXMenuCommand(projectMenu, "&Close", NULL, this, ID_CLOSE_PROJECT);
	new FXMenuCommand(projectMenu, "Close &all", NULL, this, ID_CLOSE_ALL_PROJECTS);
	new FXMenuSeparator(projectMenu);
	new FXMenuCommand(projectMenu, "&Settings ...", NULL, this, ID_PROJECT_SETTINGS);

	new FXMenuCommand(viewMenu, "View &previous tab", NULL, this, ID_PREV_TAB);
	new FXMenuCommand(viewMenu, "View &next tab\tCtrl+Tab", NULL, this, ID_NEXT_TAB);
	new FXMenuSeparator(viewMenu);
	new FXMenuCascade(viewMenu, "Syntax highlighting ...", NULL, highlightMenu);

	new FXMenuCommand(optionMenu, "&Settings ...", NULL, this, ID_SETTINGS);
	new FXMenuCommand(optionMenu, "&Reset settings to defaults", NULL, this, ID_RESET_SETTINGS);

	new FXMenuCommand(helpMenu, "&About InDE ...", NULL, this, ID_ABOUT);

	new FXMenuCommand(newMenu, "File\tCtrl+N", NULL, this, ID_NEW_FILE);
	new FXMenuCommand(newMenu, "Class\tCtrl+Shift+N", NULL, this, ID_NEW_CLASS);
}

void MainWindow::buildContent()
{
	FXSplitter* splitter 	= new FXSplitter(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y|SPLITTER_TRACKING);
	FXVerticalFrame* frm1	= new FXVerticalFrame(splitter, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	browserFrame			= new FXTabBook(frm1, NULL, 0, LAYOUT_FILL_Y|LAYOUT_FILL_X);

	new FXTabItem(browserFrame, "Filesystem");
	FXVerticalFrame* frm2 	= new FXVerticalFrame(browserFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	fileBrowser 			= new FileBrowser(frm2, this);
	FXHorizontalFrame* frm4 = new FXHorizontalFrame(frm2, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4);
	new FXLabel(frm4, "Filter:", NULL, LAYOUT_CENTER_Y);
	fileFilter 				= new FXComboBox(frm4, 25, NULL, 0, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK);
	fileFilter->setNumVisible(4);

	new FXTabItem(browserFrame, "Project");
	FXVerticalFrame* frm5 	= new FXVerticalFrame(browserFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	projectBrowser 			= new ProjectBrowser(frm5, this);
	FXHorizontalFrame* frm7 = new FXHorizontalFrame(frm5, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4);
	new FXLabel(frm7, "Filter:", NULL, LAYOUT_CENTER_Y);
	projectFilter 			= new FXComboBox(frm7, 25, NULL, 0, COMBOBOX_STATIC|LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK);
	projectFilter->setNumVisible(4);

	new FXTabItem(browserFrame, "Classes");
	FXVerticalFrame* frm8 	= new FXVerticalFrame(browserFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0);
	FXVerticalFrame* frm9 	= new FXVerticalFrame(frm8, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_LINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	editor = new TabEditor(splitter, this);
}

long MainWindow::onFileCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "MainWindow::onFileCmd\n"));
	switch (FXSELID(sel))
	{
		case ID_NEW_FILE:
			editor->appendDocument();
			break;

		case ID_NEW_CLASS:
			if (projects.no() > 0)
			{
				NewClassDialog classDialog(this, "Add file to project?");
				FXString active = projectBrowser->getActiveProject();
				int i;
				for (i = 0; i < projects.no(); ++i)
				{
					if (active == projects[i]->getProjectName())
						break;
				}
				classDialog.run(projects[i]);
			}
			break;

		case ID_OPEN_FILE:
			break;

		case ID_SAVE_FILE:
			if (!editor->saveDocument())
			{
				FXMessageBox::error(this, MBOX_OK, "Error on save", "File could not be saved. You probably don't have the permissions.");
			}
			break;

		case ID_SAVE_FILE_AS:
			if (!editor->saveDocumentAs())
			{
				FXMessageBox::error(this, MBOX_OK, "Error on save", "File could not be saved. You probably don't have the permissions.");
			}
			break;

		case ID_SAVE_FILES:
			editor->saveAll();
			break;

		case ID_CLOSE_FILE:
			editor->closeDocument();
			break;

		case ID_CLOSE_FILES:
			editor->closeAll();
			break;
	}
	return 1;
}

long MainWindow::onEditCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "MainWindow::onEditCmd\n"));
	switch (FXSELID(sel))
	{
		case ID_UNDO:
			break;

		case ID_REDO:
			break;

		case ID_COPY:
			break;

		case ID_CUT:
			break;

		case ID_PASTE:
			break;

		case ID_DELETE:
			break;

		case ID_SEARCH:
			break;

		case ID_SEARCH_REPLACE:
			break;

		case ID_GOTO:
			break;

		case ID_SHIFT_LEFT:
			break;

		case ID_SHIFT_RIGHT:
			break;
	}
	return 1;
}

long MainWindow::onProjectCmd(FXObject*, FXSelector sel, void*)
{
	FXString active;
	int i;
	FXTRACE((1, "MainWindow::onProjectCmd\n"));
	switch (FXSELID(sel))
	{
		case ID_NEW_PROJECT:
			newProject();
		break;
		case ID_OPEN_PROJECT:
			openProject();
		break;
		case ID_CLOSE_PROJECT:
			active = projectBrowser->getActiveProject().text();
			for (i = 0; i < projects.no(); ++i)
			{
				if (active == projects[i]->getProjectName())
					break;
			}
			// close the project
		break;
		case ID_CLOSE_ALL_PROJECTS:
			// close all projects
		break;
		case ID_PROJECT_SETTINGS:
			if (projects.no())
			{
				active = projectBrowser->getActiveProject().text();
				for (i = 0; i < projects.no(); ++i)
				{
					if (active == projects[i]->getProjectName())
						break;
				}
				editProjectSettings(projects[i]);
			}
		break;
	}
	return 1;
}

long MainWindow::onOptionCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "MainWindow::onOptionCmd\n"));
	switch (FXSELID(sel))
	{
		case ID_SETTINGS:
			editSettings();
			applySettings();
			break;

		case ID_RESET_SETTINGS:
			resetSettings();
			applySettings();
			break;
	}
	return 1;
}

long MainWindow::onViewCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "MainWindow::onViewCmd\n"));
	switch (FXSELID(sel))
	{
		case ID_PREV_TAB:
			editor->showPreviousTab();
			break;
		case ID_NEXT_TAB:
			editor->showNextTab();
			break;
	}
	return 1;
}

long MainWindow::onHelpCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "MainWindow::onHelpCmd\n"));
	switch (FXSELID(sel))
	{
		case ID_HELP:
		case ID_ABOUT:
			aboutDialog();
			break;
	}
	return 1;
}

void MainWindow::editSettings()
{
	SettingsDialog dialog(this, "InDE settings");
	dialog.run();
}

void MainWindow::readSettings()
{
	settings->setDefault("baseDir", FXFile::getHomeDirectory());
	settings->setDefault("loadProject", true);
	settings->setDefault("EDITOR", "font", "courier [adobe],90,medium,regular");
	settings->setDefault("EDITOR", "syntaxFile", "share/syntax.stx");
	settings->setDefault("EDITOR", "lineNumbers", true);
	settings->setDefaultColor("COLORS", "foreColor", FXRGB(0, 0, 0));
	settings->setDefaultColor("COLORS", "backColor", FXRGB(255, 255, 255));
	settings->setDefaultColor("COLORS", "numberColor", FXRGB(100, 100, 100));
	settings->setDefaultColor("COLORS", "barColor", FXRGB(220, 220, 220));
	settings->setDefault("SAVING", "saveOnTabSwitch", true);
	settings->parse();
}

void MainWindow::resetSettings()
{
	if (FXMessageBox::question(this, MBOX_YES_NO, "Reset settings?", "Do you really want to reset the settings to defaults?") == MBOX_CLICKED_YES)
	{
		settings->defaults(true);
	}
}

void MainWindow::applySettings()
{
	FXTRACE((1, "MainWindow::applySettings()\n"));
	editor->applySettings();
}

void MainWindow::newProject()
{
	NewProjectWizard wizard(this, "new InDE project");
	wizard.run();
}

FXbool MainWindow::openProject(const FXString& location)
{
	FXString target = location;
	FXString name;
	if (location == "")
	{
		FXDirDialog dialog(this, "Select project by directory");
		dialog.setDirectory(settings->getStringValue("baseDir"));
		if (dialog.execute())
		{
			target = dialog.getDirectory();
			if (!FXFile::exists(target))
			{
				FXMessageBox::error(this, MBOX_OK, "Error", "Directory doesn't exist.");
				return false;
			}
		}
	}

	if (FXFile::isDirectory(target+"/"))
	{
		name = FXFile::name(target);
		target += "/project.inde";
	}
	if (!FXFile::isFile(target))
	{
		FXMessageBox::error(this, MBOX_OK, "Error", "Directory doesn't seem to contain a InDE project. Doesn't a project.inde exist?");
		return false;
	}

	ProjectSettings* settings = new ProjectSettings(target, name);
	projects.append(settings);
	projectBrowser->openProject(settings);
	return true;
}

void MainWindow::editProjectSettings(ProjectSettings* settings)
{
	ProjectSettingsDialog dialog(this, "InDE project settings");
	dialog.run(settings);
}

void MainWindow::aboutDialog()
{
	AboutDialog dialog(this, "About InDE SVN");
	dialog.setProgramName("InDE SVN snapshot");
	dialog.setDescription("InDE is a cross-platform C/C++ IDE.\n"
		"It supports managed projects using SCons instead of traditional Makefiles.\n"
		"The GUI is built on top of the FOX-Toolkit, which probably is the fastest toolkit available for linux.");
	dialog.setLicense("GNU GPL");
	dialog.setCopyright("© 2005, Jannis Pohlmann and Jochen Rassler");
	dialog.addDeveloper("Jannis Pohlmann", "devel@sten-net.de", "Head developer, Coordinator");
	dialog.addDeveloper("Jochen Rassler", "jochen@cornmania.de", "Developer (project management)");
	dialog.run();
}
