#include "Point.h"
#include "Figure.h"
#ifndef Quadrilateral_h
#define Quadrilateral_h

class Quadrilateral: public Figure {
    public:
        Quadrilateral(const Point& a, const Point& b, const Point& c, const Point& d);
        double area() override;
        double perimeter() override;
        void print(std::ostream& os = std::cout) const override;

    protected:
        Point _a;
        Point _b;
        Point _c;
        Point _d;

};

#endif // Circle_h
