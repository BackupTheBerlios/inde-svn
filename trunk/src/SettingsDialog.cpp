#include "SettingsDialog.h"

FXDEFMAP(SettingsDialog) SettingsDialogMap[] = {
	FXMAPFUNC(SEL_COMMAND, SettingsDialog::ID_SELECT_BASEDIR, SettingsDialog::onSelectBaseDir),
	FXMAPFUNC(SEL_COMMAND, SettingsDialog::ID_SELECT_FONT, SettingsDialog::onSelectFont),
	FXMAPFUNC(SEL_COMMAND, SettingsDialog::ID_SELECT_SYNTAXFILE, SettingsDialog::onSelectSyntaxFile),
};

FXIMPLEMENT(SettingsDialog, FXDialogBox, SettingsDialogMap, ARRAYNUMBER(SettingsDialogMap))

SettingsDialog::SettingsDialog(MainWindow* owner, const FXString& title)
:	FXDialogBox(owner, title),
	tgtBaseDir(baseDir),
	tgtLoadProject(loadProject),
	tgtFont(font),
	tgtSyntaxFile(syntaxFile),
	tgtLineNumbers(lineNumbers),
	tgtBarColor(barColor),
	tgtBackColor(backColor),
	tgtForeColor(foreColor),
	tgtNumberColor(numberColor)
{
	FXVerticalFrame* 	vertical 	= new FXVerticalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame*	horizontal	= new FXHorizontalFrame(vertical, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXVerticalFrame*	buttons		= new FXVerticalFrame(horizontal, LAYOUT_LEFT|LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	switcher						= new FXSwitcher(horizontal, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0);

	// Buttons
	new FXButton(buttons, "General", NULL, switcher, FXSwitcher::ID_OPEN_FIRST, FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);
	new FXButton(buttons, "Editor", NULL, switcher, FXSwitcher::ID_OPEN_SECOND, FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);
	new FXButton(buttons, "Colors", NULL, switcher, FXSwitcher::ID_OPEN_THIRD, FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);

	FXVerticalFrame*	general		= new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(general, "General settings", NULL, LAYOUT_LEFT);
	new FXHorizontalSeparator(general, SEPARATOR_LINE|LAYOUT_FILL_X);
	FXMatrix*			matrix1		= new FXMatrix(general, 3, MATRIX_BY_COLUMNS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	new FXLabel(matrix1, "Project base directory:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXTextField(matrix1, 50, &tgtBaseDir, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXButton(matrix1, "Select ...", NULL, this, ID_SELECT_BASEDIR, FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);
	new FXLabel(matrix1, "Load last project on start:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXCheckButton(matrix1, "Yes", &tgtLoadProject, FXDataTarget::ID_VALUE);

	FXVerticalFrame*	editor		= new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(editor, "Editor settings");
	new FXHorizontalSeparator(editor, SEPARATOR_LINE|LAYOUT_FILL_X);
	FXMatrix*			matrix2		= new FXMatrix(editor, 3, MATRIX_BY_COLUMNS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXLabel(matrix2, "Editor font:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXTextField(matrix2, 50, &tgtFont, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXButton(matrix2, "Select ...", NULL, this, ID_SELECT_FONT, FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);
	new FXLabel(matrix2, "Syntax file:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXTextField(matrix2, 50, &tgtSyntaxFile, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXButton(matrix2, "Select ...", NULL, this, ID_SELECT_SYNTAXFILE, FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);
	new FXLabel(matrix2, "Display line numbers:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
	new FXCheckButton(matrix2, "Yes", &tgtLineNumbers, FXDataTarget::ID_VALUE);

	FXVerticalFrame*	colors		= new FXVerticalFrame(switcher, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXMatrix*			matrix3		= new FXMatrix(colors, 3, MATRIX_BY_COLUMNS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_X);
	new FXLabel(matrix3, "Line numbers:");
	new FXColorWell(matrix3, FXRGB(0, 0, 0), &tgtNumberColor, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_ROW,0,0,40,24);
	new FXColorWell(matrix3, FXRGB(0, 0, 0), &tgtBarColor, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_ROW,0,0,40,24);
	new FXLabel(matrix3, "Text:");
	new FXColorWell(matrix3, FXRGB(0, 0, 0), &tgtForeColor, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_ROW,0,0,40,24);
	new FXColorWell(matrix3, FXRGB(0, 0, 0), &tgtBackColor, FXDataTarget::ID_VALUE, FRAME_SUNKEN|FRAME_THICK|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_ROW,0,0,40,24);

	new FXHorizontalSeparator(vertical, SEPARATOR_RIDGE|LAYOUT_FILL_X);
  	FXHorizontalFrame* box 			= new FXHorizontalFrame(vertical, LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
	new FXButton(box, "&Accept", NULL, this, FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);
	new FXButton(box, "&Cancel", NULL, this, FXDialogBox::ID_CANCEL, BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);
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
	FXuint errors = 0;
	FXuint frame = 0;

	if (!errors && !FXFile::isDirectory(baseDir))
	{
		switch (FXMessageBox::question(this, MBOX_YES_NO, "Directory not found", "The selected base directory could not be found. Do you want to create it?"))
		{
			case MBOX_CLICKED_YES:
				FXFile::createDirectory(baseDir, 0777);
				break;
			case MBOX_CLICKED_NO:
				errors++;
				frame = 0;
				break;
		}
	}

	if (!errors && !FXFile::exists(syntaxFile))
	{
		FXMessageBox::error(this, MBOX_OK, "Syntax file not found", "The syntax file you selected could not be found. Please select a different file.");
		errors++;
		frame = 1;
	}

	if (errors > 0)
	{
		switcher->setCurrent(frame);
	}

	return errors == 0;
}

void SettingsDialog::loadValues()
{
	Settings* settings = getOwner()->settings;
	baseDir 	= settings->getStringValue("baseDir");
	loadProject = settings->getIntValue("loadProject");
	font 		= settings->getStringValue("EDITOR", "font");
	syntaxFile	= settings->getStringValue("EDITOR", "syntaxFile");
	lineNumbers = settings->getIntValue("EDITOR", "lineNumbers");
	numberColor	= settings->getColorValue("COLORS", "numberColor");
	barColor	= settings->getColorValue("COLORS", "barColor");
	backColor	= settings->getColorValue("COLORS", "backColor");
	foreColor	= settings->getColorValue("COLORS", "foreColor");
}

void SettingsDialog::storeValues()
{
	Settings* settings = getOwner()->settings;
	settings->setStringValue("baseDir", baseDir);
	settings->setIntValue("loadProject", loadProject);
	settings->setStringValue("EDITOR", "font", font);
	settings->setStringValue("EDITOR", "syntaxFile", syntaxFile);
	settings->setIntValue("EDITOR", "lineNumbers", lineNumbers);
	settings->setColorValue("COLORS", "numberColor", numberColor);
	settings->setColorValue("COLORS", "barColor", barColor);
	settings->setColorValue("COLORS", "foreColor", foreColor);
	settings->setColorValue("COLORS", "backColor", backColor);
}

void SettingsDialog::run()
{
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

long SettingsDialog::onSelectBaseDir(FXObject*, FXSelector, void*)
{
	FXDirDialog dialog(this, "Select base directory");
	dialog.setDirectory(baseDir);
	if (dialog.execute())
	{
		baseDir = dialog.getDirectory();
	}
	return 1;
}

long SettingsDialog::onSelectFont(FXObject*, FXSelector, void*)
{
	FXFontDialog dialog(this, "Select editor font");
	FXFont font(getApp(), this->font);
	FXFontDesc desc;
	font.getFontDesc(desc);
	dialog.setFontSelection(desc);
	if (dialog.execute())
	{
		dialog.getFontSelection(desc);
		font.setFontDesc(desc);
		this->font = font.getFont();
	}
	return 1;
}

long SettingsDialog::onSelectSyntaxFile(FXObject*, FXSelector, void*)
{
	FXFileDialog dialog(this, "Select syntax file");
	dialog.setFilename(syntaxFile);
	FXString newFile;
	do
	{
		if (!dialog.execute())
		{
			return 1;
		}
		newFile = dialog.getFilename();
	}
	while (!FXFile::exists(newFile));
	syntaxFile = newFile;
	return 1;
}
