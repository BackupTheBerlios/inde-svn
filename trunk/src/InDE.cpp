#include "InDE.h"

FXDEFMAP(InDE) InDEMap[] = {
	0,
};

FXIMPLEMENT(InDE, FXApp, InDEMap, ARRAYNUMBER(InDEMap))

InDE::InDE(const FXString& appKey, const FXString& vendorKey)
:	FXApp(appKey, vendorKey)
{
#ifndef DEBUG
/*
	addSignal(SIGINT,	this,	ID_CLOSEALL);
	addSignal(SIGQUIT,	this,	ID_CLOSEALL);
	addSignal(SIGHUP,	this,	ID_CLOSEALL);
	addSignal(SIGPIPE,	this,	ID_CLOSEALL);
*/
#endif
}

void InDE::create()
{
	FXApp::create();
}

InDE::~InDE()
{
}
