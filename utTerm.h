#ifndef UTTERM_H
#define UTTERM_H
#include<iostream>
#include<string>
#include<typeinfo>
#include"number.h"
#include"atom.h"
#include"variable.h"
#include<gtest\gtest.h>
using namespace std;

//test Number.value()
TEST(Number, ctor) {
	Number MY_TEST(25);
	ASSERT_EQ("25", MY_TEST.value());
}

//test Number.symbol()
TEST(Number, symbol) {
	Number MY_TEST(25);
	ASSERT_EQ(MY_TEST.symbol(), "25");
}

//?- 25=25.
//true.
TEST(Number, matchSuccess) {
	Number _25(25);
	Number _25_1(25);
	_25.match(_25_1);
	ASSERT_TRUE(_25.value() == _25_1.value());
}

//?- 25=0.
//false.
TEST(Number, matchFailureDiffValue) {
	Number _25(25);
	Number _0(0);
	ASSERT_FALSE(_25.match(_0));
}

//?- 25=tom.
//false.
TEST(Number, matchFailureDiffConstant) {
	Number _25(25);
	Atom tom("tom");
	ASSERT_FALSE(_25.match(tom));
}

//?- 25=X.
//true.
TEST(Number, matchSuccessToVar) {
	Number _25(25);
	Variable X("X");
	ASSERT_TRUE(_25.match(X));
}

////Atom-------------------------------------

//?- tom=25.
//false.
TEST(Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number _25(25);
	ASSERT_FALSE(tom.match(_25));
}

// ?- tom = X.
// X = tom.
TEST(Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable X("X");
	tom.match(X);
	ASSERT_EQ(tom.value(), "X");
}

// ?- X=tom, tom=X.
// X = tom.
TEST(Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Variable X("X");
	X.match(tom);
	tom.match(X);
	ASSERT_TRUE(X.value()=="tom");
}

// ?- X=jerry, tom=X.
// false.
TEST(Atom, matchFailureToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom jerry("jerry");
	Atom tom("tom");
	X.match(jerry);
	X.match(tom);
	ASSERT_FALSE(X.value() == "jerry");
}

////var -----------------------------------------

// ?- X = 5.
// X = 5.
TEST(Variable, matchSuccessToNumber) {
	Variable X("X");
	Number _5(5);
	X.match(_5);
	ASSERT_EQ(X.value(), "5");
}

// ?- X=25, X= 100.
// false.
TEST(Variable, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number _25(25);
	Number _100(100);
	X.match(_25);
	X.match(_100);
	ASSERT_FALSE((X.value() == "25")&(X.value()=="100"));
}

// ?- X=tom, X= 25.
// false.
TEST(Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Atom tom("tom");
	Number _25(25);
	X.match(tom);
	X.match(_25);
	ASSERT_FALSE((X.value() == "tom")&(X.value() == "25"));
}

//?- tom=X, 25=X.
//false.
TEST(Variable, matchSuccessToAtomThenFailureToNumber2) {
	Variable X("X");
	Atom tom("tom");
	Number _25(25);
	tom.match(X);
	_25.match(X);
	ASSERT_FALSE((X.value() == "tom")&(X.value() == "25"));
}

//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom){
	Variable X("X");
	Atom tom("tom");
	X.match(tom);
	X.match(tom);
	ASSERT_TRUE((X.value() == "tom")&(X.value() == "tom"));
}

#endif
