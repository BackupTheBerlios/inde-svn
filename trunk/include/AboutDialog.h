#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <fx.h>
#include "MainWindow.h"

struct Developer {
	FXString	name;
	FXString	email;
	FXString	title;
};

struct Translator {
	FXString	name;
	FXString	email;
	FXString	lang;
};


/*
	Class: AboutDialog

	Dialog displaying information about the program.
*/
class AboutDialog : public FXDialogBox
{
	FXDECLARE(AboutDialog)

	protected:
		AboutDialog() {};
		AboutDialog(const AboutDialog&);
		AboutDialog& operator=(const AboutDialog&);

	private:
		FXArray<Developer>		developers;
		FXArray<Translator>		translators;
		FXString				description;
		FXString				license;
		FXString				name;
		FXString				copyright;

	public:
		enum {
			ID_SELF = FXDialogBox::ID_LAST,
			ID_LAST,
		};

	public:

		/*
			Constructor: AboutDialog
		*/
		AboutDialog(MainWindow* win, const FXString& title);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~AboutDialog
		*/
		virtual ~AboutDialog();

		/*
			Function: setCopyright
		*/
		void setCopyright(const FXString& text) { copyright = text; }

		/*
			Function: setProgramName

			Defines the name of the program
		*/
		void setProgramName(const FXString& name) { this->name = name; }

		/*
			Function: setDescription

			Adds a description to the about dialog
		*/
		void setDescription(const FXString& text) { description = text; }

		/*
			Function: setLicense

			Adds a license note to the dialog
		*/
		void setLicense(const FXString& license) { this->license = license; }

		/*
			Function: addTranslator

			Adds a translator to the displayed list.

			Parameters:
				name - Full name of the translator
				email - E-Mail address
				lang - String like "English" or "German"
		*/
		void addTranslator(const FXString& name, const FXString& email, const FXString& lang);

		/*
			Function: addDeveloper

			Adds a developer to the displayed list

			Parameters:
				name - Full name
				email - E-Mail-Address of the developer
				title - Title like "Head developer" and/or tasks he is mainly working on
		*/
		void addDeveloper(const FXString& name, const FXString& email, const FXString& title);

		/*
			Function: run

			Creates content and shows the dialog
		*/
		void run();
};

#endif
