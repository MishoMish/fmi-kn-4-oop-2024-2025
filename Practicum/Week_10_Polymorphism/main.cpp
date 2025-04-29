#include "Triangle.h"
#include "Circle.h"
#include "Parallelogram.h"
// #include "Triangle.h"
// #include "Triangle.h"

void printFigures(Figure** figures){
    for(int i=0;i<5;i++ )
    {
        if(figures[i] != nullptr)
        {
            // std::cout<<
            figures[i]->print();
        }
    }
}












int main(){
    Figure** figures = new Figure*[5]{nullptr, nullptr, nullptr, nullptr, nullptr};
    figures[0] = new Parrallelogram(Point(13, 14), Point(15, 16), Point(17, 18), Point(15, 2));
    // figures[0] = new Circle(Point(1, 2), 3);
    // figures[1] = new Circle(Point(4, 5), 6);
    // figures[2] = new Triangle(Point(1, 2), Point(3, 4), Point(5, 6));
    // figures[3] = new Triangle(Point(7, 8), Point(9, 10), Point(11, 12));
    printFigures(figures);
    for(int i=0;i<5;i++ )
    {
        delete figures[i];
    }
    delete[] figures;
}