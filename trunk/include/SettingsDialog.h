#include "InDE.h"

class MainWindow;


//////////////////////////////////////////////////
// InDE settings dialog class

class SettingsDialog : public FXDialogBox
{
	FXDECLARE(SettingsDialog)
	
	protected:
		SettingsDialog() {};
		SettingsDialog(const SettingsDialog&);
		SettingsDialog& operator=(const SettingsDialog&);
	
	private:
		DialogTitle*		title;
		FXTextField*		inputBaseDir;
	
	public:
		enum {
			ID_ACCEPT = FXDialogBox::ID_LAST,
			ID_SELECTBASEDIR,
			ID_LAST,
		};
		
	public:
		long onCmdAccept(FXObject*, FXSelector, void*);
		long onCmdSelectBaseDir(FXObject*, FXSelector, void*);
		
	public:
	
		// Constructor
		SettingsDialog(MainWindow* owner, const FXString& name);
		
		// Create
		virtual void create();
		
		// Destructor
		virtual ~SettingsDialog();
};
