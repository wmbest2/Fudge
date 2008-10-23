/*
 * cppclass.cpp
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#include "cppclass.h"

cppclass::cppclass()
	:name("invalid")
{

}

cppclass::cppclass(const std::string& n)
	:name(n)
{

}

void cppclass::addfunc(memfunc f)
{
	dbg::trace tr("cppclass", DBG_HERE);
	f.setClass(this);
	functions.push_back(f);
}

void cppclass::addbaseclass(const std::string& access, const std::string& ident)
{
	dbg::trace tr("cppclass", DBG_HERE);
	std::pair<std::string, std::string> p(access, ident);
	dbg::out(dbg::info, "cppclass") << dbg::indent() << "Added Base Class: " << access << " " << ident << "\n";
	base_classes.push_back(p);
}

void cppclass::setname(const std::string& ident)
{
	dbg::trace tr("cppclass", DBG_HERE);
	name = ident;
	dbg::out(dbg::info, "cppclass") << dbg::indent() << "Name changed to " << name << "\n";
}

void cppclass::setNamespace(cppnamespace n)
{
	owner = n;
}

cppnamespace cppclass::getNamespace()
{
	return owner;
}

std::string cppclass::getQual()
{
	return name;
}

std::string cppclass::getName()
{
	return name;
}

void cppclass::print()
{

	std::cout << "Class: " << name << std::endl;

	for(int i = 0; i < base_classes.size(); ++i)
	{
		std::cout << "Base: " << base_classes[i].second << std::endl;
	}

	for(int i = 0; i < functions.size(); ++i)
	{
		std::cout << "Function: " << functions[i].toString() << std::endl;
	}

	std::cout << std::endl;
}

std::string cppclass::cppOutput()
{
	std::string out;

	if(owner.getName() != "invalid")
	{
		out += "using " + owner.getName() + "::" + name + ";\n\n";
	}

	for(int i = 0; i < functions.size(); ++i)
	{
		out += functions[i].toString() + "\n\n";
	}

	return out;
}

void cppclass::cppOutput(const std::string& file)
{
	std::ofstream of;
	of.open(file.c_str(), std::ios_base::app);


	if(owner.getName() != "invalid")
	{
		of << "using " << owner.getName() << "::" << name << ";\n\n";
	}
	of.close();
	for(int i = 0; i < functions.size(); ++i)
	{
		functions[i].cppOutput(file);
	}

	//std::ofstream of;
	of.open(file.c_str(), std::ios_base::app);
	of << "\n\n";
	of.close();


}
