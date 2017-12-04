#ifndef LIST_H
#define LIST_H

#include <vector>
#include "term.h"
using std::vector;

class List : public Term {
public:
	string symbol() const;
	string value() const;
	bool IsList();
	bool match(Term & term);

public:
	List() :_elements(){}
	List(vector<Term *> const & elements) :_elements(elements){}
	Term * head() const;
	List * tail() const;
	Term * args(int index);
	int arity() const;
	Iterator<Term>* createIterator();
	Iterator<Term>* createDFSIterator();
	Iterator<Term>* createBFSIterator();
private:
	vector<Term *> _elements;
	bool b_head = false, b_tail = false;
};

#endif
