#include "ProjectBrowser.h"
#include "StringTokenizer.h"

//////////////////////////////////////////////////
// Message map

FXDEFMAP(ProjectBrowser) ProjectBrowserMap[] = {
//	FXMAPFUNC(SEL_COMMAND, ProjectBrowser::ID_SELECTLICENSEFILE, ProjectBrowser::onCmdSelectLicenseHeader),
};


//////////////////////////////////////////////////
// Object implementation
FXIMPLEMENT(ProjectBrowser, FXComposite, ProjectBrowserMap, ARRAYNUMBER(ProjectBrowserMap))



//////////////////////////////////////////////////
// Constructor
ProjectBrowser::ProjectBrowser(FXComposite *p, FXObject *tgt, FXSelector sel, FXuint opts, FXint x, FXint y, FXint w, FXint h)
	: FXComposite(p)
{
	projectTree = new FXTreeList(p, tgt, sel, opts, x, y, w, h);
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
	projectTree->create();
}

void ProjectBrowser::detach()
{
	projectTree->detach();
}

void ProjectBrowser::layout()
{
	projectTree->layout();
}

FXint ProjectBrowser::getDefaultWidth()
{
	return projectTree->getDefaultWidth();
}

FXint ProjectBrowser::getDefaultHeight()
{
	return projectTree->getDefaultHeight();
}

FXint ProjectBrowser::getContentWidth()
{
	return projectTree->getContentWidth();
}

FXint ProjectBrowser::getContentHeight()
{
	return projectTree->getContentHeight();
}

void ProjectBrowser::recalc()
{
	projectTree->recalc();
}

FXbool ProjectBrowser::canFocus() const
{
	return projectTree->canFocus();
}

void ProjectBrowser::setFocus()
{
	projectTree->setFocus();
}

void ProjectBrowser::killFocus()
{
	projectTree->killFocus();
}


//////////////////////////////////////////////////
void ProjectBrowser::addFile(FXString project, FXString name, FXString dir, FileType type)
{
	FXTreeItem* root = projectTree->findItem(project);
	if (!root) return;
	FXTreeItem* sub = projectTree->findItem(dir, root);
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
	FXTreeItem* dir = new FXTreeItem(dirname.remove(dirname.length()-1), NULL, NULL);
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

	FXString type = settings->getStringValue("GENERAL", "type");
	if (type == "C/C++")
	{
		sourceType = CPP_SOURCE;
		includeType = CPP_HEADER;
	}

	FXString sourceList = settings->getStringValue("FILES", "source");
	if (sourceList != "")
	{
		strtok->reinit(sourceList, ',');
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, source, sourceType);
	}

	FXString includeList = settings->getStringValue("FILES", "include");
	if (includeList != "")
	{
		strtok->reinit(includeList, ',');
		FXString token;
		while ((token = strtok->getNextToken()) != "")
			addFile(project, token, include, includeType);
	}

	settings->unparse();
	delete strtok;
}

