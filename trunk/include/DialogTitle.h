#ifndef DIALOGTITLE_H
#define DIALOGTITLE_H

#include <fx.h>

/*
	Class: DialogTitle
	
	Can be used as header widget in dialogs
*/
class DialogTitle : public FXVerticalFrame
{
	FXDECLARE(DialogTitle)

	protected:
		DialogTitle() {};
		DialogTitle(const DialogTitle&);
		DialogTitle operator=(const DialogTitle&);

	private:
		FXLabel* text;
		FXHorizontalSeparator* bottomLine;

	public:
		enum {
			ID_SELF = FXVerticalFrame::ID_LAST,
			ID_LAST,
		};

	public:
	
		/*
			Constructor: DialogTitle
		*/
		DialogTitle(FXComposite* p, const FXString& text);
		
		/*
			Function: create
		*/
		virtual void create();
		
		/*
			Destructor: ~DialogTitle
		*/
		virtual ~DialogTitle();

		/*
			Function: getText
			
			Returns:
				FXLabel widget containing the text
		*/
		FXLabel* getText() { return text; }
};

#endif
