#include "InDE.h"


class MainWindow;

//////////////////////////////////////////////////
// Message map

FXDEFMAP(NewProjectWizard) NewProjectWizardMap[] = {
	FXMAPFUNC(SEL_COMMAND,			NewProjectWizard::ID_irgendwas,		NewProjectWizard::onCmdAccept),		
};


//////////////////////////////////////////////////
// Object implementation

FXIMPLEMENT(NewProjectWizard, FXWizard, NewProjectWizardMap, ARRAYNUMBER(NewProjectWizardMap))


//////////////////////////////////////////////////
// Constructor

NewProjectWizard::NewProjectWizard(MainWindow* owner, const FXString& name)
		: FXWizard(owner, name, NULL) 
{
	// Step 1: general project information
	step1 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step1, _("General project settings"));
	new FXLabel(step1, _("enter project name:"));
	nameField = new FXTextField(step1, 60, this, MainWindow::ID_PROJECT_NAME);
	nameField->setText(_("myProject"));
	new FXLabel(step1, _("enter project description:"));
	descriptionField = new FXText(step1, this, MainWindow::ID_PROJECT_DESCRIPTION, FRAME_SUNKEN|FRAME_THICK);
	descriptionField->setVisibleColumns(60);
	descriptionField->setText(_("enter your project description here"));
	new FXLabel(step1, _("choose building target:"));
	targetBox = new FXComboBox(step1, 20, this, MainWindow::ID_PROJECT_TARGET);
	targetBox->appendItem("executable");
	targetBox->appendItem("static library");
	targetBox->appendItem("shared library");
	targetBox->setNumVisible(3);
	targetBox->setCurrentItem(0);
	targetBox->setEditable(FALSE);
	new FXLabel(step1, _("enter version:"));
	versionField = new FXTextField(step1, 60, this, MainWindow::ID_PROJECT_VERSION);
	versionField->setText(_("0.0.1"));

	// Step 2: project directories for source, include, and binary files
	step2 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step2, _("Project directory settings"));
	new FXLabel(step2, _("directory for source files"));
	srcDir = new FXTextField(step2, 60, this, MainWindow::ID_PROJECT_SRCDIR);
	srcDir->setText(_("src/"));
	new FXLabel(step2, _("directory for include files"));
	includeDir = new FXTextField(step2, 60, this, MainWindow::ID_PROJECT_INCLUDEDIR);
	includeDir->setText(_("include/"));
	new FXLabel(step2, _("directory for binary files"));
	binDir = new FXTextField(step2, 60, this, MainWindow::ID_PROJECT_BINDIR);
	binDir->setText(_("bin/"));

	// Step 3:
	step3 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step3, _("Libraries"));
	new FXLabel(step3, _("Additional include pathes (comma separated list)"));
	includePathes = new FXTextField(step3, 60, this, MainWindow::ID_PROJECT_INCLUDEPATHES);
	new FXLabel(step3, _("Additional library pathes (comma separated list)"));
	libraryPathes = new FXTextField(step3, 60, this, MainWindow::ID_PROJECT_LIBRARYPATHES);
	new FXLabel(step3, _("Additional libraries (comma separated list, without suffix and prefix)"));
	libraries = new FXTextField(step3, 60, this, MainWindow::ID_PROJECT_LIBRARIES);

	// Step 4: compiler options
	step4 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step4, _("Compiler options"));
	FXHorizontalFrame *hf = new FXHorizontalFrame(step4, LAYOUT_FILL_Y);
	debug = new FXCheckButton(hf, _("enable debug symbols"), this, MainWindow::ID_PROJECT_DEBUG);
	pic = new FXCheckButton(hf, _("-PIC"), this, MainWindow::ID_PROJECT_PIC);
	new FXLabel(step4, _("warnings (comma separated list)"));
	warnings = new FXTextField(step4, 60, this, MainWindow::ID_PROJECT_WARNINGS);
	new FXLabel(step4, _("defines (comma separated list)"));
	defines = new FXTextField(step4, 60, this, MainWindow::ID_PROJECT_DEFINES);
	new FXLabel(step4, _("additional switches (comma separated list)"));
	switches = new FXTextField(step4, 60, this, MainWindow::ID_PROJECT_SWITCHES);


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


//////////////////////////////////////////////////
// Handlers

// onCmdAccept
long NewProjectWizard::onCmdAccept(FXObject*, FXSelector, void*)
{
	return 1;
}
