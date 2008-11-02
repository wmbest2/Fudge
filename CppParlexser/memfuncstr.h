/*
 * memfuncstr.h
 *
 *  Created on: Oct 23, 2008
 *      Author: Bill
 */

#ifndef MEMFUNCSTR_H_
#define MEMFUNCSTR_H_

#include <string>
#include <iostream>
#include "memfunc.h"

class ref
{
public:
	ref()
	{

	}

	virtual ~ref()
	{

	}

	virtual const std::string& toString() = 0;

};

class stringref : public ref
{
public:
	stringref()
	{

	}

	stringref(const std::string& s)
		:str(s)
	{

	}

	virtual ~stringref()
	{

	}

	virtual const std::string& toString()
	{
		return str;
	}

private:

	std::string str;
};

class memfuncstr : public ref
{
public:
	memfuncstr()
	{

	}
	memfuncstr(memfunc* f)
		:func(f)
	{

	}

	virtual const std::string& toString()
	{
		std::cout << "toString " << func->getName() << std::endl;
		return func->getString();
	}
private:

	memfunc* func;
};

#endif /* MEMFUNCSTR_H_ */
