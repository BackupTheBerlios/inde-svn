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

#include "AddToProjectDialog.h"
#include "DialogTitle.h"
#include "MainWindow.h"
#include "StringTokenizer.h"
#include "InDE.h"

#include <iostream>
//////////////////////////////////////////////////
// Message map
FXDEFMAP(AddToProjectDialog) AddToProjectDialogMap[] = {
};


//////////////////////////////////////////////////
// Object implementation
FXIMPLEMENT(AddToProjectDialog, FXDialogBox, AddToProjectDialogMap, ARRAYNUMBER(AddToProjectDialogMap))



//////////////////////////////////////////////////
// Constructor
AddToProjectDialog::AddToProjectDialog(FXWindow* owner, const FXString& title)
:	FXDialogBox(owner, title, DECOR_ALL),
		tgtFile(file),
		tgtProject(project),
		tgtDir(dir),
		tgtFiletype(filetype)
{
	FXVerticalFrame *frm = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new DialogTitle(frm, "Add file to project?");

	FXHorizontalFrame *hfrm;

	// Filename
	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXLabel(hfrm, "Filename:");
	new FXTextField(hfrm, 15, &tgtFile, FXDataTarget::ID_VALUE, TEXTFIELD_NORMAL|TEXTFIELD_READONLY);

	// Project
	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXLabel(hfrm, "Project:");
	combo = new FXComboBox(hfrm, 15, &tgtProject, FXDataTarget::ID_VALUE, COMBOBOX_STATIC|FRAME_NORMAL);

	// get MainWindow
	FXWindow *mainWindow = getOwner();
	while (!dynamic_cast<MainWindow*>(mainWindow))
		mainWindow = mainWindow->getOwner();
	mw = dynamic_cast<MainWindow*>(mainWindow);

	// fill ComboBox
	for (int i = 0; i < mw->projects.no(); ++i)
		combo->appendItem(mw->projects[i]->getProjectName());

	// directory and filetype
	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);

	FXGroupBox *gp = new FXGroupBox(hfrm, "Directory", FRAME_LINE);
	FXVerticalFrame *vfrm = new FXVerticalFrame(gp, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXRadioButton(vfrm, "src", 			&tgtDir, FXDataTarget::ID_OPTION+0);
	new FXRadioButton(vfrm, "include", 		&tgtDir, FXDataTarget::ID_OPTION+1);
	new FXRadioButton(vfrm, "doc", 			&tgtDir, FXDataTarget::ID_OPTION+2);
	new FXRadioButton(vfrm, "ressource",	&tgtDir, FXDataTarget::ID_OPTION+3);
	new FXRadioButton(vfrm, "project root",	&tgtDir, FXDataTarget::ID_OPTION+4);

	gp = new FXGroupBox(hfrm, "Filetype", FRAME_LINE);
	vfrm = new FXVerticalFrame(gp, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXRadioButton(vfrm, "C++ Source", 		&tgtFiletype, FXDataTarget::ID_OPTION+0);
	new FXRadioButton(vfrm, "C++ Header", 		&tgtFiletype, FXDataTarget::ID_OPTION+1);
	new FXRadioButton(vfrm, "Textfile", 		&tgtFiletype, FXDataTarget::ID_OPTION+2);
	new FXRadioButton(vfrm, "Ressource file",	&tgtFiletype, FXDataTarget::ID_OPTION+3);

	// Buttons
	hfrm = new FXHorizontalFrame(frm, LAYOUT_FILL_X);
	new FXButton(hfrm, "&Cancel", NULL, this, FXDialogBox::ID_CANCEL, BUTTON_DEFAULT|LAYOUT_LEFT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);	
	new FXButton(hfrm, "&Ok", NULL, this, FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 12, 12, 4, 4);	
}


//////////////////////////////////////////////////
// Destructor
AddToProjectDialog::~AddToProjectDialog()
{
}


//////////////////////////////////////////////////
// create
void AddToProjectDialog::create()
{
	FXDialogBox::create();
}


//////////////////////////////////////////////////
// check
FXbool AddToProjectDialog::check()
{
	FXint cur = combo->getCurrentItem();
	mw->projects[cur]->parse();
	FXString subdir;
	FXString key;

	switch (dir)
	{
		case 0:
			subdir = mw->projects[cur]->getStringValue("DIRECTORY", "sourceDir");
			key = "source";
			break;
		case 1:
			subdir = mw->projects[cur]->getStringValue("DIRECTORY", "includeDir");
			key = "include";
			break;
		case 2:
			subdir = mw->projects[cur]->getStringValue("DIRECTORY", "docDir");
			key = "doc";
			break;
		case 3:
			subdir = mw->projects[cur]->getStringValue("DIRECTORY", "ressourceDir");
			key = "ressource";
			break;
		default:
			subdir = "";
			key = "root";
			break;
	}
	ProjectBrowser::FileType type;
	switch (filetype)
	{
		case 0:		// C++ source	
			type = ProjectBrowser::CPP_SOURCE;
			break;
		case 1:		// C++ header 
			type = ProjectBrowser::CPP_HEADER;
			break;
		case 2:		// Text file	
			type = ProjectBrowser::TEXT;
			break;
		case 3:		// Ressource file	
			type = ProjectBrowser::RESSOURCE_FILE;
			break;
		default:	// Text file
			type = ProjectBrowser::TEXT;
			break;
	}

	mw->projectBrowser->addFile(combo->getItem(cur), file, subdir, type);

	mw->projects[cur]->appendStringValue("FILES", key, file);
	mw->projects[cur]->write();

	return true;
}


//////////////////////////////////////////////////
// run
void AddToProjectDialog::run(const FXString& path)
{
	file = FXFile::name(path);
	StringTokenizer strtok(FXFile::directory(path), DIR_SEPARATOR);
	FXString workspace = mw->settings->getStringValue("baseDir");
	FXString filepath;
	FXbool projectDir = false;

	// is file in InDE workspace?
	while (true)
	{
		FXString token = strtok.getNextToken();
		if (token == "")
			break;
		filepath += DIR_SEPARATOR + token;
		if (filepath == workspace)
		{
			projectDir = true;
			break;
		}
	} 

	// if file is in the project workspace
	if (projectDir)
	{
		// is file saved in a project directory
		FXString token = strtok.getNextToken();
		int i;
		if (token != "")
		{
			// set first opened project as default
			combo->setCurrentItem(0);
			// is file in a project dir
			for (i = 0; i < mw->projects.no(); ++i)
				if (token == mw->projects[i]->getProjectName())
				{
					combo->setCurrentItem(i);
					break;
				}
			project = combo->getItem(combo->getCurrentItem());
			if (i == mw->projects.no()) i = 0;
		}
		// is file saved in a special project subdirectory
		token = strtok.getNextToken();
		if (token != "")
		{
//			token += DIR_SEPARATOR;
			if (token == mw->projects[i]->getStringValue("DIRECTORY", "sourceDir"))
				dir = 0;
			if (token == mw->projects[i]->getStringValue("DIRECTORY", "includeDir"))
				dir = 1;
			if (token == mw->projects[i]->getStringValue("DIRECTORY", "docDir"))
				dir = 2;
			if (token == mw->projects[i]->getStringValue("DIRECTORY", "ressourceDir"))	
				dir = 3;
		}
		else
			dir = 4;	// project root
		// set default file type based on dir
		switch (dir)
		{
			case 0:		// C++ source	
				filetype = 0;
				break;
			case 1:		// C++ header 
				filetype = 1;
				break;
			case 2:		// Text file	
				filetype = 2;
				break;
			case 3:		// Ressource file	
				filetype = 3;
				break;
			default:	// Text file
				filetype = 2;
				break;
		}
	}

	// execute dialog
	do
	{
		if (!execute(PLACEMENT_OWNER))
		{
			return;
		}
	} while (!check());
}



