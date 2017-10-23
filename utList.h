#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor) {
	List list;
	ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
	Number _8128(8128);
	vector<Term*> v = { &_8128 };
	List list(v);
	ASSERT_EQ("[8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
	vector<Term*> v = { &terence_tao, &alan_mathison_turing };
	List list(v);
	ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X"), Y("Y");
	vector<Term*> v = { &X, &Y };
	List list(v);
	ASSERT_EQ("[X, Y]", list.symbol());

}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Number _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao"), tom("tom");
	vector<Term*> v = { &_496, &X, &terence_tao };
	List list(v);
	ASSERT_FALSE(list.match(tom));
	ASSERT_FALSE(tom.match(list));

}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number _8128(8128), _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &_496, &X, &terence_tao };
	List list(v);
	ASSERT_FALSE(list.match(_8128));
	ASSERT_FALSE(_8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Number _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v1 = { &_496, &X, &terence_tao };
	List list(v1);

	vector<Term*> v = { &X };
	Struct s(Atom("s"), v);
	ASSERT_EQ("[496, X, terence_tao]", list.symbol());
	ASSERT_EQ("s(X)", s.symbol());
	ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Number _496(496);
	Variable X("X"), Y("Y");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &_496, &X, &terence_tao };
	List list(v);
	Y.match(list);
	ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Number _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &_496, &X, &terence_tao };
	List list(v);
	ASSERT_FALSE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Number _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &_496, &X, &terence_tao };
	List list(v);
	List list1(v);
	ASSERT_TRUE(list.match(list1));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Number _496(496);
	Variable X("X"), Y("Y");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &_496, &X, &terence_tao };
	vector<Term*> v1 = { &_496, &Y, &terence_tao };
	List list(v);
	List list1(v1);
	ASSERT_TRUE(list.match(list1));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Number _496(496), _8128(8128);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &_496, &X, &terence_tao };
	vector<Term*> v1 = { &_496, &_8128, &terence_tao };
	List list(v);
	List list1(v1);
	list.match(list1);
	ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Number _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
	vector<Term*> v = { &_496, &X, &terence_tao };
	List list(v);
	X.match(alan_mathison_turing);
	ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", list.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("first"), l.head()->symbol());
	EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("second"), l.tail()->head()->value());
	EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom first("first"), second("second"), third("third");
	vector<Term*> v = { &first };
	List list(v);
	vector<Term*> v1 = { &list, &second, &third };
	List list1(v1);
	EXPECT_EQ(string("[first]"), list1.head()->symbol());
	EXPECT_EQ(string("[second, third]"), list1.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);
	EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
	EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST(List, emptyExecptionOfHead) {
	try{
		List list;
		string str = list.head()->value();
	}
	catch (std::out_of_range const & error){
		ASSERT_EQ("Accessing head in an empty list", string(error.what()));
	}
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST(List, emptyExecptionOfTail) {
	try{
		List list;
		list.tail()->value();
	}
	catch (std::out_of_range const& error){
		ASSERT_EQ("Accessing tail in an empty list", string(error.what()));
	}
}




#endif
