#ifndef NUMBER_H
#define NUMBER_H

#include<iostream>
#include<string>
#include"prolog.h"
using namespace std; 


class  Number :public Prolog{
public:
	Number(int v);
	virtual string value();
	virtual string symbol();
	virtual string type();
	virtual bool match(Prolog&);
private:
	string  _type;
	string _symbol;
	int _value;

};

Number::Number(int v){
	_symbol = to_string(v);
	_value = v;
	_type = "Number";
}

string Number::value(){
	return to_string(_value);
}

string Number::symbol(){
	return _symbol;
}

string Number::type(){
	return _type;
}

bool Number::match(Prolog &ClsObj){
	bool Check = true;
	if (ClsObj.type() == _type){
		Check = _value == stoi(ClsObj.value());
	}
	else if (ClsObj.type() == "Atom"){
		Check = false;
	}
	else if (ClsObj.type() == "Var"){
		Check = true;
	}
	return Check;
}

#endif