#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <fx.h>

struct ProjectGeneralSettings {
	FXString	type;
	FXString	name;
	FXString	description;
	FXString	target;
	FXString	version;
	FXString	author;
	FXString	mail;
	FXint		license;
	FXString	licenseHeader;
};

struct ProjectLibrarySettings {
	FXString	includePaths;
	FXString	libraryPaths;
	FXString	libraries;
};

struct ProjectDirectorySettings {
	FXString	source;
	FXString	include;
	FXString	build;
};

struct ProjectCompilerSettings {
	FXString	warnings;
	FXString	defines;
	FXString	switches;
	FXbool		debug;
	FXbool		pic;
};

struct ProjectSettings {
	ProjectGeneralSettings		general;
	ProjectLibrarySettings		libraries;
	ProjectDirectorySettings	directories;
	ProjectCompilerSettings		compiler;
};

#endif // PROJECTSETTINGS_H
