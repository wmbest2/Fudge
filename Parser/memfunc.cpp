/*
 * memfunc.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "memfunc.h"

#include "cppclass.h"

memfunc::memfunc()
{

}

memfunc::memfunc(std::string n, bool v, bool c, bool p, bool s)
	:name(n), is_virtual(v), is_const(c), is_pure(p), is_static(s),string_dirty(true)
{

}

void memfunc::setReturn(cpptype t)
{
	string_dirty = true;
	return_type = t;
}

void memfunc::addParam(cppvar p)
{
	string_dirty = true;
	params.push_back(p);
}

void memfunc::setName(const std::string& s)
{
	string_dirty = true;
	name = s;
}


std::string memfunc::getName()
{
	return name;
}

void memfunc::setClass(cppclass* c)
{
	string_dirty = true;
	owner = c;
}

std::string memfunc::toString()
{
	std::string out;
	out += return_type.toString();
	out += " ";
	out += owner->getQual();
	out += "::";
	out += name;
	out += "(";

	for(int i = 0; i < params.size(); ++i)
	{
		out += params[i].toString();
		if(i != params.size() - 1)
			out += ", ";
	}

	out += "){\n\n\n}";

	return out;
}

const std::string& getString()
{
	if(string_dirty)
	{
		output = return_type.toString();
		output += " ";
		output += owner->getQual();
		output += "::";
		output += name;
		output += "(";

		for(int i = 0; i < params.size(); ++i)
		{
			output += params[i].toString();
			if(i != params.size() - 1)
				output += ", ";
		}

		output += "){\n\n\n}\n";

		string_dirty = false;
	}

	return output;
}
