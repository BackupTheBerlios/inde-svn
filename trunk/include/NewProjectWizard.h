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

#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <fx.h>
#include "InDE.h"
#include "MainWindow.h"
#include "DialogTitle.h"

class MainWindow;

/*
	Class: NewProjectWizard

	NewProjectWizards provides several depending dialogs for the
	creation of a new InDE project
*/
class NewProjectWizard : public FXWizard  {

	FXDECLARE(NewProjectWizard)

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

		FXVerticalFrame* step1;
		FXVerticalFrame* step2;
		FXVerticalFrame* step3;
		FXVerticalFrame* step4;
		FXVerticalFrame* step5;

	protected:
		NewProjectWizard() {};
		NewProjectWizard(const NewProjectWizard&);
		NewProjectWizard& operator=(const NewProjectWizard&);

	public:
		enum {
			ID_SELECTLICENSEFILE = FXWizard::ID_LAST,
			ID_LAST
		};

	public:
		long onCmdSelectLicenseHeader(FXObject*, FXSelector, void*);

	public:

		/*
			Constructor: NewProjectWizard
		*/
		NewProjectWizard(MainWindow* owner, const FXString& name);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~NewProjectWizard
		*/
		virtual ~NewProjectWizard();

		/*
			Function: check

			Checks if the user provided us with the needed information
		*/
		FXbool check();

		/*
			Function: run

			Starts execution of NewProjectWizard
		*/
		void run();

		/*
			Function: storeValues

			Saves the project settings
		*/
		void storeValues();

};


#endif // NEWPROJECTWIZARD_H
