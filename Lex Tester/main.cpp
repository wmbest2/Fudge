/*
 * main.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */
#include <fstream>
#include <iostream>
#include <lexer.h>

int main()
{
	std::ifstream* test_stream = new std::ifstream();
	test_stream->open("Configuration.h");
	lexer my_lexer(test_stream);
	my_lexer.tokenize();
	test_stream->close();
	delete test_stream;
	return 0;
}
