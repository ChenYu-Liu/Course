#ifndef EXP_H
#define EXP_H
#include "Shapes.h"
#include "Media.h"
#include "Sort.h"
#include <iostream>
#include<list>
#include<math.h>
using namespace std;

TEST(Sort, sortByIncreasingPerimeter) {
	list<Shape*> ShapeList;
	vertex one = { 2.0f, 2.0f }; vertex two = { 3.1f, 2.3f }; vertex three = { 1.2f, 3.2f };
	//指標的部分，事後要再弄清楚↓
	auto Compare = [&](const Shape* a, const Shape* b)->bool{if ((*a).perimeter() < (*b).perimeter())return true; else return false; };
	Rectangle rectangle(2., 3., 4., 5., "rectangle");
	Circle circle(2, 3, 4, "circle");
	Triangle triangle(one, two, three, "triangle");
	ShapeList.push_back(&rectangle);
	ShapeList.push_back(&circle);
	ShapeList.push_back(&triangle);
	ShapeList.sort(Compare);
	list<Shape*>::iterator it = ShapeList.begin();
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
}

TEST(Sort, sortByDecreasingPerimeter) {
	list<Shape*> ShapeList;
	vertex one = { 2.0f, 2.0f }; vertex two = { 3.1f, 2.3f }; vertex three = { 1.2f, 3.2f };
	//指標的部分，事後要再弄清楚↓
	auto Compare = [&](const Shape* a, const Shape* b)->bool{if ((*a).perimeter() > (*b).perimeter())return true; else return false; };
	Rectangle rectangle(2., 3., 4., 5., "rectangle");
	Circle circle(2, 3, 4, "circle");
	Triangle triangle(one, two, three, "triangle");
	ShapeList.push_back(&rectangle);
	ShapeList.push_back(&circle);
	ShapeList.push_back(&triangle);
	ShapeList.sort(Compare);
	list<Shape*>::iterator it = ShapeList.begin();
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
}

TEST(Sort, sortByIncreasingArea) {
	list<Shape*> ShapeList;
	vertex one = { 2.0f, 2.0f }; vertex two = { 3.1f, 2.3f }; vertex three = { 1.2f, 3.2f };
	//指標的部分，事後要再弄清楚↓
	auto Compare = [&](const Shape* a, const Shape* b)->bool{if ((*a).area() < (*b).area())return true; else return false; };
	Rectangle rectangle(2., 3., 4., 5., "rectangle");
	Circle circle(2, 3, 4, "circle");
	Triangle triangle(one, two, three, "triangle");
	ShapeList.push_back(&rectangle);
	ShapeList.push_back(&circle);
	ShapeList.push_back(&triangle);
	ShapeList.sort(Compare);
	list<Shape*>::iterator it = ShapeList.begin();
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
}

TEST(Sort, sortByDecreasingArea) {
	list<Shape*> ShapeList;
	vertex one = { 2.0f, 2.0f }; vertex two = { 3.1f, 2.3f }; vertex three = { 1.2f, 3.2f };
	//指標的部分，事後要再弄清楚↓
	auto Compare = [&](const Shape* a, const Shape* b)->bool{if ((*a).area() > (*b).area())return true; else return false; };
	Rectangle rectangle(2., 3., 4., 5., "rectangle");
	Circle circle(2, 3, 4, "circle");
	Triangle triangle(one, two, three, "triangle");
	ShapeList.push_back(&rectangle);
	ShapeList.push_back(&circle);
	ShapeList.push_back(&triangle);
	ShapeList.sort(Compare);
	list<Shape*>::iterator it = ShapeList.begin();
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());


}

TEST(Sort, sortByIncreasingCompactness) {
	list<Shape*> ShapeList;
	vertex one = { 2.0f, 2.0f }; vertex two = { 3.1f, 2.3f }; vertex three = { 1.2f, 3.2f };
	//4 * PI * aera / pow(perimeter,2) Or "Gibbs" 4 * aera /(pi * pow(length,2))
	auto Compare = [&](const Shape* a, const Shape* b)->bool{
		double first = 4 * M_PI*(*a).area() / pow((*a).perimeter(), 2);
		double second = 4 * M_PI*(*b).area() / pow((*b).perimeter(), 2);
		if (first < second)
			return true; 
		else
			return false;
	};
	Rectangle rectangle(2., 3., 4., 5., "rectangle");
	Circle circle(2, 3, 4, "circle");
	Triangle triangle(one, two, three, "triangle");
	ShapeList.push_back(&rectangle);
	ShapeList.push_back(&circle);
	ShapeList.push_back(&triangle);
	ShapeList.sort(Compare);
	list<Shape*>::iterator it = ShapeList.begin();
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
}

#endif
