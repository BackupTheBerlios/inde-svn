#include "Edit.h"

FXDEFMAP(Edit) EditMap[] = {0,};

FXIMPLEMENT(Edit, FXText, EditMap, ARRAYNUMBER(EditMap))


Edit::Edit(FXComposite* p, FXObject* tgt, FXSelector sel, FXuint opts)
:	FXText(p, tgt, sel, opts),
	filename("Untitled"),
	syntax(NULL)
{
	modified = false;
}


void Edit::create()
{
	FXText::create();
}


Edit::~Edit()
{
}


void Edit::setFilename(const FXString& file)
{
	filename = file;
	if (title)
	{
		title->setText(FXFile::name(filename));
	}
}


void Edit::setTitleTab(FXTabItem* tab)
{
	title = tab;
	title->setText(FXFile::name(filename));
}


void Edit::setModified(FXbool flag)
{
	FXTRACE((1, "Edit::setModified(%i)\n", flag));
	if (modified)
	{
		FXTRACE((1, "modified ->"));
		if (!flag)
		{
			FXTRACE((1, " not modified"));
			FXString text = title->getText();
			text.substitute("*", "");
			title->setText(text);
		}
		FXTRACE((1, "\n"));
	}
	else
	{
		FXTRACE((1, "not modified ->"));
		if (flag)
		{
			FXTRACE((1, " modified"));
			title->setText(title->getText() + "*");
		}
		FXTRACE((1, "\n"));
	}
	modified = flag;
}

void Edit::setSyntax(FXSyntax* syn)
{
	syntax = syn;
}
