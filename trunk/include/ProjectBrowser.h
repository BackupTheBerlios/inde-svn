#ifndef PROJECTBROWSER_H
#define PROJECTBROWSER_H

#include <fx.h>
#include "InDE.h"
#include "ProjectSettings.h"


/*
	Class: ProjectBrowser

	ProjectBrowser is a special FXTreeList like Widget, which provides 
	some functionality to easyly add new projects and files to its view.
*/
class ProjectBrowser : public FXComposite 
{
	FXDECLARE(ProjectBrowser)

	private:
		FXTreeList		*projectTree;

	protected:
		ProjectBrowser() {}
		ProjectBrowser(const ProjectBrowser&) {}

	public:
		enum FileType {
			CPP_SOURCE,
			CPP_HEADER,
			RESSOURCE_FILE,
			SCONS,
			TEXT
		};
		enum DirType {
			SOURCE,
			INCLUDE,
			RESSOURCE
		};

	public:
		/*
			Constructor: ProjectBrowser
		*/
		ProjectBrowser(FXComposite *p, FXObject *tgt = NULL, FXSelector sel = 0, FXuint opts = 0, FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0);

		/*
			Destructor: ~ProjectBrowser
		*/
		virtual ~ProjectBrowser();

		// Fox interface
		/*
			Function: create
		*/
		void 	create();
		/*
			Function: detach
		*/
		void 	detach();
		/*
			Function: layout
		*/
		void 	layout();
		/*
			Function: getDefaultWidth
		*/
		FXint 	getDefaultWidth();
		/*
			Function: getDefautHeight
		*/
		FXint 	getDefaultHeight();
		/*
			Function: getContentWidth
		*/
		FXint 	getContentWidth();
		/*
			Function: getContentHeight
		*/
		FXint 	getContentHeight();
		/*
			Function: recalc
		*/
		void 	recalc();
		/*
			Function: canFocus
		*/
		FXbool 	canFocus() const;
		/*
			Function: setFocus
		*/
		void 	setFocus();
		/*
			Function: killFocus
		*/
		void 	killFocus();
	

		// working operations
		/*
			Function: addFile

			adds a file to a project in dir
		*/
		void addFile	(FXString project, FXString name, FXString dir, FileType type = TEXT);
		/*
			Function: removeFile
		
			removes a file from project in dir
		*/
		void removeFile	(FXString project, FXString name, FXString dir);
		/*
			Function: moveFile

			moves a file in project from olddir to newdir
		*/
		void moveFile	(FXString project, FXString name, FXString olddir, FXString newdir);
		/*
			Function: renameFile

			renames a file from project in dri from name to newname
		*/
		void renameFile	(FXString project, FXString name, FXString newname, FXString dir);

		/*
			Function: addDir
		
			adds a dir of type to project
		*/
		void addDir		(FXString project, FXString dirname, DirType type = RESSOURCE);
		/*
			Function: removeDir

			removes a dir from project
		*/
		void removeDir	(FXString project, FXString dirname);
		/*
			Function: renameDir

			renames a dir in project from olddirname to newdirname
		*/
		void renameDir	(FXString project, FXString olddirname, FXString newdirname);

		/*
			Function: addProject

			adds a project to the browser
		*/
		void addProject		(FXString name);
		/*
			Function: removeProject

			removes a project from the browser
		*/
		void removeProject	(FXString name);
	

		/*
			Function: getActiveProject

			returns the name of the active project
		*/
		FXString getActiveProject();

		// load and save operations
		/*
			Function: openProject

			opens project settings from a settingsfile and adds it to the browser
		*/
		void openProject(ProjectSettings* settings);
};




#endif // PROJECTBROWSER_H
