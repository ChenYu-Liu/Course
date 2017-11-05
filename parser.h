#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <stack>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
using std::string;

class Parser{
public:
	Parser(Scanner scanner) : _scanner(scanner){}

	Term* createTerm(){
		int token = _scanner.nextToken();

		if (token == VAR){
			return new Variable(symtable[_scanner.tokenValue()].first);
		}
		else if (token == NUMBER){
			return new Number(_scanner.tokenValue());
		}
		else if (token == ATOM || token == ATOMSC){
			Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
			if (_scanner.currentChar() == '('){
				checkOCBracket.push(_scanner.nextToken());
				if (_scanner.currentChar() == ')') {
					_scanner.nextToken();
					checkOCBracket.pop();
					vector<Term*> list;
					return new Struct(*atom, list);
				}
				else{
					vector<Term*> terms = getArgs();
					//每個 Struct 的最外圈左右括弧比較
					if (!checkOCBracket.empty()){
						if (abs(_currentToken - checkOCBracket.top()) <= 0 || abs(_currentToken - checkOCBracket.top()) > 2){
							throw(string("unexpected token"));
						}
						checkOCBracket.pop();
					}
					return new Struct(*atom, terms);
				}
			}
			else
				return atom;
		}
		else if (token == '['){
			if (_scanner.currentChar() == ']'){
				_scanner.nextToken();
				return new List();
			}
			else{
				checkOCBracket.push(token);
				vector<Term*> terms = getArgs();
				//每個 List 的最外圈左右括弧比較
				if (!checkOCBracket.empty()){
					if (abs(_currentToken - checkOCBracket.top()) <= 0 || abs(_currentToken - checkOCBracket.top()) > 2){
						throw(string("unexpected token"));
					}
					checkOCBracket.pop();
				}
				return new List(terms);
			}
		}
		//依據 ']',')' 跟 stack依序做檢查
		else if (token == ')' || token == ']'){
			if (abs(token - checkOCBracket.top()) <= 0 || abs(token - checkOCBracket.top()) > 2){
				throw(string("unexpected token"));
			}
			checkOCBracket.pop();
		}
		return NULL;
	}

	vector<Term*> getArgs()
	{
		Term* term = createTerm();
		vector<Term*> args;
		if (term)
			args.push_back(term);
		while ((_currentToken = _scanner.nextToken()) == ',') {
			args.push_back(createTerm());
		}
		return args;
	}

private:
	std::stack<int> checkOCBracket;
	Scanner _scanner;
	int _currentToken;
};

#endif
