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
	parser my_parser("test_h_file.h");
	my_parser.parse();
	std::cout << "Before Plex" << std::endl;
	plexser my_plexser("test_h_file.cpp");
	my_plexser.tokenize();
	std::cout << "Before Resolve" << std::endl;
	resolver my_resolver(&my_parser, &my_plexser);
	my_resolver.makeMatches();
	std::cout << "Done" << std::endl;
	return 0;
}
