#include "InDE.h"

class MainWindow;


//////////////////////////////////////////////////
// Message map

FXDEFMAP(SettingsDialog) SettingsDialogMap[] = {
	FXMAPFUNC(SEL_COMMAND,			SettingsDialog::ID_SELECTBASEDIR,		SettingsDialog::onCmdSelectBaseDir),		
};


//////////////////////////////////////////////////
// Object implementation

FXIMPLEMENT(SettingsDialog, FXDialogBox, SettingsDialogMap, ARRAYNUMBER(SettingsDialogMap))


//////////////////////////////////////////////////
// Constructor

SettingsDialog::SettingsDialog(MainWindow* owner, const FXString& name)
:	FXDialogBox(owner, name, DECOR_ALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
	// Main frame
	FXVerticalFrame* main = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	// Dialog title
	title = new DialogTitle(main, name);

	// Content frames	
	FXHorizontalFrame* content = new FXHorizontalFrame(main, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXVerticalFrame* nav = new FXVerticalFrame(content, LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	FXSwitcher* switcher = new FXSwitcher(content, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	
	// General settings button
	new FXButton(nav, _("General\tGeneral settings\tChange the general InDE settings"), NULL, switcher, FXSwitcher::ID_OPEN_FIRST, FRAME_RAISED|LAYOUT_FIX_HEIGHT, 0, 0, 50, 50); 
	
	// General settings
	FXMatrix* table = new FXMatrix(switcher, 3, MATRIX_BY_COLUMNS);
	new FXLabel(table, _("Base directory:"));
	inputBaseDir = new FXTextField(table, 50, owner, MainWindow::ID_SETTINGS_BASEDIR);
	new FXButton(table, _("Select"), NULL, this, ID_SELECTBASEDIR);
	
	// Saving settings button
	new FXButton(nav, _("Saving\tSaving configuration\tConfigure autosave and so on"), NULL, switcher, FXSwitcher::ID_OPEN_SECOND, FRAME_RAISED|LAYOUT_FILL_Y);
	
	// Saving settings
	table = new FXMatrix(switcher, 3, MATRIX_BY_COLUMNS);
	new FXLabel(table, _("Save on tab switch:"));
	new FXCheckButton(table, _("Yes"), owner, MainWindow::ID_SETTINGS_SAVEONTAB);
	new FXFrame(table, FRAME_NONE);
	new FXLabel(table, _("Autosave:"));
	new FXCheckButton(table, _("Yes"), owner, MainWindow::ID_SETTINGS_AUTOSAVE);
	new FXFrame(table, FRAME_NONE);
	new FXLabel(table, _("Autosave interval:"));
	FXSpinner* interval = new FXSpinner(table, 5, owner, MainWindow::ID_SETTINGS_AUTOSAVE_INTERVAL, FRAME_SUNKEN|FRAME_THICK);
	interval->setRange(0, 60);
	new FXLabel(table, _("From 0 up to 60 minutes"));
	
	new FXHorizontalSeparator(main);
	FXHorizontalFrame* buttonFrame = new FXHorizontalFrame(main, LAYOUT_RIGHT);
	new FXButton(buttonFrame, _("&Close"), NULL, this, FXDialogBox::ID_ACCEPT);
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
	delete inputBaseDir;
}


long SettingsDialog::onCmdSelectBaseDir(FXObject*, FXSelector, void*)
{
	FXDirDialog dialog(this, _("Select base directory"));
	dialog.setDirectory(inputBaseDir->getText());
	if (dialog.execute())
	{
		getOwner()->handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_SETTINGS_BASEDIR), (void*)dialog.getDirectory().text());
	}
}
