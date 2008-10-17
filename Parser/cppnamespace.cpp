/*
 * cpptemplate.cpp
 *
 *  Created on: Oct 16, 2008
 *      Author: Bill
 */
#include "cppnamespace.h"

cppnamespace::cppnamespace()
	:id("invalid")
{

}

cppnamespace::cppnamespace(const std::string& i)
	:id(i)
{

}


void cppnamespace::setName(const std::string& i)
{
	id = i;
}

std::string cppnamespace::getName() const
{
	return id;
}
