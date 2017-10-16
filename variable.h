#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
using std::string;

class Variable :public Term{
public:
	Variable(string s) :_symbol(s){}
	string const _symbol;
	string value(){
		return _value;

	}
	string symbol() const{
		return _symbol;
	}

	string value() const{
		return _value;
	}

	bool match(Term &atom){
		bool ret = _assignable;
		if (_assignable){
			_value = atom.symbol();
			_assignable = false;
		}
		else{
			return atom.value() == _value;
		}

		return ret;
	}
private:
	string _value;
	bool _assignable = true;
};

#endif
