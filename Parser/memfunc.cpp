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
