#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <fx.h>
#include "MainWindow.h"

class MainWindow;

/*
	Class: SettingsDialog
*/
class SettingsDialog : public FXDialogBox
{
	FXDECLARE(SettingsDialog)

	protected:
		SettingsDialog() {};
		SettingsDialog(const SettingsDialog&);
		SettingsDialog& operator=(const SettingsDialog&);

	public:
		FXString		baseDir;
		FXbool			loadProject;

		FXbool			saveOnTabSwitch;
		FXbool			autosave;
		FXuint			autosaveInterval;
		FXbool			backupOnSave;
		FXString		backupSuffix;

		FXString		font;
		FXString		syntaxFile;
		FXbool			lineNumbers;

		FXColor			backColor;
		FXColor			foreColor;
		FXColor			numberColor;
		FXColor			barColor;

	private:
		FXDataTarget	tgtBaseDir;
		FXDataTarget	tgtLoadProject;

		FXDataTarget	tgtFont;
		FXDataTarget	tgtSyntaxFile;
		FXDataTarget	tgtLineNumbers;

		FXDataTarget	tgtBackColor;
		FXDataTarget	tgtForeColor;
		FXDataTarget	tgtNumberColor;
		FXDataTarget	tgtBarColor;

	private:
		FXSwitcher*		switcher;

	public:
		enum {
			ID_SELECT_BASEDIR = FXDialogBox::ID_LAST,
			ID_SELECT_FONT,
			ID_SELECT_SYNTAXFILE,
			ID_LAST,
		};

	public:
		long onSelectBaseDir(FXObject*, FXSelector, void*);
		long onSelectFont(FXObject*, FXSelector, void*);
		long onSelectSyntaxFile(FXObject*, FXSelector, void*);

	public:

		SettingsDialog(MainWindow*, const FXString&);

		virtual void create();

		virtual ~SettingsDialog();

		virtual FXbool check();

		MainWindow* getOwner() { return (MainWindow*)FXDialogBox::getOwner(); }

		void loadValues();

		void storeValues();

		void run();
};

#endif // SETTINGSDIALOG_H
