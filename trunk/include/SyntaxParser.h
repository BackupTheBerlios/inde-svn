#ifndef SYNTAXPARSER_H
#define SYNTAXPARSER_H

#include <fx.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Hilite.h"

#define MAXLINE 2048

class SyntaxParser {
	private:
		FXString  file;
		FXchar   *line;
		FXchar   *tok;
		FILE     *fp;
		FXint     number;
		FXchar    buffer[MAXLINE];
	private:
		FXchar* getline();
		const FXchar* token();
		const FXchar* word();
		const FXchar* string();
	public:
		SyntaxParser(const FXString& fn):file(fn),line(NULL),tok(NULL),fp(NULL),number(0){}
		FXbool parse(FXSyntaxList& syntaxes);
		FXbool parserules(FXSyntax *syntax,FXint parent);
		~SyntaxParser(){ if(fp) fclose(fp); }
};

#endif
