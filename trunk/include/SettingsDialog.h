#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <fx.h>
#include "MainWindow.h"

class MainWindow;

class SettingsDialog : public FXDialogBox
{
	FXDECLARE(SettingsDialog)
	
	protected:
		SettingsDialog() {};
		SettingsDialog(const SettingsDialog&);
		SettingsDialog& operator=(const SettingsDialog&);
		
	private:
		
	public:
		enum {
			ID_SELECTBASEDIR = FXDialogBox::ID_LAST,
			ID_LAST,
		};
		
	public:
		long onCmdSelectBaseDir(FXObject*, FXSelector, void*);
		
	public:
	
		SettingsDialog(MainWindow* owner, const FXString& title);
		
		virtual void create();
		
		~SettingsDialog();
		
		FXbool check();
};

#endif // SETTINGSDIALOG_H
