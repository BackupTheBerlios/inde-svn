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

#include "NewClassDialog.h"
#include "DialogTitle.h"
#include "FileSystem.h"
#include "ProjectBrowser.h"

//////////////////////////////////////////////////
// Message map
FXDEFMAP(NewClassDialog) NewClassDialogMap[] = {
};


//////////////////////////////////////////////////
// Object implementation
FXIMPLEMENT(NewClassDialog, FXDialogBox, NewClassDialogMap, ARRAYNUMBER(NewClassDialogMap))



//////////////////////////////////////////////////
// Constructor
NewClassDialog::NewClassDialog(FXWindow* owner, const FXString& title)
	:	FXDialogBox(owner, title, DECOR_ALL),
		tgtName(name),
		tgtSource(source),
		tgtHeader(header),
		tgtSourceDir(sourceDir),
		tgtIncludeDir(includeDir),
		tgtClassType(classType),
		source(1),
		header(1),
		sourceDir(0),
		includeDir(0),
		classType(PROJECT_TYPE_CPP)
{
	// get MainWindow
	FXWindow *mainWindow = getOwner();
	while (!dynamic_cast<MainWindow*>(mainWindow))
		mainWindow = mainWindow->getOwner();
	mw = dynamic_cast<MainWindow*>(mainWindow);

	FXVerticalFrame *frm = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "create new class");

	FXHorizontalFrame *hfrm;

	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXLabel(hfrm, "Class name:");
	new FXTextField(hfrm, 15, &tgtName, FXDataTarget::ID_VALUE, TEXTFIELD_NORMAL);

	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXLabel(hfrm, "Create:");
	new FXCheckButton(hfrm, "Source file", &tgtSource, FXDataTarget::ID_VALUE);
	new FXCheckButton(hfrm, "Header file", &tgtHeader, FXDataTarget::ID_VALUE);
	
	FXGroupBox *gp;
	FXVerticalFrame *vfrm;

	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	gp = new FXGroupBox(hfrm, "Dir for source file", FRAME_LINE);
	vfrm = new FXVerticalFrame(gp, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXRadioButton(vfrm, "source dir", 	&tgtSourceDir, FXDataTarget::ID_OPTION+0);
	new FXRadioButton(vfrm, "include dir",	&tgtSourceDir, FXDataTarget::ID_OPTION+1);
	new FXRadioButton(vfrm, "root dir", 	&tgtSourceDir, FXDataTarget::ID_OPTION+2);
	gp = new FXGroupBox(hfrm, "Dir for include file", FRAME_LINE);
	vfrm = new FXVerticalFrame(gp, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXRadioButton(vfrm, "include dir", 	&tgtIncludeDir, FXDataTarget::ID_OPTION+0);
	new FXRadioButton(vfrm, "source dir", 	&tgtIncludeDir, FXDataTarget::ID_OPTION+1);
	new FXRadioButton(vfrm, "root dir", 	&tgtIncludeDir, FXDataTarget::ID_OPTION+2);

	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXLabel(hfrm, "Class type:");
	FXComboBox* typeBox = new FXComboBox(hfrm, 0, &tgtClassType, FXDataTarget::ID_VALUE, LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_NORMAL);
	typeBox->appendItem(PROJECT_TYPE_CPP);
	typeBox->appendItem(PROJECT_TYPE_PYTHON);
	typeBox->appendItem(PROJECT_TYPE_RUBY);
	typeBox->setNumVisible(3);
	typeBox->setCurrentItem(0);
	typeBox->setEditable(FALSE);

	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXButton(hfrm, "&Cancel", NULL, this, FXDialogBox::ID_CANCEL, BUTTON_DEFAULT|LAYOUT_LEFT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);	
	new FXButton(hfrm, "&Ok", NULL, this, FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);	
}


//////////////////////////////////////////////////
// Destructor
NewClassDialog::~NewClassDialog()
{
}


//////////////////////////////////////////////////
// create
void NewClassDialog::create()
{
	FXDialogBox::create();
}


//////////////////////////////////////////////////
// check
FXbool NewClassDialog::check()
{
	FXuint errors = 0;

	if (name == "")
	{
		++errors;
		FXMessageBox::error(this, MBOX_OK, "Error", "You should name the class.");
	}

	settings->parse();

	FXString baseDir = mw->settings->getStringValue("baseDir");
	baseDir += FS::dirSeparator();
	baseDir += settings->getProjectName();
	baseDir += FS::dirSeparator();

	// create source file
	if (source)
	{
		FXString sourcefile = baseDir;
		FXString sourceName = name;
		ProjectBrowser::FileType	sourceType;
		FXString	srcDir;
		FXString 	srcKey;
	
		switch (sourceDir)
		{
			case 0:		// source
				srcDir = settings->getStringValue("DIRECTORY", "sourceDir");
				sourcefile += srcDir;
				sourcefile += FS::dirSeparator();
				srcKey = "source";
				break;
			case 1:		// include
				srcDir = settings->getStringValue("DIRECTORY", "includeDir");
				sourcefile += srcDir;
				sourcefile += FS::dirSeparator();
				srcKey = "include";
				break;
			case 2:		// project root
				srcDir = "";
				srcKey = "root";
				break;
		}
		if (classType == PROJECT_TYPE_CPP)
		{
			sourceName += ".cpp";
			sourceType = ProjectBrowser::CPP_SOURCE;
		}

		if (!FXFile::exists(sourcefile+sourceName))
		{
			FXFile::createFile(sourcefile+sourceName, 0644);
			mw->projectBrowser->addFile(settings->getProjectName(), sourceName, srcDir, sourceType);
			settings->appendStringValue("FILES", srcKey, sourceName);
		}
		else
		{
			++errors;
			FXMessageBox::error(this, MBOX_OK, "Error", (sourcefile+sourceName + " already exists.").text());
		}
	}

	// create header file
	if (header)
	{
		FXString headerfile = baseDir;
		FXString headerName = name;
		ProjectBrowser::FileType	headerType;
		FXString	incDir;
		FXString	incKey;

		switch (includeDir)
		{
			case 0:		// include
				incDir = settings->getStringValue("DIRECTORY", "includeDir");
				headerfile += incDir;
				headerfile += FS::dirSeparator();
				incKey = "include";
				break;
			case 1:		// source
				incDir = settings->getStringValue("DIRECTORY", "sourceDir");
				headerfile += incDir;
				headerfile += FS::dirSeparator();
				incKey = "source";
				break;
			case 2:		// project root
				incDir = "";
				incKey = "root";
				break;
		}
		if (classType == PROJECT_TYPE_CPP)
		{
			headerName += ".h";
			headerType = ProjectBrowser::CPP_HEADER;
		}

		if (!FXFile::exists(headerfile+headerName))
		{
			FXFile::createFile(headerfile+headerName, 0644);
			mw->projectBrowser->addFile(settings->getProjectName(), headerName, incDir, headerType);
			settings->appendStringValue("FILES", incKey, headerName);
		}
		else
		{
			++errors;
			FXMessageBox::error(this, MBOX_OK, "Error", (headerfile+headerName + " already exists.").text());
		}
	}

	settings->write();

	return errors == 0;
}


//////////////////////////////////////////////////
// run
void NewClassDialog::run(ProjectSettings* project)
{
	settings = project;
	// execute dialog
	do
	{
		if (!execute(PLACEMENT_OWNER))
		{
			return;
		}
	} while (!check());
}

