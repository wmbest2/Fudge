/*
 * token.h
 *
 *  Created on: Sep 5, 2008
 *      Author: wmb001
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

class token {
public:

	enum TOKENTYPE{ invalid 		= 0,
					// SPACE FOR FORGOTTEN TYPES # 1 -> 99
					// OPERATOR TYPES # 100 -> 999
					plus 			= 100,		// +
					plusplus 		= 101,		// ++
					pluseq 			= 102,		// +=
					minus			= 103,		// -
					minusminus	 	= 104,		// --
					minuseq			= 105,		// -=
					ast				= 106,		// *
					asteq			= 107,		// *=
					div				= 108,		// /
					diveq 			= 109,		// /=
					mod				= 110,		// %
					modeq			= 111,		// %=
					less			= 112,		// <
					lesseq			= 113,		// <=
					lshift			= 114,		// <<
					lshifteq		= 115,		// <<=
					great			= 116,		// >
					greateq			= 117,		// >=
					rshift			= 118,		// >>
					rshifteq		= 119,		// >>=
					bang			= 120,		// !
					bangeq			= 121,		// !=
					eq				= 122,		// =
					eqeq			= 123,		// ==
					tilda			= 124,		// ~
					amp				= 125,		// &
					ampeq			= 126,		// &=
					ampamp			= 127,		// &&
					pipe			= 128,		// |
					pipeeq			= 129,		// |=
					pipepipe		= 130,		// ||
					caret			= 131,		// ^
					careteq			= 132,		// ^=
					lsquare			= 133,		// [
					rsquare			= 134,		// ]
					lparen			= 135,		// (
					rparen			= 136,		// )
					lcurly			= 137,		// {
					rcurly			= 138,		// }
					semi			= 139,		// ;
					under			= 140,		// _
					arrow			= 141,		// ->
					arrowast		= 142,		// ->*
					period			= 143, 		// .
					periodast		= 144,		// .*
					comma			= 145,		// ,
					quest			= 146,		// ?
					colon			= 147,		// :
					coloncolon		= 148,		// ::
					coloncoloneq	= 149,		// ::=
					lessquest		= 150,		// <?
					greatquest		= 151,		// >?
					pound			= 152,		// #
					forslash		= 153,		// \
					// OTHER TYPES #1000->
					stringliteral 	= 1000,
					charliteral,
					keyword,
					number,
					identifier,
					// PREPROCESSOR DIRECTIVES
					include			= 2000,
					define			= 2001,
					ifdef			= 2002,
					ifndef			= 2003,
					endif			= 2004,
					ppjunk			= 2005
					};

	token();
	token(const token& t);
	token(TOKENTYPE tp, std::string txt, int line, int column);

	token& operator=(const token& t);

	void text(const std::string& txt);
	const std::string& text() const;

	void type(TOKENTYPE t);
	TOKENTYPE type() const;

	void line(int ln);
	int line() const;

	void column(int cn);
	int column() const;

private:

	TOKENTYPE	toktype;
	std::string textrep;
	int			linenum;
	int			columnnum;

};

#endif /* TOKEN_H_ */
