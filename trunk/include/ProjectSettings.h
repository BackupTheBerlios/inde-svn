#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include "InDE.h"


//////////////////////////////////////////////////
// project settings structs

struct ProjectGeneralSettings {
	FXString	name;
	FXString	description;
	FXString	target;
	FXString	version;
};

struct ProjectLibrarySettings {
	FXString	includePathes;
	FXString	libraryPathes;
	FXString	libraries;
};

struct ProjectDirectorySettings {
	FXString	srcDir;
	FXString	includeDir;
	FXString	binDir;
};

struct ProjectCompilerSettings {
	FXString	warnings;
	FXString	definings;
	FXString	additionalSwitches;
	FXbool		debug;
	FXbool		pic;
};

struct ProjectSettings {
	ProjectGeneralSettings		general;
	ProjectLibrarySettings		libs;
	ProjectDirectorySettings	dirs;
	ProjectCompilerSettings		compiler;
};


#endif // PROJECTSETTINGS_H
