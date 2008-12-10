/*
 * lexer.cpp
 *
 *  Created on: Sep 3, 2008
 *      Author: wmb001
 */

#include "lexer.h"


lexer::lexer()
	:state(lexer::normal)
{
	// TODO Auto-generated constructor stub
	initializeKeywords();
	initializeOperators();
	initializePreProc();
}

lexer::lexer(const std::string& file)
	:input(new std::ifstream()), state(lexer::normal), filename(file)
{
	input->open(filename.c_str());
	if(!input)
	{
		std::cout << "Couldn't Find " << filename << std::endl;
		file_not_found f;
		f.file_name = filename;
		throw f;
	}
	initializeKeywords();
	initializeOperators();
	initializePreProc();
}

lexer::lexer(std::ifstream* i)
	:input(i), state(lexer::normal)
{
	// TODO Auto-generated constructor stub
	initializeKeywords();
	initializeOperators();
	initializePreProc();
}

lexer::~lexer() {
	// TODO Auto-generated destructor stub
}

void lexer::setFstream(const std::string& file)
{
	filename = file;
	input->open(file.c_str());
}

std::vector<token>& lexer::get_tokens()
{
	return tokens;
}

std::string lexer::getFileName()
{
	return filename;
}

int lexer::getSize()
{
	return (int)tokens.size();
}

void lexer::initializeKeywords()
{
	std::ifstream keyword_list;
	char* path = getenv("HOME");
	std::string file = path;
	file += "/.fudge/";
	file += "keywords.dat";
	keyword_list.open(file.c_str());

	while(!keyword_list.eof())
	{
		std::string current_keyword;
		std::getline(keyword_list, current_keyword);
		token tmp_token(token::keyword, current_keyword, -1, -1);
		keys[current_keyword] = tmp_token;

	}
}

void lexer::initializeOperators()
{
	std::ifstream oper_list;
	char* path = getenv("HOME");
	std::string file = path;
	file += "/.fudge/";
	file += "operators.dat";
	oper_list.open(file.c_str());

	while(!oper_list.eof())
	{
		std::string tmp;
		std::string title;
		int value = 0;
		std::string current_oper;

		oper_list >> title >> value >> current_oper;
		getline(oper_list, tmp);
		token tmp_token((token::TOKENTYPE)(value), current_oper, -1, -1);
		opers[current_oper] = tmp_token;
	}
}

void lexer::initializePreProc()
{
	token tmp_token0(token::include, "include", -1, -1);
	preprocs["include"] = tmp_token0;

	token tmp_token1(token::define, "define", -1, -1);
	preprocs["define"] = tmp_token1;

	token tmp_token2(token::ifdef, "ifdef", -1, -1);
	preprocs["ifdef"] = tmp_token2;

	token tmp_token3(token::ifndef, "ifndef", -1, -1);
	preprocs["ifndef"] = tmp_token3;

	token tmp_token4(token::endif, "endif", -1, -1);
	preprocs["endif"] = tmp_token4;
}

token lexer::get_token(unsigned int i)
{

	if(i >= 0 && i < tokens.size())
		return tokens[i];
	else
	{
		token newtok(token::invalid, "INVALID", -1, -1);
		return newtok;
	}
}
/*
bool lexer::find(const std::string& txt_to_find, int start, const std::string& terminator)
{
	token newtok(token::invalid, "INVALID", -1, -1)
	int count = 0;
	while(newtok.text() != terminator)
	{
		if(get_token(start + count).text() = txt_to_find)
		{
			return true;
		}

		++count;
	}

	return false;
}*/

void lexer::tokenize()
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

		if(isspace(current))
		{
			eatWhiteSpace();
		}
		else if(current == '/' && (input->peek() == '/' || input->peek() == '*'))
		{
			eatComments();
		}
		else if(state == lexer::normal)
		{

			if (current == '#')
			{
				tokens.push_back(buildSingleOp(current)); // #

				state = lexer::preprocdir;

			}
			else if(current == '"')
			{
				tokens.push_back(buildString());
			}
			else if(current == '\'')
			{
				tokens.push_back(buildChar());
			}
			else if(isdigit(current))
			{
				tokens.push_back(buildNumber(current));
			}
			else if(isalpha(current) || current == '_')
			{
				tokens.push_back(buildKeyOrID(current));
			}
			else if(checkTripleOp(current))
			{
				tokens.push_back(buildTripleOp(current));
			}
			else if(checkDoubleOp(current))
			{
				tokens.push_back(buildDoubleOp(current));
			}
			else if(checkSingleOp(current))
			{
				tokens.push_back(buildSingleOp(current));
			}
			else
			{
				std::string tmp;
				tmp += current;
				token newToken(token::invalid, tmp, lineNum, columnNum - 1);
				handleException(newToken);
			}
		}
		else if (state == lexer::preprocdir)
		{
			tokens.push_back(buildPreProcDir(current));

			if((tokens[tokens.size()-1]).type() != token::endif)
				state = lexer::preprocrest;
			else
				state = lexer::normal;

		}
		else if (state == lexer::preprocrest)
		{
			eatPreProc(current);
			//std::cout << (tokens[tokens.size()-1]).text() << std::endl;
			state = lexer::normal;
		}

		current = getChar();

	}


	postProcess();
}

