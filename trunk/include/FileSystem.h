#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <fx.h>

/*
	Namespace: FS
	
	Namespace including methods for the use in cases where distinguishing
	between platforms is of importance.
*/
namespace FS
{

	/* 
		Function: dirSeparator
		
		Returns the directory seperator.
		
		Returns:
			- Windows: \\
			- Linux: /
	*/
	FXString dirSeparator();
	
	/*
		Function: hiddenName
		
		Returns name of hidden file/directory with name *str*
		
		Returns:
			- Windows: *str*
			- Linux: *.str*
	*/
	FXString hiddenName(const FXString& str);
	
	/*
		Function: configFilename
		
		Appends config file suffix to given filename 
		
		Returns:
			- Windows: *str.ini*
			- Linux: *str*
	*/
	FXString configFilename(const FXString& str);

}

#endif
