/*
 * memfunc.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "memfunc.h"

#include "cppclass.h"

memfunc::memfunc()
	:is_const(false)
{

}

memfunc::memfunc(std::string n, bool v, bool c, bool p, bool s)
	:name(n), is_virtual(v), is_const(c), is_pure(p), is_static(s),string_dirty(true)
{

}

bool memfunc::operator==(const memfunc& rhs)
{

	if ( (return_type == rhs.return_type)
			&& (name == rhs.name)
			&& (owner->getName() == rhs.owner->getName())
			&& (params.size() == rhs.params.size()))
	{
		for(int i = 0; i < params.size(); ++i)
		{
			if(!(params[i].getType() == rhs.params[i].getType()))
			{
				return false;
			}
		}

		return true;
	}



	return false;
}

void memfunc::setReturn(cpptype t)
{
	string_dirty = true;
	return_type = t;
}

cpptype memfunc::getReturn()
{
	return return_type;
}

void memfunc::addParam(cppvar p)
{
	string_dirty = true;
	params.push_back(p);
}

std::vector<cppvar> memfunc::getParams()
{
	return params;
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
cppclass* memfunc::getClass()
{
	return owner;
}

std::string memfunc::toString() // returns the header string
{
	std::string out;
	out += return_type.toString();
	if(return_type.toString() != "")
		out += " ";
	out += name;
	out += "(";

	for(int i = 0; i < params.size(); ++i)
	{
		out += params[i].toString();
		if(i != params.size() - 1)
			out += ", ";
	}

	out += ")";

	if(is_const)
		out += " const";

	return out;
}

std::string memfunc::toCppString() // returns the header string
{
	std::string out;
	out += return_type.toString();
	if(return_type.toString() != "")
		out += " ";
	if(owner)
	{
		out += owner->getQual();
		out += "::";
	}
	out += name;
	out += "(";

	for(int i = 0; i < params.size(); ++i)
	{
		out += params[i].toString();
		if(i != params.size() - 1)
			out += ", ";
	}

	out += ")";

	if(is_const)
		out += " const";

	return out;
}

std::string& memfunc::getString()
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

void memfunc::setConst(bool c)
{
	is_const = c;
}

void memfunc::setVirtual(bool v)
{
	is_virtual = v;
}

void memfunc::setBody(const std::string& s)
{
	function_body = s;
}

std::string memfunc::getBody()
{
	return function_body;
}
