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
	// Step 1:
	step1 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step1, _("Step1"));
	new FXLabel(step1, _("Hier kommen die Menüpunkte...."));

	// Step 2:
	step2 = new FXVerticalFrame(getContainer(), LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(step2, _("Step2"));
	new FXLabel(step2, _("Hier kommen die Menüpunkte...."));

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
