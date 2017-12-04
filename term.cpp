#include "term.h"
#include "iterator.h"
//#include <string>

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
Iterator* Term::createIterator(){
	return new NullIterator(this);
}

Iterator* Term::createBFSIterator(){
	return new NullIterator(this);
}

Iterator* Term::createDFSIterator(){
	return new NullIterator(this);
}