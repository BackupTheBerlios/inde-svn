#ifndef SYNTAXPARSER_H
#define SYNTAXPARSER_H

#include "InDE.h"

#define MAXLINE 2048

class SyntaxParser : public FXObject {
	FXDECLARE(SyntaxParser)
	private:
		FXString	file;
		FXchar		*line;
		FXchar		*tok;
		FILE		*fp;
		FXint		number;
		FXchar		buffer[MAXLINE];
	private:
		FXchar* getline();
		const FXchar* token();
		const FXchar* word();
		const FXchar* string();
	public:
		
		// Constructor
		SyntaxParser();
		
		// Destructor
		~SyntaxParser();
		
		// Set syntax filename
		void setFile(const FXString& fn);
		
		// Get syntax filename
		const FXString& getFile();
		
		// Parse syntax file
		FXbool parse(FXSyntaxList& syntaxes);
		
		// Parse syntax rules
		FXbool parserules(FXSyntax *syntax,FXint parent);
 };
 
#endif
