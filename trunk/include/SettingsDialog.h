#include "InDE.h"

struct InDESettings;	// Defined in MainWindow.h


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
		InDESettings*		settings;
	
	public:
		enum {
			ID_ACCEPT = FXDialogBox::ID_LAST,
			ID_LAST,
		};
		
	public:
		long onCmdAccept(FXObject*, FXSelector, void*);
		
	public:
	
		// Constructor
		SettingsDialog(FXWindow* p, InDESettings* settings, const FXString& name);
		
		// Create
		virtual void create();
		
		// Destructor
		virtual ~SettingsDialog();
};
