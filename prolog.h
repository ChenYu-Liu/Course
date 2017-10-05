#ifndef PROLOGCOMPARE_H
#define PROLOGCOMPARE_H
#include<string>
using namespace std;

class Prolog
{
public:
	virtual string symbol() = 0;
	virtual string value() = 0;
	virtual string type() = 0;
	virtual bool match(Prolog&) = 0;
	virtual void setvalue(string s) = 0;
};



#endif