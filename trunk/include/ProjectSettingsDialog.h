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
