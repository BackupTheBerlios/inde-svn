/*
 * InDE - Fast, pragmatic C++ IDE
 * Copyright (C) 2005 	InDE Development Team
 *						see AUTHOR file for more information
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "ProjectSettings.h"

FXIMPLEMENT(ProjectSettings, Settings, NULL, 0)

ProjectSettings::ProjectSettings(const FXString& filename, const FXString& projectname)
:	Settings(filename)
{
	name = projectname;
}

ProjectSettings::~ProjectSettings()
{
}


void ProjectSettings::appendStringValue(const FXString& section, const FXString& key, const FXString& value)
{
	FXString valueOnDisk = getStringValue(section, key);
	setStringValue(section, key, valueOnDisk + SEPARATOR + value);
}
