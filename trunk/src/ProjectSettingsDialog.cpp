#include "ProjectSettingsDialog.h"
#include "DialogTitle.h"

//////////////////////////////////////////////////
// Message map
FXDEFMAP(ProjectSettingsDialog) ProjectSettingsDialogMap[] = {
	FXMAPFUNC(SEL_COMMAND, ProjectSettingsDialog::ID_SELECTLICENSEFILE, ProjectSettingsDialog::onCmdSelectLicenseHeader),
};


//////////////////////////////////////////////////
// Object implementation
FXIMPLEMENT(ProjectSettingsDialog, FXDialogBox, ProjectSettingsDialogMap, ARRAYNUMBER(ProjectSettingsDialogMap))



//////////////////////////////////////////////////
// Constructor
ProjectSettingsDialog::ProjectSettingsDialog(MainWindow* owner, const FXString& title)
:	FXDialogBox(owner, title, DECOR_ALL),
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
	tgtWarnings(warnings),
	tgtDefines(defines),
	tgtSwitches(switches),
	tgtDebug(debug),
	tgtPic(pic),
	tgtAuthor(author),
	tgtMail(mail),
	tgtLicense(license),
	tgtLicenseHeader(licenseHeader)
{
	FXVerticalFrame* main = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame* content = new FXHorizontalFrame(main, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXVerticalFrame* nav = new FXVerticalFrame(content, LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	FXSwitcher* switcher = new FXSwitcher(content, LAYOUT_FILL_X|LAYOUT_FILL_Y);

	new FXButton(nav, "General\tGeneral settings\tChange the general project settings", NULL, switcher, FXSwitcher::ID_OPEN_FIRST, FRAME_RAISED|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 75, 50); 
	new FXButton(nav, "Directories\tProject directories\tChange the project directories", NULL, switcher, FXSwitcher::ID_OPEN_SECOND, FRAME_RAISED);
	new FXButton(nav, "Libraries\tLibrary and Path settings\tChange the library and path settings", NULL, switcher, FXSwitcher::ID_OPEN_THIRD, FRAME_RAISED|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 75, 50); 
	new FXButton(nav, "Compiler\tCompiler and Linker options\tChange the compiler and linker options", NULL, switcher, FXSwitcher::ID_OPEN_FOURTH, FRAME_RAISED);
	new FXButton(nav, "License\tAuthor and license settings\tChange the author and license settings", NULL, switcher, FXSwitcher::ID_OPEN_FIFTH, FRAME_RAISED|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 75, 50); 
	
	FXVerticalFrame* frm;
	FXMatrix* table;
	FXSpinner* interval;

	// General project settings
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "General project settings");
	new FXLabel(frm, "Project type:");
	FXComboBox* typeBox = new FXComboBox(frm, 0, &tgtType, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_NORMAL);
	typeBox->appendItem(PROJECT_TYPE_CPP);
	typeBox->appendItem(PROJECT_TYPE_PYTHON);
	typeBox->appendItem(PROJECT_TYPE_RUBY);
	typeBox->setNumVisible(3);
	typeBox->setEditable(FALSE);
	new FXLabel(frm, "Project name:");
	// textfield is readonly -> other configuration than in NewProjectWizard -> prepend user from renaming
	new FXTextField(frm, 60, &tgtName, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL|TEXTFIELD_READONLY);
	new FXLabel(frm, "Project description:");
	FXVerticalFrame* vfrm = new FXVerticalFrame(frm, FRAME_NORMAL|LAYOUT_FILL_X|LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	new FXText(vfrm, &tgtDescription, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(frm, "Building target:");
	FXComboBox* targetBox = new FXComboBox(frm, 20, &tgtTarget, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|COMBOBOX_NORMAL);
	targetBox->appendItem(PROJECT_BUILD_EXECUTABLE);
	targetBox->appendItem(PROJECT_BUILD_STATIC);
	targetBox->appendItem(PROJECT_BUILD_SHARED);
	targetBox->setNumVisible(3);
	targetBox->setEditable(FALSE);
	new FXLabel(frm, "Version:");
	new FXTextField(frm, 60, &tgtVersion, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// Project directories
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "Project directory settings");
	new FXLabel(frm, "Source directory:");
	new FXTextField(frm, 60, &tgtSrcDir, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(frm, "Include/header directory:");
	new FXTextField(frm, 60, &tgtIncludeDir, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(frm, "Build directory:");
	new FXTextField(frm, 60, &tgtBuildDir, FXDataTarget::ID_VALUE);

	// Libraries and path settings
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "Libraries and path settings");
	new FXLabel(frm, "Additional include directories (comma separated list):");
	new FXTextField(frm, 60, &tgtIncludePaths, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(frm, "Additional library directories (comma separated list):");
	new FXTextField(frm, 60, &tgtLibraryPaths, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(frm, "Libraries to link with (comma separated list, without suffix and prefix):");
	new FXTextField(frm, 60, &tgtLibraries, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// Compiler and linker options
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "Compiler and linker options");
	FXHorizontalFrame *hf = new FXHorizontalFrame(frm, LAYOUT_FILL_Y);
	new FXCheckButton(hf, "Enable debug symbols", &tgtDebug, FXDataTarget::ID_VALUE);
	new FXCheckButton(hf, "-PIC", &tgtPic, FXDataTarget::ID_VALUE);
	new FXLabel(frm, "Warnings (comma separated list)");
	new FXTextField(frm, 60, &tgtWarnings, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(frm, "Defines (comma separated list)");
	new FXTextField(frm, 60, &tgtDefines, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(frm, "Additional switches (comma separated list)");
	new FXTextField(frm, 60, &tgtSwitches, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);

	// author and license 
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "Author and License");
	FXVerticalFrame *vf1 = new FXVerticalFrame(frm, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(vf1, "Author's name");
	new FXTextField(vf1, 60, &tgtAuthor, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	FXVerticalFrame *vf2 = new FXVerticalFrame(frm, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(vf2, "Author's email address");
	new FXTextField(vf2, 60, &tgtMail, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	FXGroupBox *gp = new FXGroupBox(frm, "choose license");
	FXMatrix *mat = new FXMatrix(gp, 5, MATRIX_BY_COLUMNS|LAYOUT_FILL_X);
	new FXRadioButton(mat, "none", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_NONE);
	new FXRadioButton(mat, "GPL", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_GPL);
	new FXRadioButton(mat, "LGPL", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_LGPL);
	new FXRadioButton(mat, "user defined", &tgtLicense, FXDataTarget::ID_OPTION+PROJECT_LICENSE_USER);
	new FXLabel(frm, "user defined license header file");
	FXHorizontalFrame *hfa = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXTextField(hfa, 60, &tgtLicenseHeader, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXButton(hfa, "Select", NULL, this, ID_SELECTLICENSEFILE, BUTTON_NORMAL, 0, 0, 0, 0, 12, 12, 2, 2);


	new FXHorizontalSeparator(main);
	FXHorizontalFrame* btnFrame = new FXHorizontalFrame(main, LAYOUT_FILL_X|LAYOUT_RIGHT);
	new FXButton(btnFrame, "Close", NULL, this, FXDialogBox::ID_ACCEPT, FRAME_RAISED|FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_RIGHT, 0, 0, 0, 0, 12, 12, 2, 2);
}


//////////////////////////////////////////////////
// Destructor
ProjectSettingsDialog::~ProjectSettingsDialog()
{
}


//////////////////////////////////////////////////
// create
void ProjectSettingsDialog::create()
{
	FXDialogBox::create();
}



//////////////////////////////////////////////////
// check
FXbool ProjectSettingsDialog::check()
{
	FXuint errors = 0;
	
/*	if (!errors && ((MainWindow*)(getOwner()))->projectSettings.general.type.empty()) 
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "You have to select a project type.");
	}
	
	if (!errors && ((MainWindow*)(getOwner()))->projectSettings.general.name.empty())
	{	
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please enter a name for your project.");
	}
	
	if (!errors && ((MainWindow*)(getOwner()))->projectSettings.general.target.empty())
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "No project build target defined.");
	}
	
	if (!errors && ((MainWindow*)(getOwner()))->projectSettings.general.author.empty())
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please enter author's name.");
	}

	if (!errors && ((MainWindow*)(getOwner()))->projectSettings.general.licenseHeader.empty() && ((MainWindow*)(getOwner()))->projectSettings.general.license == PROJECT_LICENSE_USER)
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please select license header file.");
	}
*/
	return errors == 0;
}


//////////////////////////////////////////////////
// onCmdSelectLicenseHeader
long ProjectSettingsDialog::onCmdSelectLicenseHeader(FXObject*, FXSelector, void*)
{
	FXFileDialog dialog(this, "Select license file");
/*	dialog.setDirectory(((MainWindow*)(getOwner()))->settings.general.baseDir);
	if (dialog.execute())
	{
		((MainWindow*)(getOwner()))->projectSettings.general.licenseHeader = dialog.getFilename();
	}*/
	return 1;
}


//////////////////////////////////////////////////
// loadValues
void ProjectSettingsDialog::loadValues()
{
	settings->parse();

	type = 			settings->getStringValue("GENERAL", "type");
	name = 			settings->getStringValue("GENERAL", "name");
	description = 	settings->getStringValue("GENERAL", "description");
	target = 		settings->getStringValue("GENERAL", "target");
	version = 		settings->getStringValue("GENERAL", "version");
	author = 		settings->getStringValue("GENERAL", "author");
	mail = 			settings->getStringValue("GENERAL", "mail");
	license = 		settings->getIntValue	("GENERAL", "license");
	licenseHeader = settings->getStringValue("GENERAL", "licenseHeader");

	includePaths = 	settings->getStringValue("LIBRARY", "includePaths");
	libraryPaths = 	settings->getStringValue("LIBRARY", "libraryPaths");
	libraries = 	settings->getStringValue("LIBRARY", "libraries");
	
	srcDir = 		settings->getStringValue("DIRECTORY", "sourceDir");
	includeDir = 	settings->getStringValue("DIRECTORY", "includeDir");
	buildDir = 		settings->getStringValue("DIRECTORY", "buildDir");
	
	warnings = 		settings->getStringValue("COMPILER", "warnings");
	defines = 		settings->getStringValue("COMPILER", "defines");
	switches = 		settings->getStringValue("COMPILER", "switches");
	debug = 		settings->getIntValue	("COMPILER", "debug");
	pic = 			settings->getIntValue	("COMPILER", "pic");
}


//////////////////////////////////////////////////
// storeValues
void ProjectSettingsDialog::storeValues()
{
	settings->setStringValue("GENERAL", "type", 		type);
	settings->setStringValue("GENERAL", "name", 		name);
	settings->setStringValue("GENERAL", "description", 	description);
	settings->setStringValue("GENERAL", "target", 		target);
	settings->setStringValue("GENERAL", "version", 		version);
	settings->setStringValue("GENERAL", "author", 		author);
	settings->setStringValue("GENERAL", "mail", 		mail);
	settings->setIntValue	("GENERAL", "license", 		license);
	settings->setStringValue("GENERAL", "licenseHeader",licenseHeader);

	settings->setStringValue("LIBRARY", "includePaths", includePaths);
	settings->setStringValue("LIBRARY", "libraryPaths", libraryPaths);
	settings->setStringValue("LIBRARY", "libraries", 	libraries);
	
	settings->setStringValue("DIRECTORY", "sourceDir", 	srcDir);
	settings->setStringValue("DIRECTORY", "includeDir", includeDir);
	settings->setStringValue("DIRECTORY", "buildDir", 	buildDir);
	
	settings->setStringValue("COMPILER", "warnings", 	warnings);
	settings->setStringValue("COMPILER", "defines", 	defines);
	settings->setStringValue("COMPILER", "switches", 	switches);
	settings->setIntValue	("COMPILER", "debug", 		debug);
	settings->setIntValue	("COMPILER", "pic", 		pic);

	settings->write();
}


//////////////////////////////////////////////////
// run
void ProjectSettingsDialog::run(ProjectSettings* projectSettings)
{
	settings = projectSettings;
	loadValues();
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

