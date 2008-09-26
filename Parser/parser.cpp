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
		//std::cout << tok << std::endl;
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


	parser::error e;

	int size;
};

void parser::parse()
{
	//std::cout << "parse" << std::endl;
	si = new state_info();
	si->lex = file_lexer;
	si->current_token = 0;

	try
	{
		inclfile();
	}
	catch(parser::error& e)
	{
		std::cout << "(" << e.tok.line() << ", "<< e.tok.column() << ") " << e.desc  << e.tok.text()<< std:: endl;
	}

}

/**
 * Recursive Descent Parser Functions
 * Hidden here to clean up parser class and provide easy access for future changes
 */
namespace {

	void ident(parser::state_info* si)
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

			si->matchIncr(token::coloncolon);


		}
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
		ident(si);
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

	void type(parser::state_info* si)
	{
		if(si->matchText("const"))
			si->matchIncr(token::keyword, "const");
		if(si->matchType(token::keyword))
		{
			si->matchIncr(token::keyword);
		}
		else
			ident(si);

		while(si->matchType(token::lsquare))
		{
			si->matchIncr(token::lsquare);
			si->matchIncr(token::rsquare);
		}

		if(si->matchType(token::amp))
			si->matchIncr(token::amp);
		else if(si->matchType(token::ast))
			si->matchIncr(token::amp);
	}

	void mvardecl(parser::state_info* si)
	{
		type(si);
		si->matchIncr(token::identifier);
	}

	void mfunchead(parser::state_info* si)
	{
		type(si);
		si->matchIncr(token::identifier);
		si->matchIncr(token::lparen);
		//params(si);
		si->matchIncr(token::rparen);
		if(si->matchText("const"))
			si->matchIncr(token::keyword, "const");
	}

	void mfuncdecl(parser::state_info* si)
	{
		if(si->matchText("virtual"))
			si->matchIncr(token::keyword, "virtual");
		else if(si->matchText("inline"))
			si->matchIncr(token::keyword, "inline");

		mfunchead(si);
		if(si->matchType(token::semi)) //prototype
			si->matchIncr(token::semi);
		else if(si->matchType(token::eq)) // pure virtual (should virtual be a requirement here I suppose it does)
		{
			si->matchIncr(token::eq);
			si->matchIncr(token::number, "0");
			si->matchIncr(token::semi);
		}
		else if(si->matchType(token::lcurly)) //will handle inline functions
		{
			//mfuncbody         should we keep this as one unit or break it down  Its already going to be broken down but it is possible to skip everything
		}
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
		if(si->matchText("namespace"))
		{
				si->matchIncr(token::keyword, "namespace"); // namespace
				ident(si); // identifier
		}
		else
		{
			ident(si);
			si->matchType(token::identifier);
		}

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
	//std::cout << "inclfile" << std::endl;
	entities(si);
}
