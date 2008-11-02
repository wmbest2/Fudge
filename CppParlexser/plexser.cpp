/*
 * plexser.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */

#include "plexser.h"


plexser::plexser()
	:state(plexser::skiptogen)
{
	// TODO Auto-generated constructor stub
	GENCOMMENT = "/*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\\\n *      Do not Touch Headers Below       *\n * Generated by Bills CPP file generator *\n \\*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*/";
}

plexser::plexser(const std::string& file)
	:input(new std::ifstream()), state(plexser::skiptogen), filename(file)
{
	input->open(filename.c_str());
;
	GENCOMMENT = "/*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\\\n *      Do not Touch Headers Below       *\n * Generated by Bills CPP file generator *\n \\*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*/";
}

plexser::plexser(std::ifstream* i)
	:input(i), state(plexser::skiptogen)
{
	// TODO Auto-generated constructor stub
	GENCOMMENT = "/*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\\\n *      Do not Touch Headers Below       *\n * Generated by Bills CPP file generator *\n \\*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*/";
}

plexser::~plexser() {
	// TODO Auto-generated destructor stub
}

void plexser::setFstream(const std::string& file)
{
	filename = file;
	input->open(file.c_str());
}

std::string plexser::getFileName()
{
	return filename;
}

int plexser::getSize()
{
	return (int)cpptokens.size();
}

cpptoken plexser::get_token(unsigned int i)
{

	if(i >= 0 && i < cpptokens.size())
		return cpptokens[i];
	else
	{
		cpptoken newtok(cpptoken::invalid, "INVALID", -1, -1);
		return newtok;
	}
}

bool plexser::find(const std::string& txt_to_find, int start, const std::string& terminator)
{
	cpptoken newtok(cpptoken::invalid, "INVALID", -1, -1);
	int count = 0;
	while(newtok.text() != terminator)
	{
		if(get_token(start + count).text() == txt_to_find)
		{
			return true;
		}

		++count;
	}

	return false;
}

void plexser::tokenize()
{
	char current;
	input->seekg(0);
	lineNum = 1;
	columnNum = 1;
	current = getChar();
	while(!input->eof())
	{
		//std::cout << "HERE" << std::endl;
		//std::cout << current << std::endl;

		/*if(isspace(current))
		{
			eatWhiteSpace();
		}
		else if(current == '/' && (input->peek() == '/' || input->peek() == '*'))
		{
			eatComments();
		}
		else */
		if(state == plexser::skiptogen)
		{
			NonGenerated(current);
		}
		else if(state == plexser::funcheader)
		{
			buildFuncHeader(current);
		}

		current = getChar();

	}


	postProcess();
}

void plexser::NonGenerated(char first)
{
	int line = lineNum;
	int col = columnNum;
	std::string junk, comment;
	char tmp = first;
	while(!input->eof() && state == skiptogen)
	{

		//std::cout << tmp;
		//junk += tmp;
		if(tmp == '/')
		{
			comment = '/';
			tmp = getChar();
			if(tmp == '*')
				{
					comment += tmp;
					bool exit = false;
					while(!exit && !input->eof())
					{
						tmp = getChar();

						if(tmp == '*' && input->peek() == '/')
						{
							comment += tmp;
							exit = true;
							tmp = getChar();
						}
						comment += tmp;
					}

				}
			if(comment == GENCOMMENT)
			{
				state = funcheader;
			}
			else
				junk += comment;
		}
		else
			junk += tmp;

		tmp = getChar();

	}

	cpptoken newToken(cpptoken::cppjunk, junk, line, col);
	cpptokens.push_back(newToken);

}

void plexser::builtFuncHeader(char first)
{

}

void plexser::eatWhiteSpace()
{
	char current;
	current = input->peek();
	while(isspace(current) && !input->eof())
	{
		getChar();
		current = input->peek();
	}

	// YUM
}

void plexser::eatComments()
{
	char current;
	current = input->peek();

	if(current == '/')
	{
		char tmp;
		while(tmp != '\n' && !input->eof())
			tmp = getChar();

	}
	else if(current == '*')
	{
		char tmp;
		bool exit = false;
		while(!exit && !input->eof())
		{
			tmp = getChar();

			if(tmp == '*' && input->peek() == '/')
			{
				exit = true;
				tmp = getChar();
			}
		}

	}

	// YUM
}

void plexser::postProcess()
{

}


