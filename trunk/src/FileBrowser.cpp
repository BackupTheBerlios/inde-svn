#include "FileBrowser.h"

FXDEFMAP(FileBrowser) FileBrowserMap[] = {
	FXMAPFUNC(SEL_RIGHTBUTTONRELEASE,		FileBrowser::ID_BROWSER,		FileBrowser::onRightClick),
	FXMAPFUNC(SEL_DOUBLECLICKED,			FileBrowser::ID_BROWSER,		FileBrowser::onDoubleClick),
	FXMAPFUNCS(SEL_COMMAND,					FileBrowser::ID_OPEN_FILE,
											FileBrowser::ID_DELETE_FILES,	FileBrowser::onMenuCmd),
};

FXIMPLEMENT(FileBrowser, FXVerticalFrame, FileBrowserMap, ARRAYNUMBER(FileBrowserMap))

FileBrowser::FileBrowser(FXComposite* p, MainWindow* win, FXObject* tgt, FXSelector sel, FXuint opts)
:	FXVerticalFrame(p, opts, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
	setTarget(tgt);
	setSelector(sel);
	mainWin = win;

	browser = new FXDirList(this, this, ID_BROWSER, DIRLIST_SHOWFILES|DIRLIST_NO_OWN_ASSOC|TREELIST_BROWSESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	buildMenus();
}

void FileBrowser::create()
{
	FXVerticalFrame::create();
}

FileBrowser::~FileBrowser()
{
	delete fileMenu;
	delete dirMenu;
	delete browser;
}

void FileBrowser::buildMenus()
{
	fileMenu 		= new FXMenuPane(this);
	dirMenu 		= new FXMenuPane(this);

	new FXMenuCommand(fileMenu, "Open file", NULL, this, ID_OPEN_FILE);
	new FXMenuSeparator(fileMenu);
	new FXMenuCommand(fileMenu, "Import file ...", NULL, this, ID_IMPORT_FILE);
	new FXMenuSeparator(fileMenu);
	new FXMenuCommand(fileMenu, "Delete file", NULL, this, ID_DELETE_FILE);

	new FXMenuCommand(dirMenu, "Open all files", NULL, this, ID_OPEN_FILES);
	new FXMenuSeparator(dirMenu);
	new FXMenuCommand(dirMenu, "Import directory", NULL, this, ID_IMPORT_DIR);
	new FXMenuCommand(dirMenu, "Import files ...", NULL, this, ID_IMPORT_FILES);
	new FXMenuSeparator(dirMenu);
	new FXMenuCommand(dirMenu, "Delete directory", NULL, this, ID_DELETE_DIR);
	new FXMenuCommand(dirMenu, "Delete all files", NULL, this, ID_DELETE_FILES);
}

long FileBrowser::onRightClick(FXObject* sender, FXSelector sel, void* ptr)
{
	FXTRACE((1, "FileBrowser::onRightClick()\n"));
	FXEvent* ev = (FXEvent*)ptr;
	FXTreeItem* item = browser->getItemAt(ev->click_x, ev->click_y);
	if (!item)
	{
		return 1;
	}
	browser->selectItem(item);
	currentItem = item;
	if (browser->isItemDirectory(item))
	{
		dirMenu->popup(NULL, ev->root_x, ev->root_y);
		getApp()->runModalWhileShown(dirMenu);
	}
	else if (browser->isItemFile(item))
	{
		fileMenu->popup(NULL, ev->root_x, ev->root_y);
		getApp()->runModalWhileShown(fileMenu);
	}
	return 1;
}

long FileBrowser::onDoubleClick(FXObject* sender, FXSelector sel, void* ptr)
{
	FXTRACE((1, "FileBrowser::onDoubleClick()\n"));
	if (ptr)
	{
		FXTreeItem* item = (FXTreeItem*)ptr;
		if (browser->isItemDirectory(item))
		{
	    	if(browser->isItemExpanded(item))
	    	{
				browser->collapseTree(item, TRUE);
			}
			else
			{
				browser->expandTree(item, TRUE);
			}
		}
		else if (browser->isItemFile(item))
		{
			mainWin->getEditor()->openFile(browser->getItemPathname(item));
		}
	}
	return 1;
}

long FileBrowser::onMenuCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "FileBrowser::onMenuCmd()\n"));
	switch (FXSELID(sel))
	{
		case ID_OPEN_FILE:
			if (currentItem)
			{
				openFile(browser->getItemPathname(currentItem));
			}
			break;

		case ID_IMPORT_FILE:
			break;

		case ID_DELETE_FILE:
			deleteFile(browser->getItemPathname(currentItem));
			break;

		case ID_OPEN_FILES:
			openFiles(browser->getItemPathname(currentItem));
			break;
	}
	return 1;
}

void FileBrowser::openFile(const FXString& filename)
{
	FXTRACE((1, "FileBrowser::openFile(%s)\n", filename.text()));
	mainWin->getEditor()->openFile(filename);
}

void FileBrowser::openFiles(const FXString& directory)
{
	FXTRACE((1, "FileBrowser::openFiles(%s)\n", directory.text()));
	FXString* files;
	FXint length = FXFile::listFiles(files, directory);
	for (FXint index = 0; index < length; index++)
	{
		FXString file = files[index];
		FXString absolute = FXFile::absolute(directory, file);
		if (file != ".." && file != "." && FXFile::isFile(absolute))
		{
			openFile(absolute);
		}
	}
}

void FileBrowser::deleteFile(const FXString& filename)
{
	if (FXMessageBox::warning(this, MBOX_YES_NO, "Delete file?", "Do you really want to delete %s", filename.text()) == MBOX_CLICKED_YES)
	{
		if (!FXFile::remove(filename))
		{
			FXMessageBox::error(this, MBOX_OK, "Error", "%s could not be deleted.", filename.text());
		}
	}
}
