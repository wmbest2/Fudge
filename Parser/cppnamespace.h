/*
 * cpptemplate.h
 *
 *  Created on: Oct 16, 2008
 *      Author: Bill
 */

#ifndef CPPNAMESPACE_H_
#define CPPNAMESPACE_H_

#include <string>

class cppnamespace
{
public:
	cppnamespace();
	cppnamespace(const std::string& i);

	void setName(const std::string& i);
	std::string getName();
private:
	std::string id;
};

#endif /* CPPNAMESPACE_H_ */
