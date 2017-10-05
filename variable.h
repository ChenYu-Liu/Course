#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include"prolog.h"
using namespace std;

class Variable :public Prolog{
public:
	Variable(string s);
	string value();
	string symbol();
	string type();
	void setvalue(string);
	bool match(Prolog&);

private:
	string _symbol, _value, _type;
};


Variable::Variable(string s){
	//if ((char)s[0] > 64 & (char)s[0] < 91)	{
	_symbol = s;
	_value = s;
	_type = "Var";
	//}
	//else{
	//	cout << "Create Atom boj fail. The first latter must be capitalized.";
	//}
}

bool Variable::match(Prolog& ClsObj){
	bool Check = true;
	if (ClsObj.type() == _type){
		Check = _value == ClsObj.value();
	}
	else if (ClsObj.type() == "Atom"){
		if ((_symbol != _value) & (ClsObj.value() != _value))
			Check = false;
		else
			_value = ClsObj.value();
	}
	else if (ClsObj.type() == "Number"){
		if ((_symbol!= _value) & (ClsObj.value() != _value))
			Check = false;
		else
			_value = ClsObj.value();
	}
	return Check;
}

string Variable::value(){
	return _value;

}

void Variable::setvalue(string s){
	_value = s;
}


string Variable::type(){
	return _type;
}


string Variable::symbol(){
	return _symbol;
}

#endif
