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

void memfunc::setClass(cppclass* c)
{
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

void memfunc::cppOutput(const std::string& file)
{

	std::ofstream of;
	of.open(file.c_str(), std::ios_base::app);

	of << return_type.toString();
	of << " ";
	of << owner->getQual();
	of << "::";
	of << name;
	of << "(";

	for(int i = 0; i < params.size(); ++i)
	{
		of << params[i].toString();
		if(i != params.size() - 1)
			of << ", ";
	}

	of << "){\n\n\n}\n";

	of.close();
}
