#include "ProjectSettings.h"

FXIMPLEMENT(ProjectSettings, FXSettings, NULL, 0)

ProjectSettings::ProjectSettings(const FXString& filename, const FXString& projectname)
:	FXSettings()
{
	file = filename;
	defaultDict = new FXSettings;
	name = projectname;
}

ProjectSettings::~ProjectSettings()
{
	delete defaultDict;
}


void ProjectSettings::parse()
{
	FXTRACE((1, "ProjectSettings::parse()\n"));
	if (!FXFile::exists(FXFile::directory(file)))
	{
		FXTRACE((1, "ProjectSettings::parse(): Creating directory ~/.InDE\n"));
		FXFile::createDirectory(FXFile::directory(file), 0777);
	}
	if (!FXFile::exists(file))
	{
		FXTRACE((1, "ProjectSettings::parse(): Creating user file\n"));
		FXFile::createFile(file, 0777);
		defaults();
		write();
	}
	parseFile(file, true);
	defaults(false);
}

void ProjectSettings::defaults(FXbool replace)
{
	FXTRACE((1, "ProjectSettings::defaults(%i)\n", replace));

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

void ProjectSettings::write()
{
	FXTRACE((1, "ProjectSettings::write()\n"));
	unparseFile(file);
}

void ProjectSettings::unparse()
{
	unparseFile(file);
}

/*void ProjectSettings::setDefault(const FXString& key, const FXString& val)
{
	setDefault("GENERAL", key, val);
}*/

/*void ProjectSettings::setDefault(const FXString& section, const FXString& key, const FXString& val)
{
	FXTRACE((1, "Settings::setDefault(%s, %s, %s)\n", section.text(), key.text(), val.text()));
	defaultDict->writeStringEntry(section.text(), key.text(), val.text());
}*/

/*void ProjectSettings::setDefault(const FXString& key, FXint val)
{
	setDefault("GENERAL", key, val);
}*/

/*void ProjectSettings::setDefault(const FXString& section, const FXString& key, FXint val)
{
	FXTRACE((1, "Settings::setDefault(%s, %s, %i)\n", section.text(), key.text(), val));
	defaultDict->writeIntEntry(section.text(), key.text(), val);
}*/

const FXchar* ProjectSettings::getStringValue(const FXString& key)
{
	return readStringEntry("GENERAL", key.text());
}

const FXchar* ProjectSettings::getStringValue(const FXString& section, const FXString& key)
{
	return readStringEntry(section.text(), key.text());
}

FXint ProjectSettings::getIntValue(const FXString& key)
{
	return readIntEntry("GENERAL", key.text());
}

FXint ProjectSettings::getIntValue(const FXString& section, const FXString& key)
{
	return readIntEntry(section.text(), key.text());
}

void ProjectSettings::setStringValue(const FXString& key, const FXString& value)
{
	setStringValue("GENERAL", key, value);
}

void ProjectSettings::setStringValue(const FXString& section, const FXString& key, const FXString& value)
{
	FXTRACE((1, "ProjectSettings::setStringValue(%s, %s, %s)\n", section.text(), key.text(), value.text()));
	writeStringEntry(section.text(), key.text(), value.text());
}

void ProjectSettings::setIntValue(const FXString& key, FXint value)
{
	setIntValue("GENERAL", key, value);
}

void ProjectSettings::setIntValue(const FXString& section, const FXString& key, FXint value)
{
	FXTRACE((1, "ProjectSettings::setIntValue(%s, %s, %i)\n", section.text(), key.text(), value));
	writeIntEntry(section.text(), key.text(), value);
}

void ProjectSettings::setFormatValue(const FXString& key, const FXchar* format, ...)
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

void ProjectSettings::setFormatValue(const FXString& section, const FXString& key, const FXchar* format, ...)
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

FXint ProjectSettings::getFormatValue(const FXString& key, const FXchar* format, ...)
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

FXint ProjectSettings::getFormatValue(const FXString& section, const FXString& key, const FXchar* format, ...)
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
