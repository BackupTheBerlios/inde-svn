#include "TabItem.h"

FXDEFMAP(TabItem) TabItemMap[] = {
	FXMAPFUNC(SEL_RIGHTBUTTONRELEASE, 0, TabItem::onRightButtonRelease),
};

FXIMPLEMENT(TabItem, FXTabItem, TabItemMap, ARRAYNUMBER(TabItemMap))


TabItem::TabItem(TabEditor* p, const FXString& text, FXObject* tgt, FXSelector sel)
:	FXTabItem(p, text)
{
	target = tgt;
	message = sel;
}


void TabItem::create()
{	
	FXTabItem::create();
}


TabItem::~TabItem()
{
}


long TabItem::onRightButtonRelease(FXObject* sender, FXSelector sel, void* ptr)
{
	if (target)
	{
		target->tryHandle(this, FXSEL(SEL_RIGHTBUTTONRELEASE, message), ptr);
	}
	return 1;
}
