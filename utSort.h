#ifndef EXP_H
#define EXP_H
#include "include\Shapes.h"
#include <iostream>
#include<list>
#include<math.h>
using namespace std;

//vertex one = { 2.0f, 2.0f }; vertex two = { 3.1f, 2.3f }; vertex three = { 1.2f, 3.2f };
Rectangle rectangle(2., 3., 4., 5., "rectangle");
Circle circle(2, 3, 4, "circle");
Triangle triangle(vertex{ 2.0, 2.0 }, vertex{ 3.1f, 2.3f }, vertex{ 1.2f, 3.2f }, "triangle");
//Shape 容器
list<Shape*> ShapeList{ &rectangle, &circle, &triangle };
//ShapeList pointer
list<Shape*>::iterator it;
//lambda experssion (指標的部分，事後要再弄清楚↓)
auto ByIncreasPerimeter = [&](const Shape* a, const Shape* b)->bool{if ((*a).perimeter() < (*b).perimeter())return true; else return false; };
auto ByDecreasingPerimeter = [&](const Shape* a, const Shape* b)->bool{if ((*a).perimeter() > (*b).perimeter())return true; else return false; };
auto ByIncreasAera = [&](const Shape* a, const Shape* b)->bool{if ((*a).area() < (*b).area())return true; else return false; };
auto ByDecreasingAera = [&](const Shape* a, const Shape* b)->bool{if ((*a).area() > (*b).area())return true; else return false; };
auto ByIncreasCompactness = [&](const Shape* a, const Shape* b)->bool{
	double first = 4 * M_PI*(*a).area() / pow((*a).perimeter(), 2);
	double second = 4 * M_PI*(*b).area() / pow((*b).perimeter(), 2);
	if (first < second)
		return true;
	else
		return false;
};

TEST(Sort, sortByIncreasingPerimeter) {
	ShapeList.sort(ByIncreasPerimeter);
	it = ShapeList.begin();
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
}

TEST(Sort, sortByDecreasingPerimeter) {
	ShapeList.sort(ByDecreasingPerimeter);
	it = ShapeList.begin();
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
}

TEST(Sort, sortByIncreasingArea) {
	ShapeList.sort(ByIncreasAera);
	it = ShapeList.begin();
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
}

TEST(Sort, sortByDecreasingArea) {
	ShapeList.sort(ByDecreasingAera);
	it = ShapeList.begin();
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());

}

TEST(Sort, sortByIncreasingCompactness) {
	ShapeList.sort(ByIncreasCompactness);
	it = ShapeList.begin();
	ASSERT_EQ("triangle(2 2 3.1 2.3 1.2 3.2)", (*it)->toString());
	it++;
	ASSERT_EQ("rectangle(2 3 4 5)", (*it)->toString());
	it++;
	ASSERT_EQ("circle(2 3 4)", (*it)->toString());
}

#endif
