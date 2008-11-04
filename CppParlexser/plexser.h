/*
 * plexser.h
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */

#ifndef PLEXSER_H_
#define PLEXSER_H_

#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "cpptoken.h"

class plexser {
	enum PLEXSTATE
	{
		skiptogen,
		funcheader,
		funcbody,
	};

	std::string GENCOMMENT;

public:
	plexser();
	plexser(const std::string& file);
	plexser(std::ifstream* i);
	virtual ~plexser();

	void setFstream(const std::string& file);

	cpptoken get_token(unsigned int i);

	std::string getFileName();

	int getSize();
	//const std::string& typetostring(TOKENTYPE t);

	void tokenize();

	bool find(const std::string& txt_to_find, int start, const std::string& terminator);



private:
	void initializeKeywords();
	void initializeOperators();
	void initializePreProc();
	void eatWhiteSpace();
	void eatComments();
	void NonGenerated(char first);
	void buildFuncHeader(char first, std::string cur);
	void postProcess();

	bool checkTripleOp(char first);
	bool checkDoubleOp(char first);
	bool checkSingleOp(char first);

	char getChar();

	std::pair<std::string, char> nextToken(char first);
	cpptoken buildType(char first);
	cpptoken buildIdent(char first);
	cpptoken buildParamList(char first);
	cpptoken buildParam(char first);
	cpptoken buildFunctionBody(char first);

	void handleException(cpptoken problem);

	std::ifstream* input;
	std::vector<cpptoken> cpptokens;
	std::map<std::string, cpptoken> keys;
	std::map<std::string, cpptoken> opers;
	std::map<std::string, cpptoken> preprocs;

	std::string filename;

	int lineNum;
	int columnNum;

	PLEXSTATE state;
};

#endif /* PLEXSER_H_ */
