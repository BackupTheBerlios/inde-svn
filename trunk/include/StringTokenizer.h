#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H


#include <fx.h>
#include <FXArray.h>


/*
	Class: StringTokenizer

	splits a FXString to several Tokens. Provides a seperator, which let's
	the user choose where to split
*/
class StringTokenizer {

	private:
		FXString	line;
		FXchar		separator;
		FXint		pos;

	protected:
		StringTokenizer(const StringTokenizer&) {}

	public:
		/*
			Constructor: StringTokenizer

			reinit() has to be called to initialize the StringTokenizer
		*/
		StringTokenizer() {}
		/*
			Constructor: StringTokenizer

			creates and initializes the StringTokenizer
		*/
		StringTokenizer(FXString line, FXchar separator);
		/*
			Destructor: ~StringTokenizer
		*/
		~StringTokenizer();

		/*
			Function: reinit
		
			initializes the StringTokenizer after creation.
			Must be called, if the StringTokenizer is created by the default constructor.
			May be called to reinit a StrongTokenizer with another String or Separator
		*/
		void reinit(FXString line, FXchar separator);

		/*
			Function: getNextToken

			returns next Token of the splitted String, 
			returns an empty String, if no Token is left
		*/
		FXString			getNextToken();
		/*
			Function: getAllTokens

			returns all Tokens in an array.
			getAllTokens doesn't effect getNextToken
		*/
		FXArray<FXString>	getAllTokens();
};

#endif // STRINGTOKENIZER_H
