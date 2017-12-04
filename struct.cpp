#include "struct.h"
#include "iterator.h"

int Struct::arity(){
	return _args.size();
}

Term* Struct::args(int index){
	return _args[index];//_args[index]=new address
}

Atom const & Struct::name(){
	return _name;
}

string Struct::value() const{
	string ret = _name.symbol() + "(";
	for (int i = 0; i < _args.size() - 1; i++){
		ret += _args[i]->value() + ", ";
	}
	ret += _args[_args.size() - 1]->value() + ")";
	return  ret;
}

string Struct::symbol() const{
	string ret = _name.symbol() + "(";
	if (_args.empty()){
		return ret + ')';
	}

	for (int i = 0; i < _args.size() - 1; i++){
		ret += _args[i]->symbol() + ", ";
	}
	ret += _args[_args.size() - 1]->symbol() + ")";
	return  ret;
}

bool Struct::match(Term& term){
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

std::vector<Term*> Struct::getArgs(){
	return _args;
}

Iterator * Struct::createIterator()
{
	return new StructIterator(this);
}
Iterator * Struct::createDFSIterator(){
	return new DFSIterator(this);
}

Iterator * Struct::createBFSIterator(){
	return new BFSIterator(this);
}