#ifndef UTPARSER_H
#define UTPARSER_H

#include "parser.h"
#include "scanner.h"
#include "term.h"
#include "list.h"
#include "variable.h"
#include "number.h"

class ParserTest : public ::testing::Test {
protected:
	void SetUp() {
		symtable.clear();
	}
};

TEST_F(ParserTest, createTerm_Var){
	Scanner scanner("X");
	Parser parser(scanner);
	ASSERT_EQ("X", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Num){
	Scanner scanner("123");
	Parser parser(scanner);
	ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Atom)
{
	Scanner scanner("tom");
	Parser parser(scanner);
	ASSERT_EQ("tom", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createArgs)
{
	Scanner scanner("1, X, tom");
	Parser parser(scanner);
	vector<Term*> terms = parser.getArgs();
	ASSERT_EQ("1", terms[0]->symbol());
	ASSERT_EQ("X", terms[1]->symbol());
	ASSERT_EQ("tom", terms[2]->symbol());
}

TEST_F(ParserTest, createTerms)
{
	//---------------012345678901
	Scanner scanner("s(1, X, tom)");
	Parser parser(scanner);
	ASSERT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  tom" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "tom".
TEST_F(ParserTest, listOfTermsTwo) {
	Scanner _scanner(" 12345,  tom");
	Parser _parser(_scanner);
	vector<Term*> terms = _parser.getArgs();
	ASSERT_EQ("12345", terms[0]->symbol());
	ASSERT_EQ("tom", terms[1]->symbol());
}


// Given there is string: "point(1, X, z(1,2,3))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z(1,2,3))".
TEST_F(ParserTest, parseStructOfStruct) {
	//---------------01234567890123456789012
	Scanner scanner("point(1, X, z(1, 2 ,3))");
	Parser parser(scanner);
	ASSERT_EQ("point(1, X, z(1, 2, 3))", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  67" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "67".
TEST_F(ParserTest, listOfTermsTwoNumbers) {
	Scanner _scanner(" 12345,  67");
	Parser _parser(_scanner);
	vector<Term*> terms = _parser.getArgs();
	ASSERT_EQ("12345", terms[0]->symbol());
	ASSERT_EQ("67", terms[1]->symbol());
}


// Given there is string: "point(1, X, z)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z)".
TEST_F(ParserTest, parseStructThreeArgs) {
	Scanner _scanner("point(1, X, z)");
	Parser _parser(_scanner);
	ASSERT_EQ("point(1, X, z)", _parser.createTerm()->symbol());
}

// Given there is string: "   [   ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[]".
TEST_F(ParserTest, parseListEmpty) {
	//----------------01234567
	Scanner _scanner("   [   ]");
	Parser _parser(_scanner);
	ASSERT_EQ("[]", _parser.createTerm()->symbol());
}


// Given there is string: "_date" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Variable.
// And #symbol() of Variable should return "_date".
TEST_F(ParserTest, parseVar) {
	Scanner _scanner("_date");
	Parser _parser(_scanner);
	ASSERT_EQ("_date", _parser.createTerm()->symbol());
}

//------------------ check its NULL of return value.
// Given there is not string in scanner.
// When parser parses all terms via scanner.
// Then it should return nothing.
TEST_F(ParserTest, listOfTermsEmpty) {
	Scanner _scanner;
	Parser _parser(_scanner);
	ASSERT_EQ(NULL, _parser.createTerm());
}


// Given there is string: "s(s(s(s(1))))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "s(s(s(s(1))))".
TEST_F(ParserTest, parseStructOfStructAllTheWay) {
	Scanner _scanner("s(s(s(s(1))))");
	Parser _parser(_scanner);
	ASSERT_EQ("s(s(s(s(1))))", _parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [] ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], []]".
TEST_F(ParserTest, parseListOfLists) {
	//----------------012345678901234
	Scanner _scanner("   [  [1], [] ]");
	Parser _parser(_scanner);
	ASSERT_EQ("[[1], []]", _parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [], s(s(1)) ]   " in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], [], s(s(1))]".
TEST_F(ParserTest, parseListOfListsAndStruct) {
	//----------------012345678901234567890123456
	Scanner _scanner("   [  [1], [], s(s(1)) ]   ");
	Parser _parser(_scanner);
	ASSERT_EQ("[[1], [], s(s(1))]", _parser.createTerm()->symbol());
}

// Given there is string: "   [1, 2]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[1, 2]".
TEST_F(ParserTest, parseList) {
	Scanner _scanner("   [1, 2]");
	Parser _parser(_scanner);
	ASSERT_EQ("[1, 2]", _parser.createTerm()->symbol());
}

// Given there is string: "[1,2)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a string: "unexpected token" as exception.
TEST_F(ParserTest, illegal1) {
	try{
		//----------------01234
		Scanner _scanner("[1,2)");
		Parser _parser(_scanner);
		_parser.createTerm()->symbol();
	}
	catch (const string error){
		ASSERT_EQ("unexpected token", error);
	}
}


// Given there is string: ".(1,[])" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(1, [])".
// And the first term should be number: "1", the second term should be another List: "[]".
TEST_F(ParserTest, ListAsStruct) {
	Scanner _scanner(".(1,[])");
	Parser _parser(_scanner);
	Struct* _struct = dynamic_cast<Struct*>(_parser.createTerm());
	ASSERT_EQ(2, _struct->arity());
	ASSERT_EQ(".(1, [])", _struct->symbol());
}


// Given there is string: ".(2,.(1,[]))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(2, .(1, []))"
// And the first term should be number: "2", the second term should be another Strcut: ".(1, [])".
TEST_F(ParserTest, ListAsStruct2) {
	Scanner _scanner(".(2,.(1,[]))");
	Parser _parser(_scanner);
	Struct* _struct = dynamic_cast<Struct*>(_parser.createTerm());
	ASSERT_EQ(2, _struct->arity());
	ASSERT_EQ(".(2, .(1, []))", _struct->symbol());
}


// Given there is string: "s(s(s(s(1)))), b(1,2,3)" in scanner.
// When parser parses all terms via scanner.
// Then it should return two Struct.
// And #symbol() of the first Strcut should return "s(s(s(s(1))))".
// And #symbol() of the second Strcut should return "b(1, 2, 3)".
TEST_F(ParserTest, parseStructOfStructAllTheWay2) {
	Scanner _scanner("s(s(s(s(1)))), b(1,2,3)");
	Parser _parser(_scanner);
	vector<Term*> terms = _parser.getArgs();
	ASSERT_EQ("s(s(s(s(1))))", terms[0]->symbol());
	ASSERT_EQ("b(1, 2, 3)", terms[1]->symbol());
}


// Given there is string: "point()" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point()".
TEST_F(ParserTest, parseStructNoArg) {
	Scanner _scanner("point()");
	Parser _parser(_scanner);
	ASSERT_EQ("point()", _parser.createTerm()->symbol());
}


// Given there is string: " 12345,  tom,   Date" in scanner.
// When parser parses all terms via scanner.
// Then it should return three terms: "12345", "tom" and "Date".
TEST_F(ParserTest, listOfTermsThree) {
	Scanner _scanner(" 12345,  tom,   Date");
	Parser _parser(_scanner);
	vector<Term*> terms = _parser.getArgs();
	ASSERT_EQ("12345", terms[0]->symbol());
	ASSERT_EQ("tom", terms[1]->symbol());
	ASSERT_EQ("Date", terms[2]->symbol());
}


// Given there is string: "point(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11, 12)".
TEST_F(ParserTest, parseStructTwoArgs) {
	Scanner _scanner("point(11,12)");
	Parser _parser(_scanner);
	ASSERT_EQ("point(11, 12)", _parser.createTerm()->symbol());
}


// Given there is string: "...(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "...(11, 12)".
TEST_F(ParserTest, parseStructDOTSTwoArgs) {
	Scanner _scanner("...(11,12)");
	Parser _parser(_scanner);
	ASSERT_EQ("...(11, 12)", _parser.createTerm()->symbol());
}


// Given there is string: "point(11)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11)".
TEST_F(ParserTest, parseStructOneArg) {
	Scanner _scanner("point(11)");
	Parser _parser(_scanner);
	ASSERT_EQ("point(11)", _parser.createTerm()->symbol());
}

#endif
