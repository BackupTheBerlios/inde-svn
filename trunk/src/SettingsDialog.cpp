#include "InDE.h"

FXDEFMAP(SettingsDialog) SettingsDialogMap[] = {
	FXMAPFUNC(SEL_COMMAND,		SettingsDialog::ID_ACCEPT,		SettingsDialog::onCmdAccept),
};

FXIMPLEMENT(SettingsDialog, FXDialogBox, SettingsDialogMap, ARRAYNUMBER(SettingsDialogMap))


//////////////////////////////////////////////////
// Constructor

SettingsDialog::SettingsDialog(FXWindow* p, InDESettings* settings, const FXString& name)
:	FXDialogBox(p, name, DECOR_ALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
	FXVerticalFrame* main = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	title = new DialogTitle(main, name);
	this->settings = settings;
	
	new FXHorizontalSeparator(main);
	FXHorizontalFrame* buttonFrame = new FXHorizontalFrame(main, LAYOUT_LEFT);
	new FXButton(buttonFrame, _("Save"), NULL, this, ID_ACCEPT);
	new FXButton(buttonFrame, _("Cancel"), NULL, this, FXDialogBox::ID_CANCEL);
}


//////////////////////////////////////////////////
// Create

void SettingsDialog::create()
{
	FXDialogBox::create();
}


//////////////////////////////////////////////////
// Destructor

SettingsDialog::~SettingsDialog()
{
	delete title;
}


//////////////////////////////////////////////////
// On accept button press: Write input values 
// into settings

long SettingsDialog::onCmdAccept(FXObject*, FXSelector, void* ptr)
{
	FXDialogBox::handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), ptr);
}
