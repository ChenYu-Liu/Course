#ifndef ATOM_H
#define ATOM_H

#include<iostream>
#include<sstream>
#include <string>
#include"prolog.h"
using namespace std;

class  Atom :public Prolog{
public:
	Atom(string s);
	string value();
	string symbol();
	string type();
	void setvalue(string);
	bool match(Prolog&);
private:
	string _symbol, _value, _type;
};

Atom::Atom(string s){
	//if (!((char)s[0] > 64 & (char)s[0] < 91))	{
	_symbol = s;
	_value = s;
	_type = "Atom";
	//}
	//else{
	//	cout << "Create Atom boj fail. First letter lower case.";
	//}
}

string Atom::value(){
	return _value;
}

void Atom::setvalue(string s){
	_value = s;
}

string Atom::symbol(){
	return _symbol;
}

string Atom::type(){
	return _type;
}

bool Atom::match(Prolog& ClsObj){
	bool Check = true;
	if (ClsObj.type() == _type){
		Check = _value == ClsObj.value();
	}
	else if (ClsObj.type() == "Number"){
		Check = false;
	}
	else if (ClsObj.type() == "Var"){
		if ((ClsObj.value() != ClsObj.symbol())&(ClsObj.value() != _symbol))
			Check = false;
		else
			ClsObj.setvalue(_symbol);
	}
	return Check;
}

#endif
