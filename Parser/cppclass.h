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
#include <dbg.h>
#include <iostream>

class cppclass
{
public:
	cppclass();
	cppclass(const std::string& n);

	void addfunc(memfunc f);
	void addbaseclass(const std::string& access, const std::string& ident);
	void setname(const std::string& ident);
	std::string getQual();
	void print();

private:

	std::vector<std::pair<std::string,std::string> > base_classes;
	std::vector<memfunc> functions;

	std::string name;
};

#endif /* CPPCLASS_H_ */
