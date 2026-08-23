#pragma once
#include <string>
#include <cctype>

enum class TokenType {
	TYPE_INT,
	IDENTIFIER,
	RETURN,
	LIT_INT,
	BRACE,
	PAREN,
	SEMICOL,
	EOF_TOKEN
};

struct Token {
	TokenType Type;
	std::string TokVal;

//	Token(TokenType Type, std::string TokVal) : Type(Type) , TokVal(TokVal) {}
};

class Tokenizer {
public: 
	std::string m_src;

	Tokenizer(std::string src) 
		: m_src(std::move(src)) {}

	Token getToken() {
		return nextToken();
	}

private:
	int index = 0;
	
	Token nextToken() {
		std::string token;
		
		while (index < m_src.length() && std::isspace(m_src[index])) {
			++index;
		}
	
		char c;
		if (index < m_src.length()) 
			c = m_src[index++];
		else return {TokenType::EOF_TOKEN, ""};

		/* handles integer literal */

		if (std::isdigit(static_cast<unsigned char> (c))) {
			token.push_back(c);
			for (; index < m_src.length(); index++) {
				c = m_src[index];

				if (std::isspace(static_cast<unsigned char> (c))) {
					break;
				}
				else if (std::isalpha(static_cast<unsigned char> (c))) {
					std::cerr << "wrong input" << std::endl;
					std::exit(1);
				}
				else {
					token.push_back(c);
				}
			}
			return Token{TokenType::LIT_INT, token};
		}

		/* handles identifiers and keywords */

		if (std::isalpha(static_cast<unsigned char> (c))) {
			token.push_back(c);
			for(; index < m_src.length(); index++) {
				c = m_src[index];
				if (std::isspace(static_cast<unsigned char> (c))) {
					break; 
				}
				
				if (std::isalnum(static_cast<unsigned char> (c))) {
					token.push_back(c);
				}
				else 
					break;
			}
			
			if (token == "int")
				return {TokenType::TYPE_INT, token};
			else if (token == "return") 
				return {TokenType::RETURN, token};
			else
				return {TokenType::IDENTIFIER, token};
			
		}
					
		/* handles braces and paren */
		switch (c) {
		case '{':
			return {TokenType::BRACE, std::string(1,c)};
			break;
		case '}':
			return {TokenType::BRACE, std::string(1,c)};
			break;
		case '(':
			return {TokenType::PAREN, std::string(1,c)};
			break;
		case ')':
			return {TokenType::PAREN, std::string(1,c)};
		case ';':
			return {TokenType::SEMICOL, std::string(1,c)};
		default:
			std::cerr << "unknow char" << std::endl;
			std::cout << 1 << 2 << std::endl;
			std::exit(1);
		}	
		
	}

};
