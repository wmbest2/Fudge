/*
 * main.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */
#include <fstream>
#include <iostream>
#include "parser.h"
#include "plexser.h"
#include "resolver.h"
#include <dbg.h>

int main()
{

	dbg::enable(dbg::all, "plexser", false);
	dbg::attach_ostream(dbg::all, "plexser", std::cout);

	dbg::enable(dbg::all, "parser_helpers", false);
	dbg::attach_ostream(dbg::all, "parser_helpers", std::cout);

	dbg::enable(dbg::all, "resolver", true);
	dbg::attach_ostream(dbg::all, "resolver", std::cout);


	std::cout << "Before Parse" << std::endl;
	parser my_parser("../GenHelpers/cppclass.h");
	my_parser.parse();
	std::cout << "Before Plex" << std::endl;
	plexser my_plexser("../GenHelpers/cppclass.cpp");
	my_plexser.tokenize();
	std::cout << "Before Resolve" << std::endl;
	resolver my_resolver(&my_parser, &my_plexser);
	my_resolver.makeMatches();
	std::cout << "Before Match" << std::endl;
	//my_resolver.setMatch(2,-2);
	std::cout << "Before Finalize" << std::endl;
	output_object o = my_resolver.finalize();
	std::cout << "Before Print" << std::endl;
	for(int i = 0; i < o.functions.size(); ++i)
	{
		std::cout << o.functions[i].first << o.functions[i].second << std::endl;
	}

	std::cout << "Done" << std::endl;
	return 0;
}
