#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <fx.h>

namespace FS
{

	FXString dirSeparator();
	FXString hiddenName(const FXString& str);
	FXString configFilename(const FXString& str);

}

#endif
