/*
 * parser.h
 *
 *  Created on: Sep 9, 2008
 *      Author: wmb001
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stack>

#include "cppvar.h"
#include "stackable.h"
#include "cppclass.h"
#include "memfunc.h"
#include "cppnamespace.h"
#include <dbg.h>
#include <fstream>

class lexer;
struct state_info;
struct error;

class parser {
public:




	parser();
	parser(const std::string& filename);
	parser(lexer* lex);

	virtual ~parser();

	void parse();
	void cppOutput(const std::string& filename);
	std::vector<cppclass> getClasses();



private:

	void inclfile();

	lexer* file_lexer;
	state_info* si;

};



#endif /* PARSER_H_ */
