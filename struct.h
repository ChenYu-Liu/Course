#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct :public Term
{
public:
	Struct(Atom const & name, std::vector<Term *> args) :_name(name), _args(args) {}
	int arity();
	Term * args(int index);
	Atom const & name();
	string value() const;
	string symbol() const;
	bool match(Term &term);
	std::vector<Term*> getArgs();
	std::vector<Term *> _args;
	Iterator<Term>* createIterator();
	Iterator<Term>* createDFSIterator();
	Iterator<Term>* createBFSIterator();
private:
	Atom _name;	
	Struct * objS;
};

#endif
