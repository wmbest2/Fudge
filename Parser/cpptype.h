/*
 * cpptype.h
 *
 *  Created on: Sep 28, 2008
 *      Author: wmb001
 */

#ifndef CPPTYPE_H_
#define CPPTYPE_H_

#include <string>
#include <vector>

class cpptype
{
public:
	cpptype();

	void addQual(std::string q);

	void setConst(bool c);
	bool getConst();

private:

	//including all *, &, [] and scope operators
	std::vector<std::string> qual_list;

	bool is_const;
};

#endif /* CPPTYPE_H_ */
