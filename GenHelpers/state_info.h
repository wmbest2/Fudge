/*
 * state_info.h
 *
 *  Created on: Nov 3, 2008
 *      Author: wmb001
 */

#ifndef STATE_INFO_H_
#define STATE_INFO_H_

#include <stack>
#include "token.h"
#include "stackable.h"

struct error
{

	int token_loc;
	token tok;
	std::string desc;

	error()
		:token_loc(-1), desc("invalid error object")
	{}

	error(int tl, const std::string& d)
		:token_loc(tl), desc(d)
	{
	}

};

struct state_info
{
	lexer* lex;
	int current_token;
	std::stack<stackable*> obj_stack;

	template<typename T>
	T* getStack()
	{
		std::cout << "JHHSKAAFJS" << std::endl;
		stackitem<T>* tmp = dynamic_cast<stackitem<T>*>(obj_stack.top());
		return (T*)tmp->getcur();
	}

	template <typename T>
	void pushStack(T* p)
	{
		obj_stack.push((stackable *)(new stackitem<T>(p)));
	}

	void popStack()
	{
		obj_stack.pop();
	}


	token getCurrent()
	{
		return lex->get_token(current_token);
	}

	token getAt(int i)
	{
		return lex->get_token(i);
	}

	bool hasTokens()
	{
		return current_token == lex->getSize() - 1;
	}

	std::string text()
	{
		return getCurrent().text();
	}

	token::TOKENTYPE type()
	{
		return getCurrent().type();
	}

	bool matchText(const std::string& t)
	{
		return (t == getCurrent().text());
	}

	bool matchText(const std::string& t, int advancement)
	{
		return (t == getAt(current_token + advancement).text());
	}

	bool matchType(token::TOKENTYPE t)
	{
		return (t == getCurrent().type());
	}

	void incr()
	{
		++current_token;
	}

	void incr(int i)
	{
		current_token += i;
	}

	bool matchType(token::TOKENTYPE t, int advancement)
	{
		return (t == getAt(current_token + advancement).type());
	}

	void matchIncr(token::TOKENTYPE tok)
	{
		if(matchType(tok))
		{
			incr();
		}
		else
		{
			e.token_loc = current_token;
			token tmp = getCurrent();
			e.tok = tmp;
			e.desc ="There was an error matching token ";

			throw e;
		}

	}

	void matchIncr(token::TOKENTYPE tok, const std::string& txt)
	{
		if(matchType(tok) && matchText(txt))
		{
			incr();
		}
		else
		{
			e.token_loc = current_token;
			token tmp = getCurrent();
			e.tok = tmp;
			e.desc ="There was an error matching token ";

			throw e;
		}
	}

	/******************************************
	 *             retrieve objects           *
	 ******************************************/

	cppnamespace current_namespace;

	error e;
	int size;
};

#endif /* STATE_INFO_H_ */
