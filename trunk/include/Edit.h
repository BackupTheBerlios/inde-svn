#ifndef EDIT_H
#define EDIT_H

#include <fx.h>
#include "Hilite.h"

/*
	Class: Edit

	Enhanced FXText.
	Is connected to a <TabItem> which displays its filename.
*/
class Edit : public FXText
{
	FXDECLARE(Edit)

	protected:
		Edit() {};
		Edit(const Edit&);
		Edit& operator=(const Edit&);

	private:
		FXString		filename;
		FXTabItem*		title;
		FXSyntax*		syntax;
		FXbool			modified;

	public:
		enum {
			ID_SELF = FXText::ID_LAST,
			ID_LAST,
		};

	public:

	public:

		/*
			Constructor: Edit
		*/
		Edit(FXComposite* p, FXObject* tgt=NULL, FXSelector sel=0, FXuint opts=LAYOUT_FILL_X|LAYOUT_FILL_Y);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~Edit
		*/
		~Edit();

		/*
			Function: setFilename
		*/
		void setFilename(const FXString& file);

		/*
			Function: getFilename

			Returns:
				Filename of document
		*/
		FXString& getFilename() { return filename; }

		/*
			Function: setTitleTab
			
			Passes pointer to the TabItem displaying the filename
		*/
		void setTitleTab(FXTabItem* tab);

		/*
			Function: setModified
		*/
		void setModified(FXbool flag=true);

		/*
			Function: isModified
		*/
		FXbool isModified() { return modified; }

		/*
			Function: setSyntax

			Defines <FXSyntax> used for highlighting the document content
		*/
		void setSyntax(FXSyntax* syn);

		/*
			Function: getSyntax

			Returns:
				Syntax currently used for highlighting the document content
		*/
		FXSyntax* getSyntax() { return syntax; }

};

#endif // EDIT_H
