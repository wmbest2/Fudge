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
	dbg::enable(dbg::all, "cppclass", true);
	dbg::attach_ostream(dbg::all, "cppclass", std::cout);

	dbg::enable(dbg::all, "parser_helpers", true);
	dbg::attach_ostream(dbg::all, "parser_helpers", std::cout);


	//lexer my_lexer("testhfile.h");
	//my_lexer.tokenize();

	parser my_parser("testhfile2.h");
	my_parser.parse();
	my_parser.cppOutput("test_h_file2.cpp");
	return 0;
}