/*void plexser::eatPreProc(char first)
{
	//Eat the rest
	char tmp;
	char lastchar;
	int line = lineNum;
	int col = columnNum;
	std::string tok;
	tok += first;
	bool exit = false;
	while(!exit && !input->eof())
	{

		tmp = (char)getChar();
		tok += tmp;



		if(tmp == '\n' && lastchar != '\\')
		{
			exit = true;
		}

		lastchar = tmp;
	}

	cpptoken newToken(cpptoken::ppjunk, tok, line, col);
	cpptokens.push_back(newToken);


}
*/
char plexser::getChar()
{
	if(!input->eof())
	{
		char tmp;
		tmp = input->get();
		if(tmp == '\n'){
			++lineNum;
			columnNum = 1;
		}
		else
		{
			++columnNum;
		}
		return tmp;
	}
	return -1;

}

bool plexser::checkTripleOp(char first)
{
	std::string tokinquest;
	tokinquest = first;
	tokinquest += input->get();
	tokinquest += input->peek();

	input->unget();
	return opers.find(tokinquest) != opers.end();
}

bool plexser::checkDoubleOp(char first)
{
	std::string tokinquest;
	tokinquest = first;
	tokinquest += input->peek();
	return opers.find(tokinquest) != opers.end();
}

bool plexser::checkSingleOp(char first)
{
	std::string tokinquest;
	tokinquest = first;
	return opers.find(tokinquest) != opers.end();
}

/*cpptoken plexser::buildString()
{

	std::string tok;
	tok += '"';
	char tmp = getChar();
	while(tmp != '"' && !input->eof())
	{
		tok += tmp;
		tmp = getChar();
	}
	tok += tmp;
	//std::cout <<  "string: " << tok << std::endl;
	cpptoken newToken(cpptoken::stringliteral, tok, lineNum, columnNum);
	return newToken;
}

cpptoken plexser::buildChar()
{
	std::string tok = "'";
	char tmp = getChar();
	tok += tmp;

	//escaped characters
	if(tmp == '\\')
	{
		tmp = getChar();
		tok += tmp;
	}

	// get other '
	tmp = getChar();
	tok += tmp;
	//std::cout << tok << std::endl;
	cpptoken newToken(cpptoken::charliteral, tok, lineNum, columnNum);
	return newToken;
}

cpptoken plexser::buildKeyOrID(char first)
{
	std::string tok;
	tok += first;
	char current = input->peek();
	while((isalnum(current) || current == '_') && !input->eof())
	{
		getChar();
		tok += current;
		current = input->peek();
	}

	//std::cout << tok << std::endl;

	cpptoken::TOKENTYPE cpptokenID;
	if(keys.find(tok) != keys.end())
		cpptokenID = keys[tok].type();
	else
		cpptokenID = cpptoken::identifier;

	cpptoken newToken(cpptokenID, tok, lineNum, columnNum - tok.size());
	return newToken;

}

cpptoken plexser::buildPreProcDir(char first)
{
	cpptoken pptok = buildKeyOrID(first);
	//if(pptok.type() == cpptoken::identifier) // not needed because "if" is a keyword and a pp directive
	{
		if(preprocs.find(pptok.text()) != preprocs.end())
		{
			pptok.type(preprocs[pptok.text()].type());
			//std::cout << pptok.text() << std::endl;
			return pptok;
		}

	}
	cpptoken invalid;
	return invalid;
}

cpptoken plexser::buildNumber(char first)
{
	std::string tok;
	tok += first;
	char current = input->peek();

	int periodcount = 0;
	while((isdigit(current) || current == '.') && !input->eof())
	{
		getChar();
		if(current == '.')
		{
			if(periodcount == 0)
				++periodcount;
			else
			{
				cpptoken newToken(cpptoken::invalid, tok, lineNum, columnNum - tok.size());
				handleException(newToken);
			}
		}
		tok += current;
		current = input->peek();
	}
	//std::cout << tok << std::endl;
	cpptoken newToken(cpptoken::number, tok, lineNum, columnNum - tok.size());
	return newToken;
}

cpptoken plexser::buildTripleOp(char first)
{
	std::string tok;
	tok = first;
	tok += getChar();
	tok += getChar();
	cpptoken newToken = opers.find(tok)->second;
	newToken.line(lineNum);
	newToken.column(columnNum - 3);
	return newToken;
}

cpptoken plexser::buildDoubleOp(char first)
{
	std::string tok;
	tok = first;
	tok += getChar();
	//std::cout << tok << std::endl;
	cpptoken newToken = opers.find(tok)->second;
	newToken.line(lineNum);
	newToken.column(columnNum - 2);
	return newToken;
}

cpptoken plexser::buildSingleOp(char first)
{
	std::string tok;
	tok = first;
	//std::cout << tok << std::endl;
	cpptoken newToken = opers.find(tok)->second;
	newToken.line(lineNum);
	newToken.column(columnNum - 1);
	return newToken;
}*/

void plexser::handleException(cpptoken problem)
{
	//std::cout << "********** line "  << problem.line() << " column " << problem.column() << ": \'" << problem.text() << "\'" << std::endl;
}

