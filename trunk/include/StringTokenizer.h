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
