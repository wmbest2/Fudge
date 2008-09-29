/*
 * cppvar.h
 *
 *  Created on: Sep 29, 2008
 *      Author: wmb001
 */

#ifndef CPPVAR_H_
#define CPPVAR_H_

#include <string>
#include "cpptype.h"

class cppvar
{
public:
	cppvar();
	cppvar(cpptype t, std::string i, std::string iv);

private:

	cpptype type;
	std::string id;
	std::string init_val;

};

#endif /* CPPVAR_H_ */
