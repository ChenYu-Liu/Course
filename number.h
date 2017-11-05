#ifndef NUMBER_H
#define NUMBER_H
#include "term.h"
#include <string>
using std::string;

class Number :public Term
{
public:
	Number(double v) :_value(v){
		std::ostringstream oss;
		oss << _value;
		_sybmol = oss.str();
	}
	
	bool match(Term & term){
		if (term.IsVariable()){
			return term.match(*this);
		}
		else{
			return symbol() == term.symbol();
		}
	}

	string symbol()const{
		return _sybmol;
	}
private:
	string _sybmol;
	double _value;
};


#endif