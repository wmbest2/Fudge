/*
 * main.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */
#include <fstream>
#include <iostream>
#include "plexser.h"
#include <dbg.h>

int main()
{

	dbg::enable(dbg::all, "plexser", true);
	dbg::attach_ostream(dbg::all, "plexser", std::cout);

	dbg::enable(dbg::all, "parser_helpers", true);
	dbg::attach_ostream(dbg::all, "parser_helpers", std::cout);
	//lexer my_lexer("testhfile.h");
	//my_lexer.tokenize();

	plexser my_parser("../GenHelpers/cppclass.cpp");
	my_parser.tokenize();;
	return 0;
}
