#include "InDE.h"

FXDEFMAP(DialogTitle) DialogTitleMap[] = {0,};

FXIMPLEMENT(DialogTitle, FXVerticalFrame, DialogTitleMap, ARRAYNUMBER(DialogTitleMap))

DialogTitle::DialogTitle(FXComposite* p, const FXString& text)
:	FXVerticalFrame(p, LAYOUT_FILL_X|LAYOUT_FIX_HEIGHT|FRAME_NONE, 0, 0, 0, 50, 0, 0, 0, 0, 0, 0)
{
	FXVerticalFrame* frm = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 15, 15, 15, 15);
	frm->setBackColor(FXRGB(255,255,255));
	this->text = new FXLabel(frm, text);
	this->text->setFont(new FXFont(getApp(), "Tahoma", 14));
	this->text->setBackColor(FXRGB(255,255,255));
	bottomLine = new FXHorizontalSeparator(this, LAYOUT_FILL_X|SEPARATOR_LINE);
	this->setBackColor(FXRGB(255,255,255));
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
