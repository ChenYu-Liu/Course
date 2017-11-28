#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include <stack>
//#include "utParser.h"

class Parser{
public:
	Parser(Scanner scanner) : _scanner(scanner), _terms(){}
	//�B��l�B�B�⤸
	std::stack<Node*>  stackOPtors, stackOPtor;
	std::vector<Term*> getStructVar;

	//�إ� X = 1 ���p��C
	void smallTree(){
		//�̤W���O '=' ���ɭԡC
		if (stackOPtors.top()->payload == EQUALITY){
			stackOPtors.top()->right = stackOPtor.top();
			stackOPtor.pop();
			stackOPtors.top()->left = stackOPtor.top();
			stackOPtor.pop();
			stackOPtor.push(stackOPtors.top());
			stackOPtors.pop();
		}
	}

	//create struct �̭��� variable
	bool getVarOfStruct(Term* obj){
		Struct* _struct = dynamic_cast<Struct*>(obj);
		if (_struct){
			for (int i = 0; i < _struct->arity(); i++){
				if (!getVarOfStruct(_struct->args(i)) & _struct->args(i)->IsVariable()){
					if (getStructVar.size() == 0) { getStructVar.push_back(_struct->args(i)); }
					else{
						bool set = false;
						for (int k = 0; k < getStructVar.size(); k++){
							if (_struct->args(i)->symbol() == getStructVar[k]->symbol()){
								_struct->_args[i] = getStructVar[k];
								set = true;
							}
						}
						if (!set) { getStructVar.push_back(_struct->args(i)); }
					}
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	Node* expressionTree(){
		return stackOPtor.top();
	}

	void matchings(){
		int token = _scanner.currentChar(), tag = 0;
		while (token != '.')
		{
			Node* node = new Node(TERM);
			if (token == ','){
				node->payload = COMMA;
				//�إߤp��
				smallTree();
				stackOPtors.push(node);
				//�p�G tag �O1��ܫe�᪺term�����Y�A�ҥH�n�إ����Y�C
				tag = 1;
				_scanner.nextToken();
			}
			else if (token == ';'){
				node->payload = SEMICOLON;
				//�إߤp��
				smallTree();
				//�p�G tag �O0��ܫe�᪺term�S���Y�A�ӧOcreate�C
				tag = 2;
				stackOPtors.push(node);
				_scanner.nextToken();
			}
			else if (token == '='){
				node->payload = EQUALITY;
				stackOPtors.push(node);
				_scanner.nextToken();
			}
			else{

				Term* obj = createTerm();
				if (tag == 2){
					getStructVar.clear();
					tag = 0;
				}
				//�s�� ; ��Ҧ��� term �A�]�t struct �� term�C
				getVarOfStruct(obj);
				//Var and Var �إ����Y�C
				if (tag == 1){
					for (int i = 0; i < getStructVar.size(); i++){
						if (getStructVar[i]->symbol() == obj->symbol()){
							obj = getStructVar[i];
						}
					}
				}

				getStructVar.push_back(obj);
				_terms.push_back(obj);
				//save term to stack 
				node->payload = TERM;
				node->term = obj;
				stackOPtor.push(node);
			}
			token = _scanner.currentChar();
		}
		smallTree();

		//�}�l�վ� '; or ,' ������
		while (!stackOPtors.empty())
		{
			if (stackOPtors.top()->right == NULL){
				stackOPtors.top()->right = stackOPtor.top();
				stackOPtor.pop();
			}
			if (stackOPtors.top()->left == NULL & !stackOPtor.empty()){
				stackOPtors.top()->left = stackOPtor.top();
				stackOPtor.pop();
			}

			stackOPtor.push(stackOPtors.top());
			stackOPtors.pop();
		}
	}

	Term* createTerm(){
		int token = _scanner.nextToken();
		_currentToken = token;
		if (token == VAR){
			return new Variable(symtable[_scanner.tokenValue()].first);
		}
		else if (token == NUMBER){
			return new Number(_scanner.tokenValue());
		}
		else if (token == ATOM || token == ATOMSC){
			Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
			if (_scanner.currentChar() == '(') {
				return structure();
			}
			else
				return atom;
		}
		else if (token == '['){
			return list();
		}

		return nullptr;
	}

	Term * structure() {
		Atom structName = Atom(symtable[_scanner.tokenValue()].first);
		int startIndexOfStructArgs = _terms.size();
		_scanner.nextToken();
		createTerms();
		if (_currentToken == ')')
		{
			vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
			_terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
			return new Struct(structName, args);
		}
		else {
			throw string("unexpected token");
		}
	}

	Term * list() {
		int startIndexOfListArgs = _terms.size();
		createTerms();
		if (_currentToken == ']')
		{
			vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
			_terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
			return new List(args);
		}
		else {
			throw string("unexpected token");
		}
	}

	vector<Term *> & getTerms() {
		return _terms;
	}

private:
	FRIEND_TEST(ParserTest, createArgs);
	FRIEND_TEST(ParserTest, ListOfTermsEmpty);
	FRIEND_TEST(ParserTest, listofTermsTwoNumber);
	FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

	void createTerms() {
		Term* term = createTerm();
		if (term != nullptr)
		{
			_terms.push_back(term);
			while ((_currentToken = _scanner.nextToken()) == ',') {
				_terms.push_back(createTerm());
			}
		}
	}

	vector<Term *> _terms;
	Scanner _scanner;
	int _currentToken;
};
#endif
