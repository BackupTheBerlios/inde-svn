#include "FileSystem.h"

FXString FS::dirSeparator()
{
	#ifdef WIN32
		return FXString("\\");
	#else
		return FXString("/");
	#endif
}

FXString FS::hiddenName(const FXString& str)
{
	#ifdef WIN32
		return str;
	#else
		return FXString(".") + str;
	#endif
}

FXString FS::configFilename(const FXString& str)
{
	#ifdef WIN32
		return str + FXString(".ini");
	#else
		return str;
	#endif
}
