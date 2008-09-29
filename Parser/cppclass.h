/*
 * cppclass.h
 *
 *  Created on: Sep 28, 2008
 *      Author: wmb001
 */

#ifndef CPPCLASS_H_
#define CPPCLASS_H_

#include <string>
#include <vector>
#include "memfunc.h"

class cppclass
{
public:
	cppclass();
	cppclass(const std::string& n);

	void addfunc(memfunc f);



private:

	std::vector<std::string> base_classes;
	std::vector<memfunc> functions;

	std::string name;
};

#endif /* CPPCLASS_H_ */
