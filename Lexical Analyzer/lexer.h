/*
 * lexer.h
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "token.h"

class lexer {
public:
	lexer();
	lexer(std::ifstream* i);
	virtual ~lexer();

	void setFstream(const std::string& file);

	std::vector<token>& get_tokens();
	token get_token(int i);
	void tokenize();



private:
	void initializeKeywords();
	void initializeOperators();
	void initializePreProc();
	void eatWhiteSpace();
	void eatComments();
	void eatPreProc();
	void postProcess();

	bool checkTripleOp(char first);
	bool checkDoubleOp(char first);
	bool checkSingleOp(char first);

	char getChar();

	token buildString();
	token buildChar();
	token buildKeyOrID(char first);
	token buildNumber(char first);
	token buildTripleOp(char first);
	token buildDoubleOp(char first);
	token buildSingleOp(char first);

	void handleException(token problem);

	std::ifstream* input;
	std::vector<token> tokens;
	std::map<std::string, token> keys;
	std::map<std::string, token> opers;

	int lineNum;
	int columnNum;
};

#endif /* LEXER_H_ */