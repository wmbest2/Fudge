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
class cppnamespace;
class cppclass;
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

	std::vector<cppclass> getClasses();

	std::string getFileName();

	//const std::string& typetostring(TOKENTYPE t);

	void tokenize();



private:
	void initializeKeywords();
	void initializeOperators();
	void initializePreProc();
	void eatWhiteSpace();
	void eatComments();
	void NonGenerated(char first);
	void buildFuncHeader(char first, std::pair<std::string, char> cur);
	void postProcess();


	/**
	 * Functions for breaking down a function
	 */
	//checks to see if there is a type followed by text(function name) if not it returns false
	bool hasReturnType();
	void setReturnType(memfunc& f);
	void setName(memfunc& f);
	void setParamList(memfunc& f);
	void setConst(memfunc& f);
	void setBody(memfunc& f);



	char getChar();
	cppclass& getClass(const std::string& name);

	std::pair<std::string, char> nextToken(char first);

	std::ifstream* input;
	std::map<std::string, cppclass> classes;

	std::string filename;

	int lineNum;
	int columnNum;

	PLEXSTATE state;
};

#endif /* PLEXSER_H_ */
