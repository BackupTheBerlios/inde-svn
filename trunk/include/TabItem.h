#ifndef TABITEM_H
#define TABITEM_H

#include <fx.h>
#include "TabEditor.h"

class TabEditor;

/*
	Class: TabItem
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

		TabItem(TabEditor* p, const FXString& text, FXObject* tgt=NULL, FXSelector sel=0);

		virtual void create();

		~TabItem();

};

#endif // TABITEM_H
