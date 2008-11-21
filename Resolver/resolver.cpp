/*
 * resolver.cpp
 *
 *  Created on: Nov 7, 2008
 *      Author: wmb001
 */

#include "cppclass.h"
#include "memfunc.h"
#include "resolver.h"

resolver::resolver(std::vector<cppclass> h, std::vector<cppclass> c)
	:header_classes(h), cpp_classes(c)
{
	// TODO Auto-generated constructor stub
	initialize();
}

resolver::~resolver() {
	// TODO Auto-generated destructor stub
}

void resolver::initialize()
{
	std::cout << "JHERE" << std::endl;
	dbg::trace tr("resolver", DBG_HERE);
	/*for(int i = 0; i < header_classes.size(); ++i)
	{
		const std::vector<memfunc>& h_funcs = headers_classes[i].get_funcs();

	}

	for(int j = 0; j < cpp_classes.size(); ++j)
	{
		const std::vector<memfunc>& cpp_funcs = headers_classes[i].get_funcs();
	}*/
}


//public interfaces
void resolver::makeMatches()
{
	dbg::trace tr("resolver", DBG_HERE);
	for(int i = 0; i < header_classes.size(); ++i)
	{
		for(int j = 0; j < cpp_classes.size(); ++j)
		{
			if(header_classes[i].getName() == cpp_classes[j].getName())
			{
				std::vector<memfunc> h_funcs = header_classes[i].get_funcs();
				std::vector<memfunc> cpp_funcs = cpp_classes[j].get_funcs();
				std::vector<int> used_cpps;
				for(int k = 0; k < h_funcs.size(); ++k)
				{
					for(int l = 0; i < cpp_funcs.size(); ++l)
					{
						if(h_funcs[k] == cpp_funcs[l])
						{
							std::pair<std::string, int> p(h_funcs[k].toString(), my_info.cheaders.size());
							my_info.headers.push_back(p);
							my_info.cheaders.push_back(cpp_funcs[l].toString());
							used_cpps.push_back(l);
							break;
						}
						else
						{
							std::pair<std::string, int> p(h_funcs[k].toString(), -1);
							my_info.headers.push_back(p);

						}
					}
				}

			}
		}
	}
}

//if cppindex = -1 empty body if cppindex = -2 hide on output
void resolver::setMatch(int hindex, int cppindex)
{
	my_info.headers[hindex].second = cppindex;
}

const resolver_info& resolver::getLists()
{
	return my_info;
}
std::string resolver::getFunctionBody(int cppindex)
{

}
