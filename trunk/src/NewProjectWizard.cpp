#include "NewProjectWizard.h"

class MainWindow;

//////////////////////////////////////////////////
// Message map

FXDEFMAP(NewProjectWizard) NewProjectWizardMap[] = {
	0,
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
	tgtWarnings(warnings),
	tgtDefines(defines),
	tgtSwitches(switches),
	tgtDebug(debug),
	tgtPic(pic),
	srcDir("src/"),
	includeDir("include/"),
	buildDir("build/")
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
	new FXCheckButton(hf, "Enable debug symbols:", &tgtDebug, FXDataTarget::ID_VALUE);
	new FXLabel(hf, "Enable debug symbols");
	new FXCheckButton(hf, "-PIC", &tgtPic, FXDataTarget::ID_VALUE);
	new FXLabel(hf, "-PIC");
	new FXLabel(step4, "Warnings (comma separated list)");
	new FXTextField(step4, 60, &tgtWarnings, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step4, "Defines (comma separated list)");
	new FXTextField(step4, 60, &tgtDefines, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXLabel(step4, "Additional switches (comma separated list)");
	new FXTextField(step4, 60, &tgtSwitches, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
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
	
	if (!errors && version.empty())
	{
		errors++;
		FXMessageBox::error(this, MBOX_OK, "Error", "Please define a project version.");
	}
	
	if (errors)
		getContainer()->setCurrent(0);	
	
	return errors == 0;
}
