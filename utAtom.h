#ifndef UTATOM_H
#define UTATOM_H
#include "atom.h"

TEST(Atom, first) {
	ASSERT_TRUE(true);
}

TEST(Atom, tom) {
	Atom tom("tom");
	ASSERT_EQ("tom", tom.symbol());
}

TEST(Atom, match_tom_and_jerry) {
	Atom tom("tom");
	Atom jerry("jerry");
	EXPECT_FALSE(tom.match(jerry));
	EXPECT_TRUE(tom.match(tom));
}

TEST(Atom, value)
{
	Atom tom("tom");
	EXPECT_EQ("tom", tom.value());
}

TEST(Atom, Virtual)
{
	Term* t = new Atom("tom");
	EXPECT_EQ("tom", t->value());
}

TEST(Atom, Variable1){
	Atom tom("tom");
	Variable X("X");
	ASSERT_TRUE(tom.match(X));
}

TEST(Number, Variable2){
	Variable X("X");
	Number _1(1);
	ASSERT_TRUE(_1.match(X));
}

TEST(Struct, Variable3){
	Variable X("X"), Y("Y");
	std::vector<Term*> v = { &Y };
	Struct s(Atom("s"), v);
	s.match(Y);
}

#endif
