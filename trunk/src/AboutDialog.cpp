#include "AboutDialog.h"
#include "DialogTitle.h"

FXDEFMAP(AboutDialog) AboutDialogMap[] = {0,};

FXIMPLEMENT(AboutDialog, FXDialogBox, AboutDialogMap, ARRAYNUMBER(AboutDialogMap))

AboutDialog::AboutDialog(MainWindow* win, const FXString& title)
:	FXDialogBox(win, title, DECOR_ALL, 0, 0, 500)
{
}

void AboutDialog::create()
{
	FXDialogBox::create();
}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::addDeveloper(const FXString& name, const FXString& email, const FXString& title)
{
	Developer dev;
	dev.name = name;
	dev.email = email;
	dev.title = title;
	developers.append(dev);
}

void AboutDialog::addTranslator(const FXString& name, const FXString& email, const FXString& lang)
{
	Translator trans;
	trans.name = name;
	trans.email = email;
	trans.lang = lang;
	translators.append(trans);
}

void AboutDialog::run()
{
	new DialogTitle(this, this->name);

	if (license.length())
	{
		new FXLabel(this, "License: "+license+"\n", NULL, JUSTIFY_HZ_APART);
	}

	if (description.length())
	{
		new FXLabel(this, description+"\n", NULL, JUSTIFY_HZ_APART);
	}

	if (developers.no())
	{
		new FXLabel(this, "Developers:");
		FXText* devText			= new FXText(this, NULL, 0, LAYOUT_FILL_X);
		devText->setEditable(false);
		devText->setBackColor(this->getBackColor());
		devText->setVisibleRows(developers.no()+1);
		for (FXuint index=0; index < developers.no(); index++)
		{
			Developer dev = developers[index];
			FXString ln = dev.name + " <"+ dev.email +"> ("+ dev.title +")\n";
			devText->appendText(ln.text(), ln.length());
		}
	}

	if (translators.no())
	{
		new FXLabel(this, "Translators:");
		FXText* transText		= new FXText(this, NULL, 0, LAYOUT_FILL_X);
		transText->setEditable(false);
		transText->setBackColor(this->getBackColor());
		transText->setVisibleRows(translators.no()+1);
		for (FXuint index=0; index < translators.no(); index++)
		{
			Translator person = translators[index];
			FXString ln = person.lang +": "+ person.name + " <"+ person.email +">\n";
			transText->appendText(ln.text(), ln.length());
		}
	}

	if (copyright.length())
	{
		new FXHorizontalSeparator(this, SEPARATOR_LINE|LAYOUT_FILL_X);
		new FXLabel(this, "Copyright: "+copyright, NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);
	}

	new FXHorizontalSeparator(this, SEPARATOR_LINE|LAYOUT_FILL_X);
  	FXHorizontalFrame* box 	= new FXHorizontalFrame(this, LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
	new FXButton(box, "&Ok", NULL, this, FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 2, 2);

	FXDialogBox::execute(PLACEMENT_SCREEN);
}
