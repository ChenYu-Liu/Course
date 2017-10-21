#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;


class Term{

public:
	virtual string symbol() const = 0;
	virtual string value() const{
		return symbol();
	};
	virtual bool match(Term & term) {
		return symbol() == term.symbol();
	}

	virtual bool IsVariable(){
		return false;
	}
	virtual bool IsList(){
		return false;
	}
};

class Atom : public Term{
public:
	Atom(string s) :_symbol(s) {}

	string symbol() const{
		return _symbol;
	}

	bool match(Term & term){
		if (term.IsVariable()){
			return term.match(*this);
		}
		else{
			return symbol() == term.symbol();
		}
	}

	string _symbol;
};


#endif
