/*
 * resolver.h
 *
 *  Created on: Nov 7, 2008
 *      Author: wmb001
 */

#ifndef RESOLVER_H_
#define RESOLVER_H_

class resolver {
public:
	resolver();
	virtual ~resolver();
	//public interfaces
	void makeMatches();
	const std::vector<std::pair<int, int> >& getMatches();

	//if cppindex = -1 empty body if no match made hide on output
	void setMatch(int hindex, int cppindex);


	const std::vector<std::string>& getHFileHeaders();
	const std::vector<std::string>& getCFileHeaders();
	std::string getFunctionBody(int cppindex);

private:
	std::vector<std::pair<int, int> > matched;
	std::vector<std::string> hfilenames;
	std::vector<std::string> cfilenames;

};

#endif /* RESOLVER_H_ */
