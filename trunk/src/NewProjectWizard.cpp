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

#include "NewProjectWizard.h"

class MainWindow;

//////////////////////////////////////////////////
// Message map

FXDEFMAP(NewProjectWizard) NewProjectWizardMap[] = {
	FXMAPFUNC(SEL_COMMAND, NewProjectWizard::ID_SELECTLICENSEFILE, NewProjectWizard::onCmdSelectLicenseHeader),
};


//////////////////////////////////////////////////
// Object implementation

FXIMPLEMENT(NewProjectWizard, FXWizard, NewProjectWizardMap, ARRAYNUMBER(NewProjectWizardMap))


//////////////////////////////////////////////////
// Constructor

NewProjectWizard::NewProjectWizard(MainWindow* owner, const FXString& name)
:	FXWizard(owner, name, NULL),
	tgtType(type),
	tgtName(this->name),
	tgtDescription(description),
	tgtTarget(target),
	tgtVersion(version),
	tgtIncludePaths(includePaths),
	tgtLibraryPaths(libraryPaths),
	tgtLibraries(libraries),
	tgtSrcDir(srcDir),
	tgtIncludeDir(includeDir),
	tgtBuildDir(buildDir),
	tgtDocDir(docDir),
	tgtRessourceDir(ressourceDir),
	tgtWarnings(warnings),
	tgtDefines(defines),
	tgtSwitches(switches),
	tgtDebug(debug),
	tgtPic(pic),
	tgtAuthor(author),
	tgtMail(mail),
	tgtLicense(license),
	tgtLicenseHeader(licenseHeader),
	srcDir("src"),
	includeDir("include"),
	buildDir("build"),
	docDir("doc"),
	ressourceDir("ressources"),
	license(PROJECT_LICENSE_GPL),
	debug(1),
	pic(0)
{
	// Step 1: General project settings
	step1 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step1, "General project settings");
	new FXLabel(step1, "Project type:");
	FXComboBox* typeBox = new FXComboBox(step1, 0, &tgtType, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_NORMAL);
	typeBox->appendItem(PROJECT_TYPE_CPP);
	typeBox->appendItem(PROJECT_TYPE_PYTHON);
	typeBox->appendItem(PROJECT_TYPE_RUBY);
	typeBox->setNumVisible(3);
	typeBox->setCurrentItem(0);
	typeBox->setEditable(FALSE);
	new FXLabel(step1, "Project name:");
	new FXTextField(step1, 60, &tgtName, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step1, "Project description:");
	FXVerticalFrame* frm = new FXVerticalFrame(step1, FRAME_NORMAL|LAYOUT_FILL_X|LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	new FXText(frm, &tgtDescription, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(step1, "Building target:");
	FXComboBox* targetBox = new FXComboBox(step1, 20, &tgtTarget, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|COMBOBOX_NORMAL);
	targetBox->appendItem(PROJECT_BUILD_EXECUTABLE);
	targetBox->appendItem(PROJECT_BUILD_STATIC);
	targetBox->appendItem(PROJECT_BUILD_SHARED);
	targetBox->setNumVisible(3);
	targetBox->setCurrentItem(0);
	targetBox->setEditable(FALSE);
	new FXLabel(step1, "Version:");
	new FXTextField(step1, 60, &tgtVersion, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// Step 2: Project directories
	step2 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step2, "Project directory settings");
	new FXLabel(step2, "Source directory:");
	new FXTextField(step2, 60, &tgtSrcDir, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step2, "Include/header directory:");
	new FXTextField(step2, 60, &tgtIncludeDir, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step2, "Build directory:");
	new FXTextField(step2, 60, &tgtBuildDir, FXDataTarget::ID_VALUE);
	new FXLabel(step2, "Documentation directory:");
	new FXTextField(step2, 60, &tgtDocDir, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step2, "Ressource directory:");
	new FXTextField(step2, 60, &tgtRessourceDir, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// Step 3: Libraries and path settings
	step3 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step3, "Libraries and path settings");
	new FXLabel(step3, "Additional include directories (comma separated list):");
	new FXTextField(step3, 60, &tgtIncludePaths, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step3, "Additional library directories (comma separated list):");
	new FXTextField(step3, 60, &tgtLibraryPaths, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step3, "Libraries to link with (comma separated list, without suffix and prefix):");
	new FXTextField(step3, 60, &tgtLibraries, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// Step 4: Compiler and linker options
	step4 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step4, "Compiler and linker options");
	FXHorizontalFrame *hf = new FXHorizontalFrame(step4, LAYOUT_FILL_Y);
	new FXCheckButton(hf, "Enable debug symbols", &tgtDebug, FXDataTarget::ID_VALUE);
	new FXCheckButton(hf, "-PIC", &tgtPic, FXDataTarget::ID_VALUE);
	new FXLabel(step4, "Warnings (comma separated list)");
	new FXTextField(step4, 60, &tgtWarnings, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step4, "Defines (comma separated list)");
	new FXTextField(step4, 60, &tgtDefines, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step4, "Additional switches (comma separated list)");
	new FXTextField(step4, 60, &tgtSwitches, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// step 5: author and license 
	step5 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step5, "Author and License");
	FXVerticalFrame *vf1 = new FXVerticalFrame(step5, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(vf1, "Author's name");
	new FXTextField(vf1, 60, &tgtAuthor, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	FXVerticalFrame *vf2 = new FXVerticalFrame(step5, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(vf2, "Author's email address");
	new FXTextField(vf2, 60, &tgtMail, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	FXGroupBox *gp = new FXGroupBox(step5, "choose license");
	FXMatrix *mat = new FXMatrix(gp, 5, MATRIX_BY_COLUMNS|LAYOUT_FILL_X);
	new FXRadioButton(mat, "none", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_NONE);
	new FXRadioButton(mat, "GPL", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_GPL);
	new FXRadioButton(mat, "LGPL", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_LGPL);
	new FXRadioButton(mat, "user defined", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_USER);
	new FXLabel(step5, "user defined license header file");
	FXHorizontalFrame *hfa = new FXHorizontalFrame(step5, LAYOUT_FILL_X);
	new FXTextField(hfa, 60, &tgtLicenseHeader, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXButton(hfa, "Select", NULL, this, ID_SELECTLICENSEFILE, BUTTON_NORMAL, 0, 0, 0, 0, 12, 12, 2, 2);
}


//////////////////////////////////////////////////
// Create

void NewProjectWizard::create()
{
	FXWizard::create();
}


//////////////////////////////////////////////////
// Destructor

NewProjectWizard::~NewProjectWizard()
{
	delete step1;
	delete step2;
	delete step3;
	delete step4;
	delete step5;
}


FXbool NewProjectWizard::check()
{
	FXuint errors = 0;
	
	if (!errors && type.empty()) 
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "You have to select a project type.");
	}
	
	if (!errors && name.empty())
	{	
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please enter a name for your project.");
	}
	
	if (!errors && target.empty())
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "No project build target defined.");
	}
	
	if (!errors && author.empty())
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please enter author's name.");
	}

	if (!errors && licenseHeader.empty() && license == PROJECT_LICENSE_USER)
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please select license header file.");
	}

	if (errors)
		getContainer()->setCurrent(0);	
	
	return errors == 0;
}


