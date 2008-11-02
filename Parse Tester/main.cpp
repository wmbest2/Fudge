/*
 * main.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */
#include <fstream>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include <dbg.h>

int main()
{
	dbg::enable(dbg::all, "cppclass", false);
	dbg::attach_ostream(dbg::all, "cppclass", std::cout);

	dbg::enable(dbg::all, "parser_helpers", false);
	dbg::attach_ostream(dbg::all, "parser_helpers", std::cout);


	//lexer my_lexer("testhfile.h");
	//my_lexer.tokenize();

	parser my_parser("test_h_file.h");
	my_parser.parse();
	my_parser.cppOutput("test_h_file.cpp");
	return 0;
}
