#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <fx.h>


/*
	Class: ProjectSettings

	Provides abilities to:
	- Parse and write settings from/to a file
	- Store and retrieve values depending on key and section
	- Define default values for a key
	- Fill missing values with defaults
	- Replace all values with defaults
*/
class ProjectSettings : public FXSettings
{
	FXDECLARE(ProjectSettings)

	protected:
		ProjectSettings() {};

	private:
		FXString		file;
		FXSettings*		defaultDict;
		FXString		name;

	public:

	public:

		/*
			Constructor: ProjectSettings

			Parameters:
				filename - File to parse from and write to
		*/
		ProjectSettings(const FXString& filename, const FXString& projectname);

		virtual ~ProjectSettings();

		FXString getProjectName() { return name; }
		/*
			Function: parse

			Parses the settings file

			- Creates settings file if it doesn't already exist
			  and writes default values to it
			- Parses the settings file
			- Fills missing values with defaults
		*/
		void parse();

		void unparse();

		/*
			Function: defaults

			Method to either fill missing values or to replace all
			values with defaults

			Parameters:
				replace - Replace existing values
		*/
		void defaults(FXbool replace=true);

		/*
			Function: write

			Writes settings to the file
		*/
		void write();


		/*
			Function: getStringValue

			Returns string value of a key in section "GENERAL"
		*/
		const FXchar* getStringValue(const FXString& key);

		/*
			Function: getStringValue

			Returns string value of a given key in a section
		*/
		const FXchar* getStringValue(const FXString& section, const FXString& key);

		/*
			Function: getIntValue

			Returns integer value of a key in section "GENERAL"
		*/
		FXint getIntValue(const FXString& key);

		/*
			Function: getIntValue

			Returns integer value of a key in a section
		*/
		FXint getIntValue(const FXString& section, const FXString& key);

		/*
			Function: setStringValue

			Defines a string value for a key in "GENERAL"
		*/
		void setStringValue(const FXString& key, const FXString& value);

		/*
			Function: setStringValue

			Defines a string value for a key in a section
		*/
		void setStringValue(const FXString& section, const FXString& key, const FXString& value);

		/*
			Function: setIntValue

			Defines an integer value for a key in "GENERAL"
		*/
		void setIntValue(const FXString& key, FXint value);

		/*
			Function: setIntValue

			Defines an integer value for a key in a section
		*/
		void setIntValue(const FXString& section, const FXString& key, FXint value);
		
		/*
			Function: setFormatValue
		*/
		void setFormatValue(const FXString& key, const FXchar* format, ...);
		
		/*
			Function: setFormatValue
		*/
		void setFormatValue(const FXString& section, const FXString& key, const FXchar* format, ...);
		
		/*
			Function: getFormatValue
		*/
		FXint getFormatValue(const FXString& key, const FXchar* format, ...);
		
		/*
			Function: getFormatValue
		*/
		FXint getFormatValue(const FXString& section, const FXString& key, const FXchar* format, ...);

};


#endif // PROJECTSETTINGS_H
