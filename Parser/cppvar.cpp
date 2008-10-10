/*
 * cppvar.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "cppvar.h"

cppvar::cppvar()
	:id("invalid")
{

}

cppvar::cppvar(cpptype t, std::string i, std::string iv)
	:type(t), id(i), init_val(iv)
{

}

void cppvar::setType(cpptype t)
{
	type = t;
}

void cppvar::setName(std::string i)
{
	id = i;
}

std::string cppvar::getName()
{
	return id;
}

std::string cppvar::toString()
{
	return type.toString() + " " + id;
}
