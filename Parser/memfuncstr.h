/*
 * memfuncstr.h
 *
 *  Created on: Oct 23, 2008
 *      Author: Bill
 */

#ifndef MEMFUNCSTR_H_
#define MEMFUNCSTR_H_

#include <string>
#include "memfunc.h"

class stringref
{
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

class memfuncstr : public stringref
{
public:
	memfuncstr()
	{

	}
	memfuncstr(memfunc* f)
		:func(f)
	{

	}

	const std::string& toString()
	{
		return func->getString();
	}
private:

	memfunc* func;
};

#endif /* MEMFUNCSTR_H_ */
