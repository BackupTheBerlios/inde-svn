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

#include "ProjectBrowser.h"
#include "StringTokenizer.h"
#include "FileSystem.h"

//////////////////////////////////////////////////
// Message map

FXDEFMAP(ProjectBrowser) ProjectBrowserMap[] = {
	FXMAPFUNC(SEL_DOUBLECLICKED,	ProjectBrowser::ID_BROWSER,	ProjectBrowser::onDoubleClick),
};


//////////////////////////////////////////////////
// Object implementation
FXIMPLEMENT(ProjectBrowser, FXVerticalFrame, ProjectBrowserMap, ARRAYNUMBER(ProjectBrowserMap))



//////////////////////////////////////////////////
// Constructor
ProjectBrowser::ProjectBrowser(FXComposite* p, MainWindow* win, FXObject* tgt, FXSelector sel, FXuint opts)
	: FXVerticalFrame(p, opts, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
	mainWin = win;

	projectTree = new FXTreeList(this, this, ID_BROWSER, TREELIST_BROWSESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES|LAYOUT_FILL_X|LAYOUT_FILL_Y);
}


//////////////////////////////////////////////////
// Destructor
ProjectBrowser::~ProjectBrowser()
{
	delete projectTree;
}


//////////////////////////////////////////////////
// Fox interface
void ProjectBrowser::create()
{
	FXVerticalFrame::create();
}


//////////////////////////////////////////////////
void ProjectBrowser::addFile(FXString project, FXString name, FXString dir, FileType type)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* sub;
	if (dir != "")
		sub = projectTree->findItem(dir, root);
	else
		sub = root;
	if (!sub) return;
	// add file icons
	FXTreeItem* file = new FXTreeItem(name, NULL, NULL);
	projectTree->appendItem(sub, name);
}


//////////////////////////////////////////////////
void ProjectBrowser::removeFile(FXString project, FXString name, FXString dir)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* sub = projectTree->findItem(dir, root);
	if (!sub) return;
	FXTreeItem* file = projectTree->findItem(name, sub);
	if (!file) return;
	projectTree->removeItem(file);
}


//////////////////////////////////////////////////
void ProjectBrowser::moveFile(FXString project, FXString name, FXString olddir, FXString newdir)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* old_dir = projectTree->findItem(olddir, root);
	if (!old_dir) return;
	FXTreeItem* new_dir = projectTree->findItem(newdir, root);
	if (!new_dir) return;
	FXTreeItem* file = projectTree->findItem(name, old_dir);
	if (!file) return;
	projectTree->moveItem(new_dir, old_dir, file);
}


//////////////////////////////////////////////////
void ProjectBrowser::renameFile	(FXString project, FXString name, FXString newname, FXString dir)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* sub = projectTree->findItem(dir, root);
	if (!sub) return;
	FXTreeItem* file = projectTree->findItem(name, sub);
	if (!file) return;
	file->setText(newname);
}


//////////////////////////////////////////////////
void ProjectBrowser::addDir(FXString project, FXString dirname, DirType type)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	// add directory icons
	FXTreeItem* dir = new FXTreeItem(dirname, NULL, NULL);
	projectTree->appendItem(root, dir);
}


//////////////////////////////////////////////////
void ProjectBrowser::removeDir(FXString project, FXString dirname)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* sub = projectTree->findItem(dirname, root);
	if (!sub) return;
	projectTree->removeItem(sub);
}


//////////////////////////////////////////////////
void ProjectBrowser::renameDir(FXString project, FXString olddirname, FXString newdirname)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* sub = projectTree->findItem(olddirname, root);
	if (!sub) return;
	sub->setText(newdirname);
}


//////////////////////////////////////////////////
void ProjectBrowser::addProject(FXString name)
{
	// add project icons
	FXTreeItem* project = new FXTreeItem(name, NULL, NULL);
	projectTree->appendItem(NULL, project);
}


