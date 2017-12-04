#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include <iostream>
#include <algorithm>
#include "list.h"
#include "struct.h"
#include <queue>

using namespace std;

template<class T>
class Iterator {
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual T* currentItem() const = 0;
	virtual bool isDone() const = 0;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
	NullIterator(T *n){}
	void first(){}
	void next(){}
	T* currentItem() const{
		return nullptr;
	};
	bool isDone() const{
		return true;
	}
};

template<class T>
class StructIterator :public Iterator<T>{
public:
	friend class Struct;
	void first() {
		_index = 0;
	}

	T* currentItem() const {
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

template<class T>
class ListIterator :public Iterator<T> {
public:
	ListIterator(List *list) : _index(0), _list(list) {}

	void first() {
		_index = 0;
	}

	T* currentItem() const {
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

template<class T>
class DFSIterator : public Iterator<T>{
public:
	DFSIterator(T* term) :_term(term), _index(0){

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
		T* term;
		std::stack<T*> stk;
		std::vector<T*> rev;
		stk.push(_term);

		while (!stk.empty()){
			term = stk.top();
			stk.pop();
			if (_term != term){
				_dfsTerms.push_back(term);
			}

			Iterator<T> * it = term->createIterator();

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

	T* currentItem() const{
		return _dfsTerms[_index];
	}
	bool isDone() const{
		return _index >= _dfsTerms.size();
	}
private:
	std::vector<T*> _dfsTerms;
	T* _term;
	int _index;
};

template<class T>
class BFSIterator : public Iterator<T> {
public:
	BFSIterator(T* term) :_term(term), _index(0){

	}
	void first(){
		T * term;
		_index = 0;
		queue<T*> que;
		que.push(_term);
		while (!que.empty()) {
			term = que.front();
			que.pop();

			if (_term != term){
				_bfsTerms.push_back(term);
			}
			Iterator<T> * it = term->createIterator();
			for (it->first(); !it->isDone(); it->next()){
				que.push(it->currentItem());
			}
		}
	}
	void next(){
		_index++;
	}
	T* currentItem() const{
		return _bfsTerms[_index];
	}
	bool isDone() const{
		return _index >= _bfsTerms.size();
	}
private:
	std::vector<T*> _bfsTerms;
	T* _term;
	int _index;
};

#endif
