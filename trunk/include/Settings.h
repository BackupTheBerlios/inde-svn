#ifndef SETTINGS_H
#define SETTINGS_H

#include <fx.h>

/*
	Class: Settings

	Provides abilities to:
	- Parse and write settings from/to a file
	- Store and retrieve values depending on key and section
	- Define default values for a key
	- Fill missing values with defaults
	- Replace all values with defaults
*/
class Settings : public FXSettings
{
	FXDECLARE(Settings)

	protected:
		Settings() {};

	protected:
		FXString		file;
		FXSettings*		defaultDict;

	public:

	public:

		/*
			Constructor: Settings

			Parameters:
				filename - File to parse from and write to
		*/
		Settings(const FXString& filename);

		virtual ~Settings();

		/*
			Function: parse

			Parses the settings file

			- Creates settings file if it doesn't already exist
			  and writes default values to it
			- Parses the settings file
			- Fills missing values with defaults
		*/
		void parse();

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
			Function: setDefault

			Defines a default string value for a key in section "GENERAL"
		*/
		void setDefault(const FXString& key, const FXString& value);

		/*
			Function: setDefault

			Defines a default string value for a key in a section
		*/
		void setDefault(const FXString& section, const FXString& key, const FXString& value);

		/*
			Function: setDefault

			Defines a default integer value for a key in section "GENERAL"
		*/
		void setDefault(const FXString& key, FXint value);

		/*
			Function: setDefault

			Defines a default integer value for a key in a section
		*/
		void setDefault(const FXString& key, const FXString& section, FXint value);

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

		/*
			Function: setColorValue

			Defines color value for a key in section "GENERAL"
		*/
		void setColorValue(const FXString& key, FXColor value);

		/*
			Function: setColorValue
			
			Defines color value for a key in a section
		*/
		void setColorValue(const FXString& section, const FXString& key, FXColor value);

		/*
			Function: getColorValue
			
			Returns a color of key in section "GENERAL"
		*/
		FXColor getColorValue(const FXString& key);

		/*
			Function: getColorValue
			
			Returns a color of key in a section
		*/
		FXColor getColorValue(const FXString& section, const FXString& key);

		/*
			Function: setDefaultColor

			Same as <setDefault> for integers or strings but required a different name
			due to the difference analogy of FXColor=FXuint to FXint
		*/
		void setDefaultColor(const FXString& key, FXColor value);

		/*
			Function: setDefaultColor
			
			Same as <setDefault> for integers or strings but required a different name
			due to the difference analogy of FXColor=FXuint to FXint
		*/
		void setDefaultColor(const FXString& section, const FXString& key, FXColor value);

};

#endif // SETTINGS_H
