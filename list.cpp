#include "list.h"
#include "iterator.h"

int List::arity() const{
	return _elements.size();
}

Term* List::args(int index){
	return _elements[index];
}

//head
Term* List::head() const{
	if (_elements.empty()){
		throw string("Accessing head in an empty list");
	}
	else{
		return _elements[0];
	}
}

//tail
List* List::tail() const{
	if (_elements.empty()){
		throw string("Accessing tail in an empty list");
	}
	else{
		vector<Term*> v;
		for (int i = 1; i < _elements.size(); i++){
			v.push_back(_elements[i]);
		}

		List* objL = new List(v);
		return objL;
	}
}

bool List::IsList(){
	return true;
}

string List::symbol() const{
	string str = "[";
	if (!_elements.empty()){
		for (int i = 0; i < _elements.size() - 1; i++){
			str += _elements[i]->symbol() + ", ";
		}
		str += _elements[_elements.size() - 1]->symbol() + "]";
	}
	else{
		str += "]";
	}
	return str;
}

string List::value() const{
	string str = "[";
	if (!_elements.empty()){
		for (int i = 0; i < _elements.size() - 1; i++){
			str += _elements[i]->value() + ", ";
		}
		str += _elements[_elements.size() - 1]->value() + "]";
	}
	else{
		str += "]";
	}
	return str;
}

bool List::match(Term & term){
	List* objL = dynamic_cast<List*>(&term);
	if (term.IsVariable()){
		bool NotRepeat = true;
		for (int i = 0; i < _elements.size(); i++){
			if (term.symbol() == _elements[i]->symbol()){
				NotRepeat = false;
				break;
			}
		}
		return NotRepeat;
	}
	else if (objL){
		bool CouldMatching = false;
		int MinSize = objL->_elements.size() > _elements.size() ? _elements.size() : objL->_elements.size();
		for (int i = 0; i < MinSize; i++){
			CouldMatching = _elements[i]->match(*objL->_elements[i]);
		}
		return CouldMatching;
	}
	else{
		return term.symbol() == symbol();
	}
}

Iterator<Term>*  List::createIterator(){
	return new ListIterator<Term>(this);
}

Iterator<Term>* List::createDFSIterator(){
	return new DFSIterator<Term>(this);
}

Iterator<Term> * List::createBFSIterator(){
	return new BFSIterator<Term>(this);
}