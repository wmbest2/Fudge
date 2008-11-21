/*
 * output_info.h
 *
 *  Created on: Nov 17, 2008
 *      Author: wmb001
 */

#ifndef OUTPUT_INFO_H_
#define OUTPUT_INFO_H_

#include <vector>
class memfunc;

struct output_info
{
	std::vector<std::pair<int, int> > matches;
	std::vector<memfunc> hfile_list;
	std::vector<memfunc> cppfile_list;
};

#endif /* OUTPUT_INFO_H_ */
