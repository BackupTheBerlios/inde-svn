#include "Edit.h"
#include <fxkeys.h>

FXDEFMAP(Edit) EditMap[] = {
	0,
};

FXIMPLEMENT(Edit, FXText, EditMap, ARRAYNUMBER(EditMap))


Edit::Edit(FXComposite* p, FXObject* tgt, FXSelector sel, FXuint opts)
:	FXText(p, tgt, sel, opts),
	filename("Untitled"),
	syntax(NULL)
{
	modified = false;
}


void Edit::create()
{
	FXText::create();
}


Edit::~Edit()
{
}


void Edit::setFilename(const FXString& file)
{
	filename = file;
	if (title)
	{
		title->setText(FXFile::name(filename));
	}
}


void Edit::setTitleTab(FXTabItem* tab)
{
	title = tab;
	title->setText(FXFile::name(filename));
}


void Edit::setModified(FXbool flag)
{
	FXTRACE((1, "Edit::setModified(%i)\n", flag));
	if (modified)
	{
		FXTRACE((1, "modified ->"));
		if (!flag)
		{
			FXTRACE((1, " not modified"));
			FXString text = title->getText();
			text.substitute("*", "");
			title->setText(text);
		}
		FXTRACE((1, "\n"));
	}
	else
	{
		FXTRACE((1, "not modified ->"));
		if (flag)
		{
			FXTRACE((1, " modified"));
			title->setText(title->getText() + "*");
		}
		FXTRACE((1, "\n"));
	}
	modified = flag;
}

void Edit::setSyntax(FXSyntax* syn)
{
	syntax = syn;
}

FXint Edit::findRestylePoint(FXint pos, FXint& style) const
{
	register FXint probepos, safepos, beforesafepos, runstyle, s;
	style = 0;
	probepos = backwardByContext(pos);
	if (probepos == 0)
		return 0;
	runstyle = getStyle(probepos);
	if (runstyle == 0)
		return probepos;

	safepos = backwardByContext(probepos);
	beforesafepos = backwardByContext(safepos);

	for (--probepos; 0 < probepos; --probepos)
	{
		s = getStyle(probepos);
		if (s == runstyle)
		{
			if (probepos <= beforesafepos)
			{
				style = runstyle;
				return safepos;
			}
			continue;
		}

		if (syntax->isAncestor(s, runstyle))
		{
			style = s;
			return probepos + 1;
		}

		if (syntax->isAncestor(runstyle, s))
		{
			style = runstyle;
			return probepos + 1;
		}

	    if (syntax->getRule(s)->getParent() == syntax->getRule(runstyle)->getParent())
	    {
			style = syntax->getRule(s)->getParent();
			return probepos + 1;
		}

		return probepos+1;
	}
	return 0;
}

FXint Edit::backwardByContext(FXint pos) const
{
	register FXint nlines = syntax->getContextLines();
	register FXint nchars = syntax->getContextChars();
	register FXint result = pos;
	if (1 < nlines)
	{
		result = prevLine(pos,nlines-1);
	}
	else if (nlines == 1)
	{
		result = lineStart(pos);
	}
	if (pos - nchars < result)
		result = pos - nchars;
	if (result < 0)
		result = 0;
	return result;
}

FXint Edit::forwardByContext(FXint pos) const
{
	register FXint nlines = syntax->getContextLines();
	register FXint nchars = syntax->getContextChars();
	register FXint result = pos;
	result = nextLine(pos, nlines);
	if (pos + nchars > result)
		result = pos + nchars;
	if (result > getLength())
		result = getLength();
	return result;
}
