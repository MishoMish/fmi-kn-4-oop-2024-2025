#include "Quadrilateral.h"
#include "Triangle.h"
#include <cmath>

Quadrilateral::Quadrilateral(const Point& a, const Point& b, const Point& c, const Point& d) : _a(a), _b(b), _c(c), _d(d) {}

double Quadrilateral::area() {
    Triangle t1(_a, _b, _c);
    Triangle t2(_a, _c, _d);
    return t1.area() + t2.area();   
}

double Quadrilateral::perimeter() {
    return _a.DistanceTo(_b) + _b.DistanceTo(_c) + _c.DistanceTo(_d) + _d.DistanceTo(_a);
}
void Quadrilateral::print(std::ostream& os) const {
    os << "Quadrilateral: " << std::endl;
    os << "A: " << std::endl;
    _a.Print(os);
    os << "B: "<< std::endl;
    _b.Print(os);
    os << "C: "<< std::endl;
    _c.Print(os);
    os << "D: "<< std::endl;
    _d.Print(os);
}
