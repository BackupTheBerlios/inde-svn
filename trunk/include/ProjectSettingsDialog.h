#ifndef PROJECTSETTINGSDIALOG_H
#define PROJECTSETTINGSDIALOG_H

#include <fx.h>
#include "MainWindow.h"

class MainWindow;

class ProjectSettingsDialog : public FXDialogBox
{
	FXDECLARE(ProjectSettingsDialog)
	
	protected:
		ProjectSettingsDialog() {};
		ProjectSettingsDialog(const ProjectSettingsDialog&);
		ProjectSettingsDialog& operator=(const ProjectSettingsDialog&);
		
	private:
		
	public:
		enum {
			ID_SELECTLICENSEFILE = FXDialogBox::ID_LAST,
			ID_LAST,
		};
		
	public:
		long onCmdSelectLicenseHeader(FXObject*, FXSelector, void*);
		
	public:
	
		ProjectSettingsDialog(MainWindow* owner, const FXString& title);
		
		virtual void create();
		
		~ProjectSettingsDialog();
		
		FXbool check();
};

#endif // PROJECTSETTINGSDIALOG_H
