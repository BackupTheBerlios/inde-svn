#ifndef CTAGHANDLE_H
#define CTAGHANDLE_H

#include <fstream>
#include <fx.h>

/*
	Class: CtagHandle
	
	Class to write, read, parse and query an Exhuberant Ctags file.
*/
class CtagHandle : public FXObject
{
	FXDECLARE(CtagHandle)
	
	protected:
		CtagHandle(const CtagHandle&);
		CtagHandle& operator=(const CtagHandle);
	
	private:
		FXString			filename;
	
	public:

		/*
			Constructor: CtagHandle
		*/
		CtagHandle();	
		
		/*
			Function: create
		*/
		virtual void create();
		
		/*
			Destructor: ~CtagHandle
		*/
		virtual ~CtagHandle();
};

#endif
