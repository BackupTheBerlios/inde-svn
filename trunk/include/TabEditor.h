#ifndef TABEDITOR_H
#define TABEDITOR_H

#include <fx.h>
#include "Edit.h"
#include "MainWindow.h"
#include "SyntaxParser.h"

class MainWindow;

/*
	Class: TabEditor

	Tab-based document editor as known from many enhanced editors like
	Anjuta or browsers like Firefox.
*/
class TabEditor : public FXTabBook
{
	FXDECLARE(TabEditor)

	protected:
		TabEditor() {};
		TabEditor(const TabEditor&);
		TabEditor& operator=(const TabEditor&);

	private:
		FXMenuPane* 		tabMenu;
		FXString			font;
		MainWindow*			mainWin;

		SyntaxParser*		syntaxParser;
		FXString			syntaxFile;
		FXSyntaxList		syntaxes;
		FXHiliteArray		styles;

		FXbool				lineNumbersShown;

	public:
		enum {
			ID_TAB_MENU = FXTabBook::ID_LAST,

			ID_DOCUMENT,

			ID_NEW,
			ID_CLOSE,
			ID_CLOSE_OTHERS,
			ID_CLOSE_ALL,

			ID_LAST,
		};

	public:
		long onTabMenu(FXObject*, FXSelector, void*);
		long onMenuCmd(FXObject*, FXSelector, void*);
		long onTextInserted(FXObject*, FXSelector, void*);
		long onTextReplaced(FXObject*, FXSelector, void*);
		long onTextChanged(FXObject*, FXSelector, void*);
		long onTextDeleted(FXObject*, FXSelector, void*);

	public:

		/*
			Constructor: TabEditor
		*/
		TabEditor(FXComposite* p, MainWindow* win, FXObject* tgt=NULL, FXSelector sel=0, FXuint opts=LAYOUT_FILL_X|LAYOUT_FILL_Y);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~TabEditor
		*/
		virtual ~TabEditor();

		/*
			Function: openFile

			Opens a file in a new tab

			Returns:
				Whether opening succeeded or failed
		*/
		FXbool openFile(const FXString& filename);

		void appendDocument(const FXString& filename, const FXString& content);

		/*
			Function: appendDocument

			Appends an empty and untitled document
		*/
		void appendDocument();

		/*
			Function: setFont

			Sets the editor font for all opened documents
		*/
		void setFont(const FXString& font);

		/*
			Function: getFont

			Returns:
				Current editor font
		*/
		FXString& getFont() { return font; }

		/*
			Function: saveDocument

			Saves document at given index
		*/
		FXbool saveDocument(FXuint index);

		/*
			Function: saveDocument

			Saves current document
		*/
		FXbool saveDocument();

		/*
			Function: documentAt

			Returns:
				<Edit> widget of document at given index
		*/
		Edit* documentAt(FXuint index);

		/*
			Function: lastDocument

			Returns:
				<Edit> widget of last document
		*/
		Edit* lastDocument();

		/*
			Function: closeDocument

			Closes (and saves) document at a given index
		*/
		FXbool closeDocument(FXuint index);

		/*
			Function: closeDocument

			Closes (and saves) current file
		*/
		FXbool closeDocument();

		/*
			Function: closeAll

			Closes (and saves) all opened documents
		*/
		FXbool closeAll();

		/*
			Function: saveAll

			Saves all opened documents
		*/
		FXbool saveAll();

		/*
			Function: saveDocumentAs

			Saves document at given index under a different name

			Returns:
				Whether the document was saved or not
		*/
		FXbool saveDocumentAs(FXuint index);

		/*
			Function: saveDocumentAs

			Saves current document under a different name

			Returns:
				Whether the document was saved or not
		*/
		FXbool saveDocumentAs();

		/*
			Function: setSyntaxFile

			Sets syntax file for the editor to use when determining document
			syntax and highlighting the document content
		*/
		void setSyntaxFile(const FXString& filename);

		/*
			Function: loadSyntaxFile

			Parses the syntax file
		*/
		void loadSyntaxFile();

		/*
			Function: getSyntaxParser

			Returns:
				SyntaxParser object used by the editor
		*/
		SyntaxParser* getSyntaxParser();

		/*
			Function: determineSyntax

			Automatically determines syntax rules for document
			at given index
		*/
		void determineSyntax(FXuint index);

		/*
			Function: setSyntax

			Set syntax rules for document at given index
		*/
		void setSyntax(FXuint index, FXSyntax* syn);

		/*
			Function: readStyleForRule
		*/
		FXHiliteStyle readStyleForRule(const FXString& name);

		/*
			Function: restyleDocument

			Restyle document at given index
		*/
		void restyleDocument(FXuint index);

		/*
			Function: showLineNumbers

			Display line numbers or not
		*/
		void showLineNumbers(FXbool flag=true);

		/*
			Function: showNextTab
			
			Switches to the next tab. Displays first tab if current
			tab is the last one.
		*/
		void showNextTab();

		/*
			Function: showPreviousTab()
		*/
		void showPreviousTab();

		/*
			Function: applySettings

			Reads settings from MainWindow object and applies
			them to all opened documents
		*/
		void applySettings();

		/*
			Function: applySettingsTo
			
			Reads settings from MainWindow object and applies
			them to document at given index
		*/
		void applySettingsTo(FXuint index);
};

#endif