void lexer::eatWhiteSpace()
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

void lexer::eatComments()
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

void lexer::postProcess()
{
	std::vector<token>::iterator itr = tokens.begin();
	//std::cout << "POST PROCESS" << std::endl;

	while(itr+1 != tokens.end())
	{

		//std::cout << itr->type() << ": " <<itr->text() << std::endl;
		if(itr->type() == token::stringliteral && (itr + 1)->type() == token::stringliteral)
		{
			std::string text1 = itr->text();
			std::string text2 = (itr+1)->text();
			itr->text("\"" + text1.substr(1, text1.size()-2) + text2.substr(1, text2.size()-2) + "\"");
			//std::cout << itr->text();
			tokens.erase(itr+1);
		}
		else
			++itr;
	}
}


void lexer::eatPreProc(char first)
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

	token newToken(token::ppjunk, tok, line, col);
	tokens.push_back(newToken);


}

char lexer::getChar()
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

bool lexer::checkTripleOp(char first)
{
	std::string tokinquest;
	tokinquest = first;
	tokinquest += input->get();
	tokinquest += input->peek();

	input->unget();
	return opers.find(tokinquest) != opers.end();
}

bool lexer::checkDoubleOp(char first)
{
	std::string tokinquest;
	tokinquest = first;
	tokinquest += input->peek();
	return opers.find(tokinquest) != opers.end();
}

bool lexer::checkSingleOp(char first)
{
	std::string tokinquest;
	tokinquest = first;
	return opers.find(tokinquest) != opers.end();
}

token lexer::buildString()
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
	token newToken(token::stringliteral, tok, lineNum, columnNum);
	return newToken;
}

token lexer::buildChar()
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
	token newToken(token::charliteral, tok, lineNum, columnNum);
	return newToken;
}

token lexer::buildKeyOrID(char first)
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

	token::TOKENTYPE tokenID;
	if(keys.find(tok) != keys.end())
		tokenID = keys[tok].type();
	else
		tokenID = token::identifier;

	token newToken(tokenID, tok, lineNum, columnNum - tok.size());
	return newToken;

}

token lexer::buildPreProcDir(char first)
{
	token pptok = buildKeyOrID(first);
	//if(pptok.type() == token::identifier) // not needed because "if" is a keyword and a pp directive
	{
		if(preprocs.find(pptok.text()) != preprocs.end())
		{
			pptok.type(preprocs[pptok.text()].type());
			//std::cout << pptok.text() << std::endl;
			return pptok;
		}

	}
	token invalid;
	return invalid;
}

token lexer::buildNumber(char first)
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
				token newToken(token::invalid, tok, lineNum, columnNum - tok.size());
				handleException(newToken);
			}
		}
		tok += current;
		current = input->peek();
	}
	//std::cout << tok << std::endl;
	token newToken(token::number, tok, lineNum, columnNum - tok.size());
	return newToken;
}

token lexer::buildTripleOp(char first)
{
	std::string tok;
	tok = first;
	tok += getChar();
	tok += getChar();
	token newToken = opers.find(tok)->second;
	newToken.line(lineNum);
	newToken.column(columnNum - 3);
	return newToken;
}

token lexer::buildDoubleOp(char first)
{
	std::string tok;
	tok = first;
	tok += getChar();
	//std::cout << tok << std::endl;
	token newToken = opers.find(tok)->second;
	newToken.line(lineNum);
	newToken.column(columnNum - 2);
	return newToken;
}

token lexer::buildSingleOp(char first)
{
	std::string tok;
	tok = first;
	//std::cout << tok << std::endl;
	token newToken = opers.find(tok)->second;
	newToken.line(lineNum);
	newToken.column(columnNum - 1);
	return newToken;
}

void lexer::handleException(token problem)
{
	//std::cout << "********** line "  << problem.line() << " column " << problem.column() << ": \'" << problem.text() << "\'" << std::endl;
}


