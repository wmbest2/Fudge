/*
 * cpptype.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "cpptype.h"

cpptype::cpptype()
	:is_const(false)
{

}

bool cpptype::operator==(cpptype rhs)
{
	if(getConst() == rhs.getConst())
	{
		std::string lhss, rhss;
		for(int i = 0; i < qual_list.size(); ++i)
					lhss += qual_list[i];

		for(int i = 0; i < rhs.qual_list.size(); ++i)
			rhss += rhs.qual_list[i];

		if(lhss == rhss)
			return true;
	}
	return false;
}

void cpptype::addQual(std::string q)
{
	dbg::trace tr("cpptype", DBG_HERE);
	qual_list.push_back(q);
}

void cpptype::setConst(bool c)
{
	dbg::trace tr("cpptype", DBG_HERE);
	is_const = c;
}
bool cpptype::getConst()
{
	dbg::trace tr("cpptype", DBG_HERE);
	return is_const;
}

std::string cpptype::toString()
{
	std::string tot;

	if(is_const)
		tot += "const ";

	for(int i = 0; i < qual_list.size(); ++i)
	{
		tot += qual_list[i];
	}

	return tot;
}
