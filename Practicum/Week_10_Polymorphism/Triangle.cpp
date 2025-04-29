#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : _a(a), _b(b), _c(c) {}

double Triangle::area() {
    double ab = _a.DistanceTo(_b);
    double bc = _b.DistanceTo(_c);
    double ca = _c.DistanceTo(_a);
    double s = (ab + bc + ca) / 2.0;
    return sqrt(s * (s - ab) * (s - bc) * (s - ca));
}

double Triangle::perimeter() {
    return _a.DistanceTo(_b) + _b.DistanceTo(_c) + _c.DistanceTo(_a);
}
void Triangle::print(std::ostream& os) const {
    os << "Triangle: " << std::endl;
    os << "A: " << std::endl;
    _a.Print(os);
    os << "B: "<< std::endl;
    _b.Print(os);
    os << "C: "<< std::endl;
    _c.Print(os);
}
