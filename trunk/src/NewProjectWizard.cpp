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
	new DialogTitle(step3, _("Step3"));
	new FXLabel(step3, _("Hier kommen die Menüpunkte...."));

	// Step 4:
	step4 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step4, _("Step4"));
	new FXLabel(step4, _("Hier kommen die Menüpunkte...."));

	// Step 5:
	step5 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step5, _("Step5"));
	new FXLabel(step5, _("Hier kommen die Menüpunkte...."));

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


//////////////////////////////////////////////////
// Handlers

// onCmdAccept
long NewProjectWizard::onCmdAccept(FXObject*, FXSelector, void*)
{
	return 1;
}
