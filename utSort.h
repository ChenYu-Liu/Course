#ifndef EXP_H
#define EXP_H
#include "Shapes.h"
#include "Media.h"
#include "Sort.h"
#include <iostream>
using namespace std;

TEST(Sort, sortByIncreasingPerimeter) {
	//list<Shape*> ShapeList;
	//   auto Compare = [&](const double &a ,const double &b)->bool{if(a>b)return true; else return false;};    
	//   list<double> answer {18.0,18.84954};
	//   Rectangle rectangle(2.,3.,4.,5.,"rectangle");
	//   Circle circle(2,3,4,"circle");
	//   //Triangle triangle(,2,3);

	//   ShapeList.push_back(&rectangle);
	//   ShapeList.push_back(&circle);
	//   //ShapeList.push_back(&triangle);
	//   ShapeList.sort(Compare);
	//list<Shape*>::iterator it = ShapeList.begin();
	//ASSERT_EQ("test", "");

}

TEST(mytest)
{
	Rectangle rectangle(2., 3., 4., 5., "rectangle");
	cout << rectangle.perimeter() << "\n";
	Circle circle(2, 3, 4, "circle");
	cout << circle.perimeter() << "\n";
}

//
//TEST (Sort, sortByDecreasingPerimeter) {
//
//}
//
//TEST (Sort, sortByIncreasingArea) {
//
//}
//
//TEST (Sort, sortByDecreasingArea) {
//
//}
//
//TEST (Sort, sortByIncreasingCompactness) {
//
//}
//
#endif
