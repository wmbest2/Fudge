/*
 * stackable.h
 *
 *  Created on: Oct 2, 2008
 *      Author: wmb001
 */

#ifndef STACKABLE_H_
#define STACKABLE_H_

class stackable
{
public:
	stackable()
	{}

	stackable(const stackable& s)
	{
	}

	virtual ~stackable()
	{}
};

template <typename T>
class stackitem : public stackable
{
public:
	stackitem()
	{}

	stackitem(T* p)
		:ptr(p)
	{

	}

	stackitem(stackitem& si)
		:ptr(si.getcur())
	{

	}

	T* getcur()
	{
		return ptr;
	}

	void setcur(T* p)
	{
		ptr = p;
	}

private:
	T* ptr;
};

#endif /* STACKABLE_H_ */
