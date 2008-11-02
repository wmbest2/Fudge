/*
 * cpptoken.cpp
 *
 *  Created on: Sep 5, 2008
 *      Author: wmb001
 */

#include "cpptoken.h"

cpptoken::cpptoken() {
	// TODO Auto-generated constructor stub

}

cpptoken::cpptoken(const cpptoken& t)
{
	// TODO Auto-generated constructor stub
	toktype = t.type();
	textrep = t.text();
	linenum = t.line();
	columnnum = t.column();
}

cpptoken::cpptoken(cpptoken::CPPTOKENTYPE tp, std::string txt, int line, int column)
:toktype(tp), textrep(txt), linenum(line), columnnum(column)
{
	// TODO Auto-generated constructor stub

}

cpptoken& cpptoken::operator=(const cpptoken& t)
{
	type(t.type());
	text(t.text());
	line(t.line());
	column(t.column());
	return *this;
}

void cpptoken::text(const std::string& txt)
{
	textrep = txt;
}
const std::string& cpptoken::text() const
{
	return textrep;
}

void cpptoken::type(cpptoken::CPPTOKENTYPE t)
{
	toktype = t;
}

cpptoken::CPPTOKENTYPE cpptoken::type() const
{
	return toktype;
}

void cpptoken::line(int ln)
{
	linenum = ln;
}

int cpptoken::line() const
{
	return linenum;
}

void cpptoken::column(int cn)
{
	columnnum = cn;
}

int cpptoken::column() const
{
	return columnnum;
}
