/*
 * resolver.cpp
 *
 *  Created on: Nov 7, 2008
 *      Author: wmb001
 */

#include "cppclass.h"
#include "memfunc.h"
#include "resolver.h"

resolver::resolver() {
	// TODO Auto-generated constructor stub
	initialize();
}

resolver::~resolver() {
	// TODO Auto-generated destructor stub
}

void resolver::initialize()
{
	for(int i = 0; i < header_classes.size(); ++i)
	{
		const std::vector<memfunc>& h_funcs = headers_classes[i].get_funcs();

	}

	for(int j = 0; j < cpp_classes.size(); ++j)
	{
		const std::vector<memfunc>& cpp_funcs = headers_classes[i].get_funcs();
	}
}


//public interfaces
void resolver::makeMatches()
{
	for(int i = 0; i < header_classes.size(); ++i)
	{
		for(int j = 0; j < cpp_classes.size(); ++j)
		{
			if(header_classes[i].getName() == cpp_classes[j].getName())
			{
				makeMatches!
			}
		}
	}
}

//if cppindex = -1 empty body if cppindex = -2 hide on output
void resolver::setMatch(int hindex, int cppindex)
{
	my_info.headers[i].second = cppindex;
}

const resolver_info& resolver::getLists()
{
	return my_info;
}
std::string resolver::getFunctionBody(int cppindex)
{

}
