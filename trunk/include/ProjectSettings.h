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

#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <fx.h>
#include "Settings.h"


/*
	Class: ProjectSettings

	Provides abilities to:
	- Parse and write settings from/to a file
	- Store and retrieve values depending on key and section
	- Define default values for a key
	- Fill missing values with defaults
	- Replace all values with defaults
*/
class ProjectSettings : public Settings
{
	FXDECLARE(ProjectSettings)

	protected:
		ProjectSettings() {};

	private:
		FXString		name;

	public:
		static const FXchar SEPARATOR = ',';

	public:

		/*
			Constructor: ProjectSettings

			Parameters:
				filename - File to parse from and write to
		*/
		ProjectSettings(const FXString& filename, const FXString& projectname);

		/*
			Destructor: ~ProjectSettings
		*/
		virtual ~ProjectSettings();

		/*
			Function: getProjectName
		*/
		FXString getProjectName() { return name; }

		/*
			Function: appendStringValue

			Appends a String value to an existing String value
		*/
		void appendStringValue(const FXString& section, const FXString& key, const FXString& value);

};


#endif // PROJECTSETTINGS_H
