/*
 * token.cpp
 *
 *  Created on: Sep 5, 2008
 *      Author: wmb001
 */

#include "token.h"

token::token() {
	// TODO Auto-generated constructor stub

}

token::token(const token& t)
{
	// TODO Auto-generated constructor stub
	toktype = t.type();
	textrep = t.text();
	linenum = t.line();
	columnnum = t.column();
}

token::token(token::TOKENTYPE tp, std::string txt, int line, int column)
:toktype(tp), textrep(txt), linenum(line), columnnum(column)
{
	// TODO Auto-generated constructor stub

}

token& token::operator=(const token& t)
{
	type(t.type());
	text(t.text());
	line(t.line());
	column(t.column());
	return *this;
}

void token::text(const std::string& txt)
{
	textrep = txt;
}
const std::string& token::text() const
{
	return textrep;
}

void token::type(token::TOKENTYPE t)
{
	toktype = t;
}

token::TOKENTYPE token::type() const
{
	return toktype;
}

void token::line(int ln)
{
	linenum = ln;
}

int token::line() const
{
	return linenum;
}

void token::column(int cn)
{
	columnnum = cn;
}

int token::column() const
{
	return columnnum;
}
