/*
 * parser.cpp
 *
 *  Created on: Sep 9, 2008
 *      Author: wmb001
 */

#include "parser.h"

parser::parser()
	:file_lexer(new lexer())
{
	// TODO Auto-generated constructor stub

}

parser::parser(lexer* lex)
	:file_lexer(lex)
{

}

parser::~parser() {
	// TODO Auto-generated destructor stub
}



struct parser::error
{
	error()
		token_loc(-1), desc("invalid error object")
	{}
	
	error(int tl, const std::string& d)
		:token_loc(tl), desc(d)
	{
	}
	
	int token_loc;
	token tok;
	std::string desc;
};

struct parser::state_info
{
	lexer* lex;
	int current_token;

	token getCurrent()
	{
		return lex->get_token(current_token);
	}

	token getAt(int i)
	{
		return lex->get_token(i);
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
			incr()
		}
		else
		{
			e.token_loc = current_token;
			token tmp = getCurrent();
			e.tok = tmp;
			e.desc ="There was an error matching token to type ";

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
			e.desc ="There was an error matching token to type ";

			throw e;
		}
	}


	parser::error e;

	int size;
};

void parser::parse()
{
	std::cout << "parse" << std::endl;
	si = new state_info();
	si->lex = file_lexer;
	si->current_token = 0;

	try
	{
		inclfile();
	}
	catch(parser::error& e)
	{
		std::cout << e.desc << std:: endl;
	}

}

/**
 * Recursive Descent Parser Functions
 * Hidden here to clean up parser class and provide easy access for future changes
 */
namespace {

	void q(parser::state_info* si)
	{

	}

	void qlist(parser::state_info* si)
	{
		if(si->matchType(token::coloncolon))
			si->matchIncr(token::coloncolon);
		while(true)
		{
			si->matchIncr(token::identifier);
			
			if(!si->matchType(token::coloncolon))
			{
				break;
			}
			
			// build identifier object here
				
		}
	}

	void ident(parser::state_info* si)
	{
		qlist(si);
		si->matchIncr(token::identifier);
	}

	void ifdefdir(parser::state_info* si)
	{
		if(si->matchText("ifdef"))
		{
			si->matchIncr(token::ifdef);

		}
		else if(si->matchText("ifndef"))
		{
			si->matchIncr(token::ifndef);
		}
		else if(si->matchText("endif"))
		{
			si->matchIncr(token::endif);
		}
		si->matchIncr(token::ppjunk);

	}
	void defdir(parser::state_info* si)
	{
		si->matchIncr(token::define);
		si->matchIncr(token::ppjunk);

	}

	void incldir(parser::state_info* si)
	{
		si->matchIncr(token::include);
		si->matchIncr(token::ppjunk);
	}


	void preproc(parser::state_info* si)
	{
		si->matchIncr(token::pound);
		if(si->matchText("ifdef") || si->matchText("ifndef") || si->matchText("endif"))
			ifdefdir(si);
		else if (si->matchText("define"))
			defdir(si);
		else if(si->matchText("include"))
			incldir(si);

	}

	void baseclass(parser::state_info* si)
	{
		si->matchIncr(token::keyword);
		si->matchIncr(token::identifier);
	}

	void baseclasses(parser::state_info* si)
	{

		baseclass(si);
		if(si->matchType(token::comma))
		{
			si->matchIncr(token::comma);
			baseclasses(si);
		}
	}

	void access_scope(parser::state_info* si)
	{
		si->matchIncr(token::keyword);
		si->matchIncr(token::colon);
	}

	void mdecls(parser::state_info* si)
	{
		if(si->matchText("public") || si->matchText("private") || si->matchText("protected") )
		{
			 access_scope(si);
		}
		else if(true)
		{
				//stuff for member variable, functions and other decls
		}
	}

	void classbody(parser::state_info* si)
	{
		si->matchIncr(token::lcurly);
		mdecls(si);
		si->matchIncr(token::rcurly);
		si->matchIncr(token::semi);

	}

	void classdecl(parser::state_info* si)
	{
		si->matchIncr(token::keyword);
		si->matchIncr(token::identifier);
		if(si->matchType(token::colon))
		{
			si->matchIncr(token::colon);
			baseclasses(si);
		}

		classbody(si);
	}

	void gfuncdecl(parser::state_info* si)
	{

	}

	void gvardecl(parser::state_info* si)
	{

	}

	void decls(parser::state_info* si);

	void nspacebody(parser::state_info* si)
	{
		si->matchIncr(token::lcurly);
		decls(si);
		si->matchIncr(token::rcurly);
	}

	void nspacedecl(parser::state_info* si)
	{
		si->matchIncr(token::keyword, "namespace");
		if(si->matchType(token::identifier))  // this will handle empty namespaces
			si->matchIncr(token::identifier);

		nspacebody(si);
	}

	void usingnsdecl(parser::state_info* si)
	{
		 // using
		si->matchIncr(token::keyword, "namespace"); // namespace
		si->matchIncr(token::identifier); // identifier
		si->matchIncr(token::semi);
	}

	void decls(parser::state_info* si)
	{
		if(si->matchType(token::keyword))
		{
			if(si->matchText("class"))
			{
				classdecl(si);
			}
			else if(si->matchText("namespace"))
			{
				nspacedecl(si);
			}
			else if(si->matchText("using"))
			{
				si->matchIncr(token::keyword, "using");

				if(si->matchText("namespace"))
					usingnsdecl(si);
			}
		}

		/*if(isGFunc(si))
			gfuncdecl(si);
		else
			gvardecl(si);*/
	}



	void entity(parser::state_info* si)
	{
		if(si->matchType(token::pound))
			preproc(si);
		else
			decls(si);
	}
	void entities(parser::state_info* si)
	{
		while(!si->matchType(token::invalid))
		{
			entity(si);
		}
	}

}


void parser::inclfile()
{
	std::cout << "inclfile" << std::endl;
	entities(si);
}