//////////////////////////////////////////////////
void ProjectBrowser::removeProject(FXString name)
{
	FXTreeItem* root = projectTree->findItem(name);
	if (!root) return;
	projectTree->removeItem(root);
}


//////////////////////////////////////////////////
FXString ProjectBrowser::getActiveProject()
{
	FXTreeItem* current = projectTree->getCurrentItem();
	while (true)
	{
		FXTreeItem* parent = current->getParent();
		if (parent == NULL)
			break;
		current = parent;
	}
	return current->getText();
}


//////////////////////////////////////////////////
void ProjectBrowser::openProject(ProjectSettings* settings)
{
	FileType sourceType, includeType;
	StringTokenizer* strtok = new StringTokenizer();

	settings->parse();

	FXString project = settings->getStringValue("GENERAL", "name");
	addProject(project);

	FXString source = settings->getStringValue("DIRECTORY", "sourceDir");
	if (source != "")
		addDir(project, source, SOURCE);
	FXString include = settings->getStringValue("DIRECTORY", "includeDir");
	if (include != "")
		addDir(project, include, INCLUDE);
	FXString ressource = settings->getStringValue("DIRECTORY", "ressourceDir");
	if (ressource != "")
		addDir(project, ressource, RESSOURCE);
	FXString doc = settings->getStringValue("DIRECTORY", "docDir");
	if (doc != "")
		addDir(project, doc, DOC);

	FXString type = settings->getStringValue("GENERAL", "type");
	if (type == "C/C++")
	{
		sourceType = CPP_SOURCE;
		includeType = CPP_HEADER;
	}

	FXString sourceList = settings->getStringValue("FILES", "source");
	if (sourceList != "")
	{
		strtok->reinit(sourceList, ProjectSettings::SEPARATOR);
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, source, sourceType);
	}

	FXString includeList = settings->getStringValue("FILES", "include");
	if (includeList != "")
	{
		strtok->reinit(includeList, ProjectSettings::SEPARATOR);
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, include, includeType);
	}

	FXString ressourceList = settings->getStringValue("FILES", "ressource");
	if (ressourceList != "")
	{
		strtok->reinit(ressourceList, ProjectSettings::SEPARATOR);
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, ressource, RESSOURCE_FILE);
	}

	FXString docList = settings->getStringValue("FILES", "doc");
	if (docList != "")
	{
		strtok->reinit(docList, ProjectSettings::SEPARATOR);
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, doc, TEXT);
	}

	FXString rootList = settings->getStringValue("FILES", "root");
	if (rootList != "")
	{
		strtok->reinit(rootList, ProjectSettings::SEPARATOR);
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, "", TEXT);
	}

	settings->write();	// unparse
	delete strtok;
}


//////////////////////////////////////////////////
FXString ProjectBrowser::getPathname(FXTreeItem* item) 
{
	FXString path;

	FXTreeItem* current = item;
	while (true)
	{
		path.prepend(current->getText());
		path.prepend(FS::dirSeparator());
		FXTreeItem* parent = current->getParent();
		if (parent == NULL)
			break;
		current = parent;
	}

	path.prepend(mainWin->settings->getStringValue("baseDir"));
	return path;
}


//////////////////////////////////////////////////
long ProjectBrowser::onDoubleClick(FXObject* sender, FXSelector sel, void* ptr)
{
	FXTRACE((1, "FileBrowser::onDoubleClick()\n"));
	if (ptr)
	{
		FXTreeItem* item = (FXTreeItem*)ptr;
		if (!projectTree->isItemLeaf(item))
		{
	    	if(projectTree->isItemExpanded(item))
	    	{
				projectTree->collapseTree(item, TRUE);
			}
			else
			{
				projectTree->expandTree(item, TRUE);
			}
		}
		else// if (projectTree->isItemLeaf(item))
		{
			mainWin->getEditor()->openFile(getPathname(item));
		}
	}
	return 1;
}
