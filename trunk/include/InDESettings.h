#ifndef INDESETTINGS_H
#define INDESETTINGS_H

#include "InDE.h"


//////////////////////////////////////////////////
// InDE settings structs


struct GeneralSettings
{
	FXString			baseDir;
	FXuint				numRecentProjects;
	FXuint				numRecentFiles;
	FXbool				autoLoadLastProject;
};


struct SavingSettings
{
	FXbool				saveOnTabSwitch;
	FXbool				autosave;
	FXuint				autosaveInterval;
	FXbool				backupOnSave;
	FXString			backupSuffix;
};


struct InDESettings {
	GeneralSettings		general;
	SavingSettings		saving;
};

#endif
