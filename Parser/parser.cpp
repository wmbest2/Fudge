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

	bool matchType(token::TOKENTYPE t)
	{
		return (t == getCurrent().type());
	}

	void si->matchIncr(token::TOKENTYPE tok)
	{
		if(matchType(tok))
		{
			std::cout << si->text() << std::endl;
			++current_token;
		}
		else
			throw e;
	}

	void si->matchIncr(token::TOKENTYPE tok, const std::string& txt)
	{
		if(matchType(tok) && matchText(txt))
		{
			++current_token;
		}
		else
			throw e;
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
	inclfile();

}

/**
 * Recursive Descent Parser Functions
 * Hidden here to clean up parser class and provide easy access for future changes
 */
namespace {






	void ifdefdir(parser::state_info* si)
	{
		if(si->matchText("ifdef") || si->matchText("ifndef"))
		{
			si->matchIncr(token::keyword);
			si->matchIncr(token::identifier);
		}
		else if(si->matchText("endif"))
		{
			si->matchIncr(token::keyword);
		}

	}
	void defdir(parser::state_info* si)
	{
		 if (si->matchText("define"))
		 {
			si->matchIncr(token::keyword);
			si->matchIncr(token::identifier);
			if(si->matchType(token::eq))
			{
				si->matchIncr(token::eq);
				// must be char, string, or num literal
				if(si->matchType(token::charliteral) || si->matchType(token::stringliteral) || si->matchType(token::number))
					si->matchIncr(si->type());
			}
		 }
	}

	void incldir(parser::state_info* si)
	{
		si->matchIncr(token::keyword);
		if(si->matchType(token::great))
		{
			si->matchIncr(token::great);
			si->matchIncr(token::identifier);
			si->matchIncr(token::less);
		}
		else
		{
			si->matchIncr(token::stringliteral);
		}
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
		si->matchIncr(token::keyword);
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
