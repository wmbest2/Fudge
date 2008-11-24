/*
 * cppclass.h
 *
 *  Created on: Sep 28, 2008
 *      Author: wmb001
 */

#ifndef CPPCLASS_H_
#define CPPCLASS_H_

#include <fstream>
#include <string>
#include <vector>
#include "memfunc.h"
#include "memfuncstr.h"
#include <dbg.h>
#include <iostream>

#include "cppnamespace.h"

class cppclass
{
public:
	cppclass();
	cppclass(const std::string& n);

	void addfunc(memfunc f);
	void addbaseclass(const std::string& access, const std::string& ident);
	void setname(const std::string& ident);
	void setNamespace(cppnamespace n);
	const std::vector<memfunc>& get_funcs();
	cppnamespace getNamespace();
	std::string getName() const;
	std::string getQual();
	void print();
	const std::vector<ref*>& cppOutput();
	void cppOutput(const std::string& file);

private:

	std::vector<std::pair<std::string,std::string> > base_classes;
	std::vector<memfunc> functions;

	std::string prefuncout;
	std::string postfuncout;
	std::vector<ref*> outputrefs;


	cppnamespace owner;
	std::string name;
};

#endif /* CPPCLASS_H_ */
