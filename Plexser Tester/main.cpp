/*
 * main.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */
#include <fstream>
#include <iostream>
#include "plexser.h"

int main()
{


	//lexer my_lexer("testhfile.h");
	//my_lexer.tokenize();

	plexser my_parser("test_h_file.cpp");
	my_parser.tokenize();;
	return 0;
}
