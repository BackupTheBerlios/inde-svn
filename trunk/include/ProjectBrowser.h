/*
 * InDE - Fast, pragmatic C++ IDE
 * Copyright (C) 2005 	InDE Development Team
 *						see AUTHOR file for more information
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

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
class ProjectBrowser : public FXVerticalFrame 
{
	FXDECLARE(ProjectBrowser)

	private:
		FXTreeList		*projectTree;

		MainWindow*		mainWin;

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
			RESSOURCE,
			DOC
		};

	public:
		enum {
			ID_BROWSER = FXComposite::ID_LAST,
		};

		long onDoubleClick(FXObject*, FXSelector, void*);

	public:
		/*
			Constructor: ProjectBrowser
		*/
		ProjectBrowser(FXComposite* p, MainWindow* win, FXObject* tgt=NULL, FXSelector sel=0, FXuint opts=FRAME_LINE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

		/*
			Destructor: ~ProjectBrowser
		*/
		virtual ~ProjectBrowser();

		// Fox interface
		/*
			Function: create
		*/
		void 	create();
	

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

		/*
			Function: getPathname

			returns the pathname of the given item
		*/
		FXString getPathname(FXTreeItem* item);
};




#endif // PROJECTBROWSER_H
