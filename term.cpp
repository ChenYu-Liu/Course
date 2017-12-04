#include "term.h"
#include "iterator.h"

string Term::value() const{
	return symbol();
}

bool Term::IsVariable(){
	return false;
}

bool Term::match(Term& term){
	return symbol() == term.symbol();
}

bool Term::IsList(){
	return false;
}

//³Ñ¤U Iterator
Iterator<Term>* Term::createIterator(){
	return new NullIterator<Term>(this);
}

Iterator<Term>* Term::createBFSIterator(){
	return new NullIterator<Term>(this);
}

Iterator<Term>* Term::createDFSIterator(){
	return new NullIterator<Term>(this);
}