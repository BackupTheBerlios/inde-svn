#ifndef TABITEM_H
#define TABITEM_H

#include <fx.h>
#include "TabEditor.h"

class TabEditor;

/*
	Class: TabItem
	
	FXTabItem enhanced by the ability to send messages to a target
*/
class TabItem : public FXTabItem
{
	FXDECLARE(TabItem)

	protected:
		TabItem() {};
		TabItem(const TabItem&);
		TabItem& operator=(const TabItem&);

	public:
		enum {
			ID_LAST = FXTabItem::ID_LAST,
		};

	public:
		long onRightButtonRelease(FXObject*, FXSelector, void*);

	public:

		/*
			Constructor: TabItem
		*/
		TabItem(TabEditor* p, const FXString& text, FXObject* tgt=NULL, FXSelector sel=0);

		/*
			Function: create
		*/
		virtual void create();

		/*
			Destructor: ~TabItem
		*/
		~TabItem();

};

#endif // TABITEM_H
