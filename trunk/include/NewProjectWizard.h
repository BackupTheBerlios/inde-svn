#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include "InDE.h"

class MainWindow;

//////////////////////////////////////////////////
// new project wizard class

class NewProjectWizard : public FXWizard  {
	FXDECLARE(NewProjectWizard)

	private:
		FXVerticalFrame	*step1;
		FXVerticalFrame	*step2;
		FXVerticalFrame	*step3;
		FXVerticalFrame	*step4;

		// step 1 vars
		FXTextField		*nameField;
		FXText			*descriptionField;
		FXComboBox		*targetBox;
		FXTextField		*versionField;

		// step 2 vars
		FXTextField		*includePathes;
		FXTextField		*libraryPathes;
		FXTextField		*libraries;

		// step 3: pathes
		FXTextField		*srcDir;
		FXTextField		*includeDir;
		FXTextField		*binDir;

		// step 4: compiler options
		FXTextField		*warnings;
		FXTextField		*defines;
		FXTextField		*switches;
		FXCheckButton	*debug;
		FXCheckButton	*pic;

	protected:
		NewProjectWizard() {};
		NewProjectWizard(const NewProjectWizard&);
		NewProjectWizard& operator=(const NewProjectWizard&);

	public:
		enum {
			ID_irgendwas = FXWizard::ID_LAST,
			ID_LAST
		};

	public:
		long onCmdAccept(FXObject*, FXSelector, void*);
		
	public:
	
		// Constructor
		NewProjectWizard(MainWindow* owner, const FXString& name);
		
		// Create
		virtual void create();
		
		// Destructor
		virtual ~NewProjectWizard();

};


#endif // NEWPROJECTWIZARD_H
