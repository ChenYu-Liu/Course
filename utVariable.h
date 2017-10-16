#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "number.h"

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

//Variable is accept all the type
TEST(Variable, matching1){
	Number _25(25);
	Atom jerry("jerry");
	Atom tom("tom");
	std::vector<Term *> v = { &_25, &jerry };
	std::vector<Term *> v1 = { &_25, &tom };
	Struct argument(tom,v);
	Struct argument1(tom, v1);
	Variable X("X");
	Variable Y("Y");
	Variable S("S");
	Variable S1("S1");
	Variable S2("S2");
	X.match(_25);
	Y.match(tom);
	S.match(argument);
	S1.match(argument1);
	S2.match(argument1);
	ASSERT_EQ("tom", Y.value());
	ASSERT_EQ("25", X.value());
	ASSERT_EQ("tom(25, jerry)", S.value());
	ASSERT_FALSE(X.match(tom));
	ASSERT_FALSE(Y.match(_25));
	ASSERT_FALSE(S.match(argument1));
	ASSERT_TRUE(S1.match(S2));
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

TEST(Number, symbol){
	Number _25(25.1);
	Number _251(25.1);
	ASSERT_EQ("25.1", _25.symbol());
	ASSERT_TRUE(_25.match(_251));
}

TEST(Number, matching){
	Atom tom("tom");
	Number _25(25);
	ASSERT_FALSE(_25.match(tom));
}

TEST(Number, matching1){
	Variable X("X");
	Number _25(25);
	Number _20(20);
	X.match(_25);
	ASSERT_FALSE(X.match(_20));
	ASSERT_TRUE(X.match(_25));
}

#endif
