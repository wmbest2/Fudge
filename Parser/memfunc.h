/*
 * memfunc.h
 *
 *  Created on: Sep 28, 2008
 *      Author: wmb001
 */

#ifndef MEMFUNC_H_
#define MEMFUNC_H_

#include <string>
#include <vector>
#include "cppvar.h"
#include "cpptype.h"

class memfunc
{
public:

	memfunc();
	memfunc(std::string n, bool v, bool c, bool p, bool s);

	void setReturn(cpptype t);

	void addParam(cppvar p);

private:
	std::string name;
	bool is_virtual;
	bool is_const;
	bool is_pure;
	bool is_static;

	cpptype return_type;
	std::vector<cppvar> params;
};

#endif /* MEMFUNC_H_ */
