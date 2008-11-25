/*
 * resolver.cpp
 *
 *  Created on: Nov 7, 2008
 *      Author: wmb001
 */

#include "parser.h"
#include "plexser.h"
#include "cppclass.h"
#include "memfunc.h"
#include "resolver.h"

resolver::resolver(parser* h, plexser* c)
	:parse(h), plex(c)
{
	// TODO Auto-generated constructor stub
	initialize();
}

resolver::~resolver() {
	// TODO Auto-generated destructor stub
}

void resolver::initialize()
{
	dbg::trace tr("resolver", DBG_HERE);
	//std::cout << "HERE" << std::endl;
	header_classes = parse->getClasses();
	//std::cout << "HERE" << std::endl;
	cpp_classes = plex->getClasses();
	//std::cout << "HERE" << std::endl;
}


//public interfaces
void resolver::makeMatches()
{
	dbg::trace tr("resolver", DBG_HERE);
	for(int i = 0; i < header_classes->size(); ++i)
	{
		for(int j = 0; j < cpp_classes->size(); ++j)
		{
			if((*header_classes)[i].getName() == (*cpp_classes)[j].getName())
			{
				dbg::out(dbg::info, "resolver") << dbg::indent() << (*header_classes)[i].getName() << ":" << std::endl;

				std::vector<memfunc> h_funcs = (*header_classes)[i].get_funcs();
				std::vector<memfunc> cpp_funcs = (*cpp_classes)[j].get_funcs();
				std::vector<int> used_cpps;
				for(int k = 0; k < h_funcs.size(); ++k)
				{
					bool found = false;
					for(int l = 0; l < cpp_funcs.size(); ++l)
					{

						if(h_funcs[k] == cpp_funcs[l])
						{
							std::pair<std::string, int> p(h_funcs[k].toString(), my_info.cheaders.size());
							my_info.headers.push_back(p);
							my_info.cheaders.push_back(cpp_funcs[l].toString());
							dbg::out(dbg::info, "resolver") <<"**" << dbg::indent() << h_funcs[k].toString() << std::endl;
							dbg::out(dbg::info, "resolver") <<"**" << dbg::indent() << "matches" << std::endl;
							dbg::out(dbg::info, "resolver") <<"**" << dbg::indent() << cpp_funcs[l].toString() << std::endl;
							used_cpps.push_back(l);
							found = true;
							break;
						}

					}

					if(!found)
					{
						dbg::out(dbg::info, "resolver") << dbg::indent() << " No Match Found" << std::endl;
						std::pair<std::string, int> p(h_funcs[k].toString(), -1);
						my_info.headers.push_back(p);

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
