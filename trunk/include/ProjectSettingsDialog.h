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

#ifndef PROJECTSETTINGSDIALOG_H
#define PROJECTSETTINGSDIALOG_H

#include <fx.h>
#include "MainWindow.h"
#include "ProjectSettings.h"

class MainWindow;


/*
	Class ProjectSettingsDialog

	This class provides a dialog for the user to change several 
	project settings.
*/
class ProjectSettingsDialog : public FXDialogBox
{
	FXDECLARE(ProjectSettingsDialog)
	
	protected:
		ProjectSettingsDialog() {};
		ProjectSettingsDialog(const ProjectSettingsDialog&);
		ProjectSettingsDialog& operator=(const ProjectSettingsDialog&);
		
	public:
		FXString		type;
		
		FXString		name;
		FXString		description;
		FXString		target;
		FXString		version;
		FXString		author;
		FXString		mail;
		FXint			license;
		FXString		licenseHeader;
		
		FXString		includePaths;
		FXString		libraryPaths;
		FXString		libraries;
		
		FXString		srcDir;
		FXString		includeDir;
		FXString		buildDir;
		FXString		docDir;
		FXString		ressourceDir;
		
		FXString		warnings;
		FXString		defines;
		FXString		switches;
		FXbool			debug;
		FXbool			pic;

	private:
		FXDataTarget	tgtType;
		
		FXDataTarget	tgtName;
		FXDataTarget	tgtDescription;
		FXDataTarget	tgtTarget;
		FXDataTarget	tgtVersion;
		
		FXDataTarget	tgtIncludePaths;
		FXDataTarget	tgtLibraryPaths;
		FXDataTarget	tgtLibraries;
		
		FXDataTarget	tgtSrcDir;
		FXDataTarget	tgtIncludeDir;
		FXDataTarget	tgtBuildDir;
		FXDataTarget	tgtDocDir;
		FXDataTarget	tgtRessourceDir;
		
		FXDataTarget	tgtWarnings;
		FXDataTarget	tgtDefines;
		FXDataTarget	tgtSwitches;
		FXDataTarget	tgtDebug;
		FXDataTarget	tgtPic;

		FXDataTarget	tgtAuthor;
		FXDataTarget	tgtMail;
		FXDataTarget	tgtLicense;
		FXDataTarget	tgtLicenseHeader;
		
	private:
		ProjectSettings	*settings;

	public:
		enum {
			ID_SELECTLICENSEFILE = FXDialogBox::ID_LAST,
			ID_LAST,
		};
		
	public:
		long onCmdSelectLicenseHeader(FXObject*, FXSelector, void*);
		
	public:
		/* 
			Constructor: ProjectSettingsDialog
		*/	
		ProjectSettingsDialog(MainWindow* owner, const FXString& title);
		
		/*
			Function: create
		*/
		virtual void create();
		
		/*
			Destructor: ~ProjectSettingsDialog
		*/
		~ProjectSettingsDialog();
		
		/*
			Function: check

			checks if the user provided us with the needed information
		*/
		FXbool check();

		/*
			Function: loadValues

			loads the settings from file
		*/
		void loadValues();

		/*
			Function: storeValues

			saves the settings to file
		*/
		void storeValues();

		/*
			Function: run

			executes the dialog. Needs the project settings to know which 
			project to edit.
		*/
		void run(ProjectSettings* ProjectSettings);
};

#endif // PROJECTSETTINGSDIALOG_H
