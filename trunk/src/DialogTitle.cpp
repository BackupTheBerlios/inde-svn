#include "DialogTitle.h"

FXDEFMAP(DialogTitle) DialogTitleMap[] = {0,};

FXIMPLEMENT(DialogTitle, FXVerticalFrame, DialogTitleMap, ARRAYNUMBER(DialogTitleMap))

DialogTitle::DialogTitle(FXComposite* p, const FXString& text)
:	FXVerticalFrame(p, LAYOUT_FILL_X|FRAME_NONE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
	this->text = new FXLabel(this, text);
	this->text->setFont(new FXFont(getApp(), "Tahoma", 12));
	bottomLine = new FXHorizontalSeparator(this, LAYOUT_FILL_X|SEPARATOR_LINE);
	new FXFrame(this, LAYOUT_FILL_X|FRAME_NONE|LAYOUT_FIX_HEIGHT, 0, 0, 0, 15);
}

void
DialogTitle::create()
{
	FXVerticalFrame::create();
}

DialogTitle::~DialogTitle()
{
	delete text;
	delete bottomLine;
}
