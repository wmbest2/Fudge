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
				int offset = my_info.cheaders.size();
				for(int l = 0; l < cpp_funcs.size(); ++l)
				{
					std::pair<std::string, std::string> p(cpp_funcs[l].toString(), cpp_funcs[l].getBody());
					my_info.cheaders.push_back(p);
					my_info.cpp_used.push_back(false);
				}

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
							dbg::out(dbg::info, "resolver") <<"**" << dbg::indent() << h_funcs[k].toString() << std::endl;
							dbg::out(dbg::info, "resolver") <<"**" << dbg::indent() << "matches" << std::endl;
							dbg::out(dbg::info, "resolver") <<"**" << dbg::indent() << cpp_funcs[l].toString() << std::endl;
							my_info.cpp_used[l + offset] = true;
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
	dbg::trace tr("resolver", DBG_HERE);
	if(my_info.headers[hindex].second >=0 && my_info.headers[hindex].second < my_info.headers.size())
		my_info.cpp_used[my_info.headers[hindex].second] = false;
	my_info.headers[hindex].second = cppindex;
	if(cppindex >= 0 && cppindex < my_info.cpp_used.size())
		my_info.cpp_used[cppindex] = true;

}

const resolver_info& resolver::getLists()
{
	return my_info;
}
std::string resolver::getFunctionBody(int cppindex)
{

}

output_object resolver::finalize()
{
	dbg::trace tr("resolver", DBG_HERE);
	output_object o;
	for(int i = 0; i < my_info.headers.size(); ++i)
	{
		if(my_info.headers[i].second != -2)
		{

			std::pair<std::string, std::string> p;
			p.first = my_info.headers[i].first;

			if(my_info.headers[i].second == -1)
				p.second = "\n{\n\n\n}\n";
			else
				p.second = my_info.cheaders[i].second;

			o.functions.push_back(p);
		}



	}
	return o;
}
