#ifndef NUMBER_H
#define NUMBER_H
#include "atom.h"
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

	string symbol()const{
		return _sybmol;
	}
private:
	string _sybmol;
	double _value;
};


#endif