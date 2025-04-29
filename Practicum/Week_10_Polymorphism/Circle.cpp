#include "Circle.h"
#include <cmath>

Circle::Circle(const Point& c,unsigned int r) :  _c(c), _radius(r) {}

double Circle::area() {
    return M_PI * _radius * _radius;
}

double Circle::perimeter() {
    return 2 * M_PI * _radius;
}
void Circle::print(std::ostream& os) const {
    os << "Circle: " << std::endl;
    os << "Center: "<< std::endl;
    _c.Print(os);
    os << "Radius: " << _radius << std::endl;
}
