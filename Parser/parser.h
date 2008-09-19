/*
 * parser.h
 *
 *  Created on: Sep 9, 2008
 *      Author: wmb001
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"

class parser {
public:


	struct error;
	struct state_info;

	parser();
	parser(lexer* lex);

	virtual ~parser();

	void parse();



private:

	void inclfile();

	lexer* file_lexer;
	state_info* si;

};

#endif /* PARSER_H_ */
