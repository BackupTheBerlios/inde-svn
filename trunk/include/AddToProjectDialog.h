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

#ifndef ADDTOPROJECTDIALOG_H
#define ADDTOPROJECTDIALOG_H

#include <fx.h>
#include "MainWindow.h"

class AddToProjectDialog : public FXDialogBox
{
	FXDECLARE(AddToProjectDialog)

	public:
		FXString		file;
		FXString		project;
		FXint			dir;
		FXint			filetype;

	private:
		FXDataTarget 	tgtFile;
		FXDataTarget 	tgtProject;
		FXDataTarget 	tgtDir;
		FXDataTarget 	tgtFiletype;

		FXComboBox 		*combo;
		MainWindow 		*mw;
	protected:
		AddToProjectDialog() {}
		AddToProjectDialog(const AddToProjectDialog&);
		AddToProjectDialog& operator=(const AddToProjectDialog&);
		
	public:
		/*
			Constructor: AddToProjectDialog
		*/
		AddToProjectDialog(FXWindow* owner, const FXString& title);

		/*
			Destructor: ~AddToProjectDialog
		*/
		~AddToProjectDialog();

		/*
			Function: create
		*/
		virtual void create();

		/*
			Function: check

			Checks if the user provided us with the needed information
		*/
		FXbool check();

		/*
			Function: run

			executes the dialog. 
		*/
		void run(const FXString& path);
		
};


#endif // ADDTOPROJECTDIALOG_H
