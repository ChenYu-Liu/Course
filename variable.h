#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
using std::string;

class Variable :public Term{
public:
	Variable(string s) :_symbol(s), _value(s){}

	string const _symbol;

	std::vector<Variable * > RelateTable;

	virtual bool IsVariable(){
		return true;
	}

	string symbol() const{
		return _symbol;
	}

	string value() const{
		if (_assignable){
			return _value;
		}
		else{
			return term->value();
		}
	}

	bool match(Term &atom){
		bool ret = _assignable;

		//存取其他 Variable 的指標位置。
		Variable* objV = dynamic_cast<Variable*>(&atom);

		if (objV){
			RelateTable.push_back(objV);
			objV->RelateTable.push_back(this);
			_value = objV->_value;
			//if (_assignable & !objV->_assignable){
			//	
			//}

			if (!_assignable){
				SetingAll(RelateTable, this);
			}

			if (!objV->_assignable){
				objV->SetingAll(objV->RelateTable, objV);
			}
		}
		else{
			//非 variable 並直接給值的情況。
			if (_assignable){
				_assignable = false;
				_value = atom.value();
				term = &atom;
				SetingAll(RelateTable, &atom);
			}
			else{
				return atom.value() == _value;
			}
		}
		return ret;
	}

private:
	Term* term;
	string _value;
	bool _assignable = true;
	//走訪所有相依表並賦予值。
	void SetingAll(std::vector<Variable *> pot, Term* term){
		for (int i = 0; i < pot.size(); i++){
			if (pot[i]->_assignable){
				pot[i]->term = term;
				pot[i]->_value = term->value();
				pot[i]->_assignable = false;
				SetingAll(pot[i]->RelateTable, term);
			}
		}
	}
};

#endif
