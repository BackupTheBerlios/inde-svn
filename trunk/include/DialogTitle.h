#ifndef DIALOGTITLE_H
#define DIALOGTITLE_H

#include "InDE.h"


//////////////////////////////////////////////////
// DialogTitle class

class DialogTitle : public FXVerticalFrame
{
	FXDECLARE(DialogTitle)
	
	protected:
		DialogTitle() {};
		DialogTitle(const DialogTitle&);
		DialogTitle operator=(const DialogTitle&);
	
	public:
		DialogTitle(FXComposite* p, const FXString& text);
		virtual void create();
		virtual ~DialogTitle();
	
	private:
		FXLabel* text;
		FXHorizontalSeparator* bottomLine;
	
	public:
		enum {
			ID_SELF = FXVerticalFrame::ID_LAST,
			ID_LAST,
		};
};

#endif
