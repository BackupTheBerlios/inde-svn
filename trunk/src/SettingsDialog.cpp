#include "SettingsDialog.h"

FXDEFMAP(SettingsDialog) SettingsDialogMap[] = {
	FXMAPFUNC(SEL_COMMAND, SettingsDialog::ID_SELECTBASEDIR, SettingsDialog::onCmdSelectBaseDir),
};

FXIMPLEMENT(SettingsDialog, FXDialogBox, SettingsDialogMap, ARRAYNUMBER(SettingsDialogMap))


SettingsDialog::SettingsDialog(MainWindow* owner, const FXString& title)
:	FXDialogBox(owner, title, DECOR_ALL)
{
	FXVerticalFrame* main = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame* content = new FXHorizontalFrame(main, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXVerticalFrame* nav = new FXVerticalFrame(content, LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	FXSwitcher* switcher = new FXSwitcher(content, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	
	new FXButton(nav, "General\tGeneral settings\tChange the general InDE settings", NULL, switcher, FXSwitcher::ID_OPEN_FIRST, FRAME_RAISED|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 75, 50); 
	new FXButton(nav, "Saving\tSaving settings\tConfigure autosave and so on", NULL, switcher, FXSwitcher::ID_OPEN_SECOND, FRAME_RAISED);
	
	FXVerticalFrame* frm;
	FXMatrix* table;
	FXSpinner* interval;
	
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "General settings");
	table = new FXMatrix(frm, 2, MATRIX_BY_COLUMNS);
	new FXLabel(table, "Base directory:");
	FXHorizontalFrame* hf = new FXHorizontalFrame(table, LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	new FXTextField(hf, 60, getOwner(), MainWindow::ID_SETTING_BASEDIR, LAYOUT_FILL_X|TEXTFIELD_NORMAL);
	new FXButton(hf, "Select", NULL, this, ID_SELECTBASEDIR, BUTTON_NORMAL, 0, 0, 0, 0, 12, 12, 2, 2);
	new FXLabel(table, "Recent project displayed:");
	interval = new FXSpinner(table, 5, getOwner(), MainWindow::ID_SETTING_NUMRECENTPROJECTS, FRAME_SUNKEN|FRAME_THICK);
	interval->setRange(0, 10);
	new FXLabel(table, "Recent files displayed:");
	interval = new FXSpinner(table, 5, getOwner(), MainWindow::ID_SETTING_NUMRECENTFILES, FRAME_SUNKEN|FRAME_THICK);
	interval->setRange(0, 10);
	new FXLabel(table, "Automatically load last project:");
	new FXCheckButton(table, "Yes", getOwner(), MainWindow::ID_SETTING_AUTOLOADLASTPROJECT);
	
	frm = new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "Saving settings");
	table = new FXMatrix(frm, 2, MATRIX_BY_COLUMNS);
	new FXLabel(table, "Save on tab switch:");
	new FXCheckButton(table, "Yes", getOwner(), MainWindow::ID_SETTING_SAVEONTABSWITCH);
	new FXLabel(table, "Autosave:");
	new FXCheckButton(table, "Yes", getOwner(), MainWindow::ID_SETTING_AUTOSAVE);
	new FXLabel(table, "Autosave interval (in seconds):");
	interval = new FXSpinner(table, 5, getOwner(), MainWindow::ID_SETTING_AUTOSAVEINTERVAL, FRAME_SUNKEN|FRAME_THICK);
	interval->setRange(0, 3600);
	new FXLabel(table, "Create backup when saving file:");
	new FXCheckButton(table, "Yes", getOwner(), MainWindow::ID_SETTING_BACKUPONSAVE);
	new FXLabel(table, "Backup file suffix:");
	new FXTextField(table, 10, getOwner(), MainWindow::ID_SETTING_BACKUPSUFFIX);
	
	new FXHorizontalSeparator(main);
	FXHorizontalFrame* btnFrame = new FXHorizontalFrame(main, LAYOUT_FILL_X|LAYOUT_RIGHT);
	new FXButton(btnFrame, "Close", NULL, this, FXDialogBox::ID_ACCEPT, FRAME_RAISED|FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_RIGHT, 0, 0, 0, 0, 12, 12, 2, 2);
}


void SettingsDialog::create()
{
	FXDialogBox::create();
}


SettingsDialog::~SettingsDialog()
{
}


FXbool SettingsDialog::check()
{
	return true;
}


long SettingsDialog::onCmdSelectBaseDir(FXObject*, FXSelector, void*)
{
	FXDirDialog dialog(this, "Select base directory");
	dialog.setDirectory(((MainWindow*)(getOwner()))->settings.general.baseDir);
	if (dialog.execute())
	{
		getOwner()->handle(this, FXSEL(SEL_COMMAND, MainWindow::ID_SETTING_BASEDIR), (void*)dialog.getDirectory().text());
	}
}
