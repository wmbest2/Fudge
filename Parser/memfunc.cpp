/*
 * memfunc.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "memfunc.h"

memfunc::memfunc()
{

}

memfunc::memfunc(std::string n, bool v, bool c, bool p, bool s)
	:name(n), is_virtual(v), is_const(c), is_pure(p), is_static(s)
{

}

void memfunc::setReturn(cpptype t)
{
	return_type = t;
}

void memfunc::addParam(cppvar p)
{
	params.push_back(p);
}

void memfunc::setName(const std::string& s)
{
	name = s;
}


std::string memfunc::getName()
{
	return name;
}

std::string memfunc::toString(const std::string& class_name)
{
	std::string out;
	out += return_type.toString();
	out += " ";
	out += class_name;
	out += "::";
	out += name;
	out += "(";

	for(int i = 0; i < params.size(); ++i)
	{
		out += params[i].toString();
		if(i != params.size() - 1)
			out += ", ";
	}

	out += ");";

	return out;
}
