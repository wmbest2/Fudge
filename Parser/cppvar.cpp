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
