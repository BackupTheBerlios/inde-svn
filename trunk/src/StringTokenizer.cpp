#include "StringTokenizer.h"
// needed for FXArray
#include <new>

//////////////////////////////////////////////////
// Constructor
StringTokenizer::StringTokenizer(FXString line, FXchar separator)
{
	this->line = line;
	if (separator)
		this->separator = separator;
	else
		this->separator = ' ';
	pos = 0;
}


//////////////////////////////////////////////////
// Destructor
StringTokenizer::~StringTokenizer()
{
}


//////////////////////////////////////////////////
// reinit
void StringTokenizer::reinit(FXString line, FXchar separator)
{
	this->line = line;
	if (separator)
		this->separator = separator;
	else
		this->separator = ' ';
	pos = 0;
}


//////////////////////////////////////////////////
// getNextToken
FXString StringTokenizer::getNextToken()
{
	if (line == "")
		return "";
	FXString token;

	token = line.section(separator, pos);
	pos++;

	return token;
}


//////////////////////////////////////////////////
// getAllTokens, doesn't effect getNextToken
FXArray<FXString> StringTokenizer::getAllTokens()
{
	FXString token;
	FXint poz = 0;
	FXArray<FXString> tokenList;// = new FXArray<FXString>();
	FXbool end = FALSE;

	while (!end)
	{
		token = line.section(separator, poz);
		poz++;
		if (token == "") 
		{
			end = TRUE;
			continue;
		}
		tokenList.append(token);
	}
	return tokenList;
}

