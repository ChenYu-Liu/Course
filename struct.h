#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include <vector>
#include <string>

using std::string;

class Struct :public Term
{
public:
	Struct(Atom const & name, std::vector<Term *> args) :_name(name), _args(args) {}

	int arity(){
		return _args.size();
	}

	Term * args(int index) {
		return _args[index];
	}

	Atom const & name() {
		return _name;
	}

	string value() const{
		string ret = _name.symbol() + "(";
		for (int i = 0; i < _args.size() - 1; i++){
			ret += _args[i]->value() + ", ";
		}
		ret += _args[_args.size() - 1]->value() + ")";
		return  ret;
	}

	string symbol() const{
		string ret = _name.symbol() + "(";
		if (_args.empty()){
			return ret + ')';
		}

		for (int i = 0; i < _args.size() - 1 ; i++){
			ret += _args[i]->symbol() + ", ";
		}
		ret += _args[_args.size() - 1]->symbol() + ")";
		return  ret;

	}

	bool match(Term &term){
		Struct * ps = dynamic_cast<Struct *>(&term);
		Term * obj = dynamic_cast<Term *>(&term);
		if (ps){
			if (!_name.match(ps->_name))
				return false;
			if (_args.size() != ps->_args.size())
				return false;
			for (int i = 0; i < _args.size(); i++){
				if (_args[i]->symbol() != ps->_args[i]->symbol())
					return false;
			}
			return true;
		}
		else if (obj){
			return  symbol() == obj->value();
		}
		return false;
	}

	std::vector<Term*> getArgs(){
		return _args;
	}

private:
	Atom _name;
	std::vector<Term *> _args;
	Struct * objS;
};

#endif
