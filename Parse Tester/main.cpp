/*
 * main.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */
#include <fstream>
#include <iostream>
#include <lexer.h>
#include <parser.h>
#include <dbg.h>

int main()
{
	dbg::enable(dbg::all, "cppclass", false);
	dbg::attach_ostream(dbg::all, "cppclass", std::cout);

	dbg::enable(dbg::all, "parser_helpers", false);
	dbg::attach_ostream(dbg::all, "parser_helpers", std::cout);


	std::ifstream* test_stream = new std::ifstream();
	test_stream->open("testhfile.h");

	lexer my_lexer(test_stream);
	my_lexer.tokenize();

	parser my_parser(&my_lexer);
	my_parser.parse();
	test_stream->close();
	delete test_stream;
	return 0;
}
