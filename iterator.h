#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include <iostream>
#include <algorithm>
#include "list.h"
#include "struct.h"
#include <queue>

using namespace std;

class Iterator {
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual Term* currentItem() const = 0;
	virtual bool isDone() const = 0;
};

class NullIterator :public Iterator{
public:
	NullIterator(Term *n){}
	void first(){}
	void next(){}
	Term * currentItem() const{
		return nullptr;
	}
	bool isDone() const{
		return true;
	}

};

class StructIterator :public Iterator {
public:
	friend class Struct;
	void first() {
		_index = 0;
	}

	Term* currentItem() const {
		return _s->args(_index);
	}

	bool isDone() const {
		return _index >= _s->arity();
	}

	void next() {
		_index++;
	}
private:
	StructIterator(Struct *s) : _index(0), _s(s) {}
	int _index;
	Struct* _s;
};

class ListIterator :public Iterator {
public:
	ListIterator(List *list) : _index(0), _list(list) {}

	void first() {
		_index = 0;
	}

	Term* currentItem() const {
		return _list->args(_index);
	}

	bool isDone() const {
		return _index >= _list->arity();
	}

	void next() {
		_index++;
	}
private:
	int _index;
	List* _list;
};

class DFSIterator : public Iterator{
public:
	DFSIterator(Term* term) :_term(term), _index(0){

	}
	//s(1, t(1,2), X)
	/*


	s(1, t(1,2), X)
	  /    |     \
	/     |      \
	1    t(1,2)    X
	      / \
	     /   \
	    1     2
	DFS:
	Stack: [X t(1,2) 1]
	Stack: [X t(1,2)  ]    Output: 1
	Stack: [X 2 1]         Output: 1, t(1,2)
	Stack: [X 2]           Output: 1, t(1,2), 1
	Stack: [X]             Output: 1, t(1,2), 1, 2
	Stack: []              Output: 1, t(1,2), 1, 2, X

	BFS:
	Queue: [1 t(1,2) X]
	Queue: [  t(1,2) X]    Output: 1
	Queue: [X 1 2]         Output: 1, t(1,2)
	Queue: [1 2]           Output: 1, t(1,2), X
	Queue: [2]             Output: 1, t(1,2), X, 1
	Queue: []              Output: 1, t(1,2), X, 1, 2
	*/
	void first(){
		_index = 0;
		Term* term;
		std::stack<Term*> stk;
		std::vector<Term*> rev;
		stk.push(_term);

		while (!stk.empty()){
			term = stk.top();
			stk.pop();
			if (_term != term){
				_dfsTerms.push_back(term);
			}

			Iterator * it = term->createIterator();

			rev.clear();
			for (it->first(); !it->isDone(); it->next()){
				rev.push_back(it->currentItem());
			}
			std::reverse(rev.begin(), rev.end());
			for (int i = 0; i < rev.size(); i++){
				stk.push(rev[i]);
			}

		}
	}
	void next(){
		_index++;
	}
	Term* currentItem() const{
		return _dfsTerms[_index];
	}
	bool isDone() const{
		return _index >= _dfsTerms.size();
	}
private:
	std::vector<Term*> _dfsTerms;
	Term* _term;
	int _index;
};

class BFSIterator : public Iterator {
public:
	BFSIterator(Term* term) :_term(term), _index(0){

	}
	void first(){
		Term * term;
		_index = 0;
		queue<Term*> que;
		que.push(_term);
		while (!que.empty()) {
			term = que.front();
			que.pop();

			if (_term != term){
				_bfsTerms.push_back(term);
			}
			Iterator * it = term->createIterator();
			for (it->first(); !it->isDone(); it->next()){
				que.push(it->currentItem());
			}
		}
	}
	void next(){
		_index++;
	}
	Term* currentItem() const{
		return _bfsTerms[_index];
	}
	bool isDone() const{
		return _index >= _bfsTerms.size();
	}
private:
	std::vector<Term*> _bfsTerms;
	Term* _term;
	int _index;

};

#endif
