#include "Settings.h"

FXIMPLEMENT(Settings, FXSettings, NULL, 0)

Settings::Settings(const FXString& filename)
:	FXSettings()
{
	file = filename;
	defaultDict = new FXSettings;
}

Settings::~Settings()
{
	delete defaultDict;
}

void Settings::parse()
{
	FXTRACE((1, "Settings::parse()\n"));
	if (!FXFile::exists(FXFile::directory(file)))
	{
		FXTRACE((1, "Settings::parse(): Creating directory ~/.InDE\n"));
		FXFile::createDirectory(FXFile::directory(file), 0775);
	}
	if (!FXFile::exists(file))
	{
		FXTRACE((1, "Settings::parse(): Creating user file\n"));
		FXFile::createFile(file, 0664);
		defaults();
		write();
	}
	parseFile(file, true);
	defaults(false);
}

void Settings::defaults(FXbool replace)
{
	FXTRACE((1, "Settings::defaults(%i)\n", replace));

	FXint index, pos;
	FXDict* dict;
	for (index = defaultDict->first(); index < defaultDict->size(); index = defaultDict->next(index))
	{
		// FXTRACE((1, "[%s]\n", defaultDict->key(index)));
		dict = defaultDict->data(index);
		for (pos = dict->first(); pos < dict->size(); pos = dict->next(pos))
		{
			// FXTRACE((1, "%s=%s\n", dict->key(pos), dict->data(pos)));

			if (existingEntry(defaultDict->key(index), dict->key(pos)))
			{
				if (replace)
				{
					FXTRACE((1, "Replacing [%s]->%s=%s with %s\n", defaultDict->key(index), dict->key(pos), readStringEntry(defaultDict->key(index), dict->key(pos)), dict->data(pos)));
					writeStringEntry(defaultDict->key(index), dict->key(pos), (FXchar*)dict->data(pos));
				}
			}
			else
			{
				FXTRACE((1, "Setting [%s]->%s to %s\n", defaultDict->key(index), dict->key(pos), dict->data(pos)));
				writeStringEntry(defaultDict->key(index), dict->key(pos), (FXchar*)dict->data(pos));
			}
		}
	}
}

void Settings::write()
{
	FXTRACE((1, "Settings::write()\n"));
	unparseFile(file);
}

void Settings::setDefault(const FXString& key, const FXString& val)
{
	setDefault("GENERAL", key, val);
}

void Settings::setDefault(const FXString& section, const FXString& key, const FXString& val)
{
	FXTRACE((1, "Settings::setDefault(%s, %s, %s)\n", section.text(), key.text(), val.text()));
	defaultDict->writeStringEntry(section.text(), key.text(), val.text());
}

void Settings::setDefault(const FXString& key, FXint val)
{
	setDefault("GENERAL", key, val);
}

void Settings::setDefault(const FXString& section, const FXString& key, FXint val)
{
	FXTRACE((1, "Settings::setDefault(%s, %s, %i)\n", section.text(), key.text(), val));
	defaultDict->writeIntEntry(section.text(), key.text(), val);
}

const FXchar* Settings::getStringValue(const FXString& key)
{
	return readStringEntry("GENERAL", key.text());
}

const FXchar* Settings::getStringValue(const FXString& section, const FXString& key)
{
	return readStringEntry(section.text(), key.text());
}

FXint Settings::getIntValue(const FXString& key)
{
	return readIntEntry("GENERAL", key.text());
}

FXint Settings::getIntValue(const FXString& section, const FXString& key)
{
	return readIntEntry(section.text(), key.text());
}

void Settings::setStringValue(const FXString& key, const FXString& value)
{
	setStringValue("GENERAL", key, value);
}

void Settings::setStringValue(const FXString& section, const FXString& key, const FXString& value)
{
	FXTRACE((1, "Settings::setStringValue(%s, %s, %s)\n", section.text(), key.text(), value.text()));
	writeStringEntry(section.text(), key.text(), value.text());
}

