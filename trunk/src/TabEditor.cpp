#include "TabEditor.h"
#include "TabItem.h"
#include <fstream>

FXDEFMAP(TabEditor) TabEditorMap[] = {
	FXMAPFUNC(SEL_RIGHTBUTTONRELEASE,	TabEditor::ID_TAB_MENU,		TabEditor::onTabMenu),
	FXMAPFUNCS(SEL_COMMAND,				TabEditor::ID_NEW,
										TabEditor::ID_CLOSE_ALL,	TabEditor::onMenuCmd),
	FXMAPFUNC(SEL_CHANGED,				TabEditor::ID_DOCUMENT,		TabEditor::onTextChanged),
	FXMAPFUNC(SEL_INSERTED,				TabEditor::ID_DOCUMENT,		TabEditor::onTextInserted),
	FXMAPFUNC(SEL_REPLACED,				TabEditor::ID_DOCUMENT,		TabEditor::onTextReplaced),
	FXMAPFUNC(SEL_DELETED,				TabEditor::ID_DOCUMENT,		TabEditor::onTextDeleted),
};

FXIMPLEMENT(TabEditor, FXTabBook, TabEditorMap, ARRAYNUMBER(TabEditorMap))

TabEditor::TabEditor(FXComposite* p, MainWindow* win, FXObject* tgt, FXSelector sel, FXuint opts)
:	FXTabBook(p, tgt, sel, TABBOOK_NORMAL|opts)
{
	mainWin = win;

	tabMenu = new FXMenuPane(this);
	new FXMenuCommand(tabMenu, "&New", NULL, this, ID_NEW);
	new FXMenuSeparator(tabMenu);
	new FXMenuCommand(tabMenu, "&Close", NULL, this, ID_CLOSE);
	new FXMenuCommand(tabMenu, "Close &others", NULL, this, ID_CLOSE_OTHERS);
	new FXMenuCommand(tabMenu, "Close &all", NULL, this, ID_CLOSE_ALL);
}

void TabEditor::create()
{
	FXTabBook::create();
}

TabEditor::~TabEditor()
{
	delete tabMenu;
	/*while (syntaxes.no())
	{
		delete syntaxes[0];
	}*/
	if (syntaxParser)
	{
		delete syntaxParser;
	}
}

FXbool TabEditor::openFile(const FXString& filename)
{
	FXTRACE((1, "TabEditor::openFile(%s)\n", filename.text()));

	std::ifstream fp(filename.text());
	if (!fp || !fp.is_open() || fp.bad())
	{
		return false;
	}
	FXuint size = FXFile::size(filename);
	FXchar* data = new FXchar[size];
	fp.rdbuf()->sgetn(data, size);

	appendDocument();
	lastDocument()->setFilename(filename);
	lastDocument()->setText(data, size);
	setCurrent(numChildren()/2);
	determineSyntax(getCurrent()-1);
	lastDocument()->setModified(false);
	lastDocument()->setEditable(FXFile::isWritable(filename));
	return true;
}

long TabEditor::onTabMenu(FXObject* sender, FXSelector, void* ptr)
{
	FXEvent* ev = (FXEvent*)ptr;
	((FXTabItem*)sender)->setFocus();
	tabMenu->popup(NULL, ev->root_x, ev->root_y);
	getApp()->runModalWhileShown(tabMenu);
	return 1;
}

long TabEditor::onMenuCmd(FXObject*, FXSelector sel, void*)
{
	FXTRACE((1, "TabEditor::onMenuCmd()\n"));
	switch (FXSELID(sel))
	{
		case ID_NEW:
			appendDocument();
			break;

		case ID_CLOSE:
			closeDocument(indexOfChild(getFocus())/2);
			break;

		case ID_CLOSE_OTHERS:
			break;

		case ID_CLOSE_ALL:
			closeAll();
			break;
	}
	return 1;
}

