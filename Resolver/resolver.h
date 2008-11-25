/*
 * resolver.h
 *
 *  Created on: Nov 7, 2008
 *      Author: wmb001
 */

#ifndef RESOLVER_H_
#define RESOLVER_H_

#include <string>
#include <vector>
#include <dbg.h>

class parser;
class plexser;
class cppclass;

struct resolver_info
{
	std::vector<std::pair<std::string, int> > headers;
	std::vector<std::string>  cheaders;
};

class resolver {
public:
	resolver(parser* h, plexser* c);
	virtual ~resolver();
	//public interfaces
	void makeMatches();
	const std::vector<std::pair<int, int> >& getMatches();

	//if cppindex = -1 empty body if cppindex = -2 hide on output
	void setMatch(int hindex, int cppindex);

	const resolver_info& getLists();
	std::string getFunctionBody(int cppindex);

private:

	void initialize();
	resolver_info my_info;

	parser* parse;
	plexser* plex;

	std::vector<cppclass>* header_classes;
	std::vector<cppclass>* cpp_classes;


};

#endif /* RESOLVER_H_ */