void Settings::setIntValue(const FXString& key, FXint value)
{
	setIntValue("GENERAL", key, value);
}

void Settings::setIntValue(const FXString& section, const FXString& key, FXint value)
{
	FXTRACE((1, "Settings::setIntValue(%s, %s, %i)\n", section.text(), key.text(), value));
	writeIntEntry(section.text(), key.text(), value);
}

void Settings::setFormatValue(const FXString& key, const FXchar* format, ...)
{
	if (!format)
	{
		fxerror("FXSettings::writeFormatEntry: bad fmt argument.\n");
	}
	FXStringDict* group = insert("GENERAL");
	va_list args;
	va_start(args, format);
	FXint result = 0;
	if (group)
	{
		FXchar buffer[2000];
#if defined(WIN32) || defined(HAVE_VSNPRINTF)
		result = vsnprintf(buffer, sizeof(buffer), format, args);
#else
		result = vsprintf(buffer, format, args);
#endif
		group->replace(key.text(), buffer, TRUE);
		modified = TRUE;
	}
	va_end(args);
	return;
}

void Settings::setFormatValue(const FXString& section, const FXString& key, const FXchar* format, ...)
{
	if (!format)
	{
		fxerror("FXSettings::writeFormatEntry: bad fmt argument.\n");
	}
	FXStringDict* group = insert(section.text());
	va_list args;
	va_start(args, format);
	FXint result = 0;
	if (group)
	{
		FXchar buffer[2000];
#if defined(WIN32) || defined(HAVE_VSNPRINTF)
		result = vsnprintf(buffer, sizeof(buffer), format, args);
#else
		result = vsprintf(buffer, format, args);
#endif
		group->replace(key.text(), buffer, TRUE);
		modified = TRUE;
	}
	va_end(args);
	return;
}

FXint Settings::getFormatValue(const FXString& key, const FXchar* format, ...)
{
	if (!format)
	{
		fxerror("FXSettings::readFormatEntry: bad fmt argument.\n");
	}
	FXStringDict *group = find("GENERAL");
	va_list args;
	va_start(args, format);
	FXint result = 0;
	if (group)
	{
    	const char* value = group->find(key.text());
		if (value)
		{
			result = vsscanf((char*)value, format, args);
		}
	}
	va_end(args);
	return result;
}

FXint Settings::getFormatValue(const FXString& section, const FXString& key, const FXchar* format, ...)
{
	if (!format)
	{
		fxerror("FXSettings::readFormatEntry: bad fmt argument.\n");
	}
	FXStringDict *group = find(section.text());
	va_list args;
	va_start(args, format);
	FXint result = 0;
	if (group)
	{
    	const char* value = group->find(key.text());
		if (value)
		{
			result = vsscanf((char*)value, format, args);
		}
	}
	va_end(args);
	return result;
}


void Settings::setColorValue(const FXString& key, FXColor value)
{
	setColorValue("GENERAL", key, value);
}

void Settings::setColorValue(const FXString& section, const FXString& key, FXColor value)
{
	FXTRACE((1, "Settings::setColorValue(%s, %s, %i)\n", section.text(), key.text(), value));
	writeColorEntry(section.text(), key.text(), value);
}

void Settings::setDefaultColor(const FXString& key, FXColor value)
{
	setDefaultColor("GENERAL", key, value);
}

void Settings::setDefaultColor(const FXString& section, const FXString& key, FXColor value)
{
	FXTRACE((1, "Settings::setDefault(%s, %s, %i)\n", section.text(), key.text(), -value));
	defaultDict->writeColorEntry(section.text(), key.text(), value);
}

FXColor Settings::getColorValue(const FXString& key)
{
	return getColorValue("GENERAL", key);
}

FXColor Settings::getColorValue(const FXString& section, const FXString& key)
{
	return readColorEntry(section.text(), key.text());
}
