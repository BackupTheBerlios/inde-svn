#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <fx.h>
#include "MainWindow.h"

class MainWindow;

/*
	Class: FileBrowser

	FXVerticalFrame subclass with a child FXDirList. Provides
	context menus for directories and files in order to
	open or import them into the current project.
*/
class FileBrowser : public FXVerticalFrame
{
	FXDECLARE(FileBrowser)

	protected:
		FileBrowser() {};
		FileBrowser(const FileBrowser&);
		FileBrowser& operator=(const FileBrowser&);

	private:
		FXDirList*		browser;
		FXMenuPane*		fileMenu;
		FXMenuPane*		dirMenu;
		MainWindow*		mainWin;
		FXTreeItem*		currentItem;

	public:
		enum {
			ID_BROWSER = FXVerticalFrame::ID_LAST,

			ID_OPEN_FILE,
			ID_IMPORT_FILE,
			ID_DELETE_FILE,

			ID_OPEN_FILES,
			ID_IMPORT_DIR,
			ID_IMPORT_FILES,
			ID_DELETE_DIR,
			ID_DELETE_FILES,

			ID_LAST,
		};

	public:
		long onRightClick(FXObject*, FXSelector, void*);
		long onDoubleClick(FXObject*, FXSelector, void*);
		long onMenuCmd(FXObject*, FXSelector, void*);

	public:

		/*
			Constructor: FileBrowser
		*/
		FileBrowser(FXComposite* p, MainWindow* win, FXObject* tgt=NULL, FXSelector sel=0, FXuint opts=FRAME_LINE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~FileBrowser
		*/
		virtual ~FileBrowser();

		/*
			Function: openFile

			Opens a file with given filename in the tabbed editor
		*/
		void openFile(const FXString& filename);

		/*
			Function: openFiles

			Opens all files in a given directory in the editor. Not recursive!
		*/
		void openFiles(const FXString& directory);

		/*
			Function: deleteFile

			Deletes a file after asking the user if he is really sure he wants to
		*/
		void deleteFile(const FXString& filename);

	protected:

		void buildMenus();
};

#endif // FILEBROWSER_H
