#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <vector>
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

private:
	vector<Term *> _elements;
	bool b_head = false, b_tail = false;
};


//head
Term* List::head() const{
	try{
		if (_elements.empty()){
			throw 1;
		}
		return _elements[0];		
	}
	catch (int e){
		List* list = new List();
		list->b_head = true;
		return list;
	}
}

//tail
List* List::tail() const{
	try{
		if (_elements.empty()){
			throw 1;
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
	catch (int e){
		List* list = new List();
		list->b_tail = true;
		return list;
	}
}


bool List::IsList(){
	return true;
}

string List::symbol() const{
	if (b_head){
		return "Accessing head in an empty list";
	}
	else if (b_tail){
		return "Accessing tail in an empty list";
	}
	else{
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
}

string List::value() const{
	if (b_head){
		return "Accessing head in an empty list";
	}
	else if (b_tail){
		return "Accessing tail in an empty list";
	}
	else{
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

#endif