void TabEditor::appendDocument(const FXString& filename, const FXString& content)
{
	FXTRACE((1, "TabEditor::appendDocument(%s, ...)\n", filename.text()));
	TabItem* tab 			= new TabItem(this, FXFile::name(filename.text()), this, ID_TAB_MENU);
	FXVerticalFrame* frm 	= new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED);
	FXVerticalFrame* frm1	= new FXVerticalFrame(frm, LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Edit* edit				= new Edit(frm1, this, ID_DOCUMENT, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	tab->create();
	frm->create();
	frm1->create();
	edit->create();
	edit->setTitleTab(tab);
	edit->setFilename(filename);
	edit->setText(content);
	edit->setHiliteMatchTime(2000);
	FXFont* newFont = new FXFont(getApp(), font);
	newFont->create();
	edit->setFont(newFont);
	recalc();
}

void TabEditor::appendDocument()
{
	appendDocument("Untitled", "");
	lastDocument()->setModified();
}

Edit* TabEditor::documentAt(FXuint index)
{
	return (Edit*)(childAtIndex(index*2+1)->childAtIndex(0)->childAtIndex(0));
}

Edit* TabEditor::lastDocument()
{
	return (Edit*)(childAtIndex(numChildren()-1)->childAtIndex(0)->childAtIndex(0));
}

FXbool TabEditor::saveDocument(FXuint index)
{
	FXTRACE((1, "TabEditor::saveDocument(%i)\n", index));
	Edit* edit = (Edit*)(childAtIndex(index*2+1)->childAtIndex(0)->childAtIndex(0));
	if (edit->getFilename() != "Untitled" && !FXFile::isWritable(edit->getFilename()))
	{
		return false;
	}
	if (edit->getFilename() == "Untitled")
	{
		return saveDocumentAs(index);
	}
	std::ofstream fp;
	fp.open(edit->getFilename().text());
	if (fp.bad())
	{
		return false;
	}
	fp.write(edit->getText().text(), edit->getText().length());
	fp.close();
	edit->setModified(false);
	return true;
}

FXbool TabEditor::closeDocument(FXuint index)
{
	FXTRACE((1, "TabEditor::closeDocument(%i)\n", index));
	Edit* edit = documentAt(index);
	if (edit->isModified())
	{
		if (FXMessageBox::question(this, MBOX_YES_NO, "Document modified", "%s was modified. Do you want to save it?", edit->getFilename().text()) == MBOX_CLICKED_YES)
		{
			if (!saveDocument(index))
			{
				if (FXMessageBox::error(this, MBOX_YES_NO, "Error on save", "%s could not be saved. Do you still want to close it?", edit->getFilename().text()) == MBOX_CLICKED_NO)
				{
					return false;
				}
			}
		}
	}
	delete childAtIndex(index*2);
	delete childAtIndex(index*2);
	return true;
}

void TabEditor::setFont(const FXString& fontname)
{
	font = fontname;
	for (FXuint i = 0; i < numChildren()/2; i++)
	{
		FXFont* newFont = new FXFont(getApp(), font);
		newFont->create();
		documentAt(i)->setFont(newFont);
	}
}

FXbool TabEditor::closeAll()
{
	FXuint pos=0;
	FXuint documents = numChildren()/2;
	for (FXuint i = 0; i < documents; i++)
	{
		if (!closeDocument(pos))
		{
			pos++;
		}
	}

	return numChildren() == 0;
}


FXbool TabEditor::closeDocument()
{
	if (getCurrent() < 0)
		return true;
	return closeDocument(getCurrent());
}

FXbool TabEditor::saveDocument()
{
	if (getCurrent() < 0)
		return true;
	return saveDocument(getCurrent());
}

FXbool TabEditor::saveAll()
{
	for (FXuint i = 0; i < numChildren()/2; i++)
	{
		saveDocument(i);
	}
	return true;
}

FXbool TabEditor::saveDocumentAs(FXuint index)
{
	FXTRACE((1, "TabEditor::saveDocument(%i)\n", index));
	Edit* edit = (Edit*)(childAtIndex(index*2+1)->childAtIndex(0)->childAtIndex(0));
	FXFileDialog dialog(this, "Save file as ...");
	FXString target;
	dialog.setFilename(edit->getFilename());
	do
	{
		if (!dialog.execute())
		{
			return false;
		}
		target = dialog.getFilename();
	}
	while (FXFile::exists(target) && FXMessageBox::warning(this, MBOX_YES_NO, "File already exists", "The file %s already exists. Do you want to overwrite it?", target.text()) == MBOX_CLICKED_NO);
	std::ofstream fp;
	fp.open(target.text());
	if (fp.bad())
	{
		return false;
	}
	fp.write(edit->getText().text(), edit->getText().length());
	fp.close();
	if (!FXFile::exists(target))
	{
		return false;
	}
	if (edit->getFilename() != target)
	{
		determineSyntax(index);
		restyleDocument(index);
	}
	edit->setFilename(target);
	edit->setModified(false);
	return true;
}

FXbool TabEditor::saveDocumentAs()
{
	FXTRACE((1, "TabEditor::saveDocumentAs()\n"));
	if (getCurrent() < 0)
		return true;
	return saveDocumentAs(getCurrent());
}

void TabEditor::setSyntaxFile(const FXString& filename)
{
	syntaxFile = filename;
	loadSyntaxFile();
}

void TabEditor::loadSyntaxFile()
{
	FXTRACE((1, "TabEditor::loadSyntaxFile()\n"));
	syntaxParser = new SyntaxParser(syntaxFile);
	syntaxParser->parse(syntaxes);
}

void TabEditor::determineSyntax(FXuint index)
{
	FXTRACE((1, "TabEditor::determineSyntax(%i)\n", index));
	Edit* edit = documentAt(index);

	FXint syn;
	FXString file = FXFile::name(edit->getFilename());

	// First, try match based on file extension
	for (syn = 0; syn < syntaxes.no(); syn++)
	{
		if (syntaxes[syn]->matchFilename(file))
		{
			FXTRACE((1,"language %s matched wildcard\n", syntaxes[syn]->getName().text()));
			setSyntax(index, syntaxes[syn]);
			return;
		}
	}

	// Get the first part of contents
	FXString text('\0', FXMIN(edit->getLength(), 512));
	edit->extractText(&text[0], 0, text.length());

	// And try to match based on contents
	for (syn = 0; syn < syntaxes.no(); syn++)
	{
		if(syntaxes[syn]->matchContents(text))
		{
			FXTRACE((1,"language %s matched contents\n",syntaxes[syn]->getName().text()));
			setSyntax(index, syntaxes[syn]);
			return;
		}
	}

	// Back to plain text mode
	setSyntax(index, NULL);
}

void TabEditor::setSyntax(FXuint index, FXSyntax* syn)
{
	FXTRACE((1, "TabEditor::setSyntax(%i, ...)\n", index));
	Edit* edit = documentAt(index);
	edit->setSyntax(syn);

	register FXint rule;
	if (syn)
	{
		edit->setDelimiters(syn->getDelimiters().text());
		styles.size(syn->getNumRules()-1);
		for (rule = 1; rule < syn->getNumRules(); rule++)
		{
			styles[rule-1] = readStyleForRule(syn->getRule(rule)->getName());
		}
		edit->setHiliteStyles(styles.data());
		edit->setStyled(true);
		restyleDocument(index);
		// edit->setCurrentstyle(0);
	}
	else
	{
		edit->setDelimiters(FXText::textDelimiters);
		edit->setHiliteStyles(NULL);
		edit->setStyled(false);
		// edit->setCurrentStyle(-1);
	}
}

FXHiliteStyle TabEditor::readStyleForRule(const FXString& name)
{
	FXchar nfg[100], nbg[100], sfg[100], sbg[100], hfg[100], hbg[100], abg[100];
	FXint sty;
	FXHiliteStyle style = {0, 0, 0, 0, 0, 0, 0, 0};
	if (mainWin->settings->readFormatEntry("STYLE", name.text(), "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %d", nfg, nbg, sfg, sbg, hfg, hbg, abg, &sty) == 8)
	{
		style.normalForeColor = fxcolorfromname(nfg);
		style.normalBackColor = fxcolorfromname(nbg);
		style.selectForeColor = fxcolorfromname(sfg);
		style.selectBackColor = fxcolorfromname(sbg);
		style.hiliteForeColor = fxcolorfromname(hfg);
		style.hiliteBackColor = fxcolorfromname(hbg);
		style.activeBackColor = fxcolorfromname(abg);
		style.style = sty;
	}
	return style;
}

void TabEditor::restyleDocument(FXuint index)
{
	FXTRACE((1, "TabEditor::restyleDocument(%i)\n", index));
	Edit* edit = documentAt(index);
	FXchar* text;
	FXchar* style;
	FXint head, tail, len;
	FXSyntax* syntax = edit->getSyntax();

	if (syntax)
	{
		len = edit->getLength();
		FXMALLOC(&text, FXchar, len+len);
		style = text + len;
		edit->extractText(text, 0, len);
		syntax->getRule(0)->stylize(text, style, 0, len, head, tail);
		edit->changeStyle(0, len, style);
		FXFREE(&text);
	}
}

long TabEditor::onTextInserted(FXObject* sender, FXSelector, void*)
{
	FXTRACE((1, "TabEditor::onTextInserted()\n"));
	FXuint index = indexOfChild(((Edit*)sender)->getParent()->getParent());
	Edit* edit = (Edit*)sender;
	edit->setModified();
	if (edit->getSyntax())
	{
		restyleDocument(index);
	}
	return 1;
}


long TabEditor::onTextReplaced(FXObject* sender, FXSelector, void*)
{
	FXTRACE((1, "TabEditor::onTextReplaced()\n"));
	FXuint index = indexOfChild(((Edit*)sender)->getParent()->getParent())-1;
	Edit* edit = (Edit*)sender;
	edit->setModified();
	if (edit->getSyntax())
	{
		restyleDocument(index);
	}
	return 1;
}


long TabEditor::onTextChanged(FXObject* sender, FXSelector, void*)
{
	FXuint index = indexOfChild(((Edit*)sender)->getParent()->getParent())-1;
	Edit* edit = (Edit*)sender;
	return 1;
}


long TabEditor::onTextDeleted(FXObject* sender, FXSelector, void*)
{
	FXTRACE((1, "TabEditor::onTextDeleted()\n"));
	FXuint index = indexOfChild(((Edit*)sender)->getParent()->getParent())-1;
	Edit* edit = (Edit*)sender;
	edit->setModified();
	if (edit->getSyntax())
	{
		restyleDocument(index);
	}
	return 1;
}