long NewProjectWizard::onCmdSelectLicenseHeader(FXObject*, FXSelector, void*)
{
	FXFileDialog dialog(this, "Select license file");
	dialog.setDirectory(((MainWindow*)(getOwner()))->settings->getStringValue("baseDir"));
	if (dialog.execute())
	{
		licenseHeader = dialog.getFilename();
	}
	return 1;
}


void NewProjectWizard::run()
{
	do
	{
		if (!execute(PLACEMENT_OWNER))
		{
			return;
		}
	}
	while (!check());
	storeValues();
}


void NewProjectWizard::storeValues()
{
	FXString conffile;
	FXString path;
#ifdef WIN32
	path = FXString(((MainWindow*)(getOwner()))->settings->getStringValue("baseDir")) + "\\" +  name + "\\";
	conffile = path + "project.inde";
#else
	path = FXString(((MainWindow*)(getOwner()))->settings->getStringValue("baseDir")) + "/" +  name + "/";
	conffile = path + "project.inde";
#endif

	ProjectSettings* settings = new ProjectSettings(conffile, name);
	settings->parse();

	settings->setStringValue("GENERAL", "type", 			type);
	settings->setStringValue("GENERAL", "name", 			name);
	settings->setStringValue("GENERAL", "description", 		description);
	settings->setStringValue("GENERAL", "target", 			target);
	settings->setStringValue("GENERAL", "version",	 		version);
	settings->setStringValue("GENERAL", "author", 			author);
	settings->setStringValue("GENERAL", "mail", 			mail);
	settings->setIntValue	("GENERAL", "license",	 		license);
	settings->setStringValue("GENERAL", "licenseHeader",	licenseHeader);

	settings->setStringValue("LIBRARY", "includePaths",	 	includePaths);
	settings->setStringValue("LIBRARY", "libraryPaths", 	libraryPaths);
	settings->setStringValue("LIBRARY", "libraries", 		libraries);
	
	settings->setStringValue("DIRECTORY", "sourceDir", 		srcDir);
	settings->setStringValue("DIRECTORY", "includeDir", 	includeDir);
	settings->setStringValue("DIRECTORY", "buildDir", 		buildDir);
	settings->setStringValue("DIRECTORY", "docDir", 		docDir);
	settings->setStringValue("DIRECTORY", "ressourceDir", 	ressourceDir);
	settings->setStringValue("FILES", 	  "root", 			"");	// default value
	
	settings->setStringValue("COMPILER", "warnings", 		warnings);
	settings->setStringValue("COMPILER", "defines", 		defines);
	settings->setStringValue("COMPILER", "switches", 		switches);
	settings->setIntValue	("COMPILER", "debug", 			debug);
	settings->setIntValue	("COMPILER", "pic", 			pic);

	settings->write();
	((MainWindow*)(getOwner()))->projects.append(settings);
	((MainWindow*)(getOwner()))->projectBrowser->addProject(name);

	// create directories
	FXFile::createDirectory(path + srcDir, 0775);
	FXFile::createDirectory(path + includeDir, 0775);
	FXFile::createDirectory(path + buildDir, 0775);
	FXFile::createDirectory(path + docDir, 0775);
	FXFile::createDirectory(path + ressourceDir, 0775);
	((MainWindow*)(getOwner()))->projectBrowser->addDir(name, srcDir, ProjectBrowser::SOURCE);
	((MainWindow*)(getOwner()))->projectBrowser->addDir(name, includeDir, ProjectBrowser::INCLUDE);
	((MainWindow*)(getOwner()))->projectBrowser->addDir(name, docDir, ProjectBrowser::DOC);
	((MainWindow*)(getOwner()))->projectBrowser->addDir(name, ressourceDir, ProjectBrowser::RESSOURCE);

}

