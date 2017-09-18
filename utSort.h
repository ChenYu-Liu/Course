#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

list<Shape*> ShapeList;
const double epsilon = 0.000001;

TEST (Sort, sortByIncreasingPerimeter) {
    auto Compare = [&](const double &a ,const double &b)->bool{if(a>b)return true; else return false;};    
    list<double> answer {18.0,18.84954};
    Rectangle rectangle(2,3,4,5,"rectangle");
    Circle circle(2,3,4,"circle");
    Triangle triangle(4,2,3,"triangle");

    ShapeList.push_back(rectangle.perimeter());
    ShapeList.push_back(circle.perimeter());
    ShapeList.push_back(triangle.perimeter());
    ShapeList.Sort(Compare);

    list<double>::iterator itans;
    itans = answer.begin();
    list<double>::Iterator it;
    for(it = ShapeList.begin();it!=ShapeList.end();it++,itans++)
    {
        ASSERT_EQ(it,itans,epsilon);    
    }
    
}

TEST (Sort, sortByDecreasingPerimeter) {

}

TEST (Sort, sortByIncreasingArea) {

}

TEST (Sort, sortByDecreasingArea) {

}

TEST (Sort, sortByIncreasingCompactness) {

}

#endif
