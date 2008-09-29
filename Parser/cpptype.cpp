/*
 * cpptype.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "cpptype.h"

cpptype::cpptype()
{

}

void cpptype::addQual(std::string q)
{
	qual_list.push_back(q);
}

void cpptype::setConst(bool c)
{
	is_const = c;
}
bool cpptype::getConst()
{
	return is_const;
}
