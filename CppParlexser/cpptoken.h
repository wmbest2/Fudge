/*
 * cpptoken.h
 *
 *  Created on: Sep 5, 2008
 *      Author: wmb001
 */

#ifndef CPPTOKEN_H_
#define CPPTOKEN_H_

#include <string>

class cpptoken {
public:

	enum CPPTOKENTYPE{ invalid 		= 0,
					// SPACE FOR FORGOTTEN TYPES # 1 -> 99
					// OPERATOR TYPES # 100 -> 999
					cppjunk	=	99,
					vartype = 	100,
					id,
					lparen,
					rparen,
					lcurly,
					rcurly,
					comma,
					body
					};

	cpptoken();
	cpptoken(const cpptoken& t);
	cpptoken(CPPTOKENTYPE tp, std::string txt, int line, int column);

	cpptoken& operator=(const cpptoken& t);

	void text(const std::string& txt);
	const std::string& text() const;

	void type(CPPTOKENTYPE t);
	CPPTOKENTYPE type() const;

	void line(int ln);
	int line() const;

	void column(int cn);
	int column() const;

private:

	CPPTOKENTYPE	toktype;
	std::string textrep;
	int			linenum;
	int			columnnum;

};

#endif /* CPPTOKEN_H_ */
