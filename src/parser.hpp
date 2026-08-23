#pragma once
#include <memory>
#include "token.hpp"
#include <iostream>
#include <utility>

class IdAST;
class TypeAST;
class BodyAST;
class RetAST;
class ExprAST;
class FunctionAST;

class startAST {
	std::unique_ptr<FunctionAST> function;
public:
	startAST(std::unique_ptr<FunctionAST> fucntion) 
		: function(std::move(function)) {} 
};

class TypeAST {
	
private: 
	TokenType type;
	std::string val;
public:
	TypeAST(TokenType type, std::string val) : type(TokenType::LIT_INT), val(val) {}
};

class IdAST {
	std::string name;
public:
	IdAST(std::string name) : name(std::move(name)) {} 
};

class BodyAST {
	std::unique_ptr<RetAST> ret;
	std::unique_ptr<ExprAST> expr;
public:
	BodyAST(std::unique_ptr<RetAST> ret,
		   	std::unique_ptr<ExprAST> expr) 
		: ret(std::move(ret)),
	   	expr(std::move(expr)) {}
};

class RetAST {
	TokenType type;
	std::string val;
public:
	RetAST(TokenType type, std::string val) : type(type) , val(val) {}
};

class ExprAST {
	TokenType type;
	std::string val;
public:
	ExprAST(TokenType type, std::string val) : type(type), val(val) {}
};

class FunctionAST {
	std::unique_ptr<TypeAST> type;
	std::unique_ptr<IdAST> id;
	std::unique_ptr<BodyAST> body;

public:
	FunctionAST(std::unique_ptr<TypeAST> type, 
				std::unique_ptr<IdAST> id,
				std::unique_ptr<BodyAST> body)
		: type(std::move(type)), 
		  id(std::move(id)), 
		  body(std::move(body)) {}
};


class Parser {
public:
	std::unique_ptr<TypeAST> parseType() {
		match(TokenType::TYPE_INT, "int");
		return std::make_unique<TypeAST>(TokenType::LIT_INT, "int" );	
	}

	std::unique_ptr<IdAST> parseId() {
		match(TokenType::IDENTIFIER, "main");
		return std::make_unique<IdAST>("main");
	}

	std::unique_ptr<RetAST> parseRet() {
		match(TokenType::RETURN, "return");
		return std::make_unique<RetAST>(TokenType::RETURN, "return");
	}

	std::unique_ptr<ExprAST> parseExpr() {
		match(TokenType::LIT_INT, "0");
		return std::make_unique<ExprAST>(TokenType::LIT_INT, "0");
	}

	std::unique_ptr<BodyAST> parseBody() {
		auto ret = parseRet();
		auto expr = parseExpr();
		
		return std::make_unique<BodyAST>(std::move(ret), std::move(expr)); 
	}

	std::unique_ptr<FunctionAST> parseFunction() {
		auto type = parseType();
		auto id = parseId();
		
		match(TokenType::BRACE, "{");
		
		auto body = parseBody();
		
		match(TokenType::BRACE, "}");

		return make_unique<FunctionAST>(std::move(type), std::move(id), std::move(body));
	}

	std::unique_ptr<startAST> parseStart() {
		auto function = parseFunction();
		return std::make_unique<startAST>(std::move(function));
	}

private:
	std::string contents;
	Tokenizer Tok;
	Token look_ahead;
public:
	Parser(std::string contents) 
			: contents(std::move(contents)),
		      Tok(this->contents),
		      look_ahead(Tok.getToken())	{}
private:
	void match(TokenType expected, std::string val) {
		if ( look_ahead.Type == expected) {
			if (look_ahead.TokVal == val) {
                std::cout << "look_ahead: " << look_ahead.TokVal << std::endl; 
				look_ahead = Tok.getToken();
					
			}
			else {
				std::cerr << "syntax error" << std::endl;
				exit(1);
			}
		}
		else {
			std::cerr << "syntax error" << std::endl;
			exit(1);
		}
	}
};
