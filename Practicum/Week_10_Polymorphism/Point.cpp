#include "Point.h"
#include <cmath>

Point::Point() {
}

Point::Point(double x, double y): _x(x), _y(y){}

double Point::GetX() const {
    return _x;
}

double Point::GetY() const {
    return _y;
}

void Point::SetX(double x) {
    _x = x;
}

void Point::SetY(double y) {
    _y = y;
}

void Point::Print(std::ostream& os) const {
    os << "Point(" << _x << ", " << _y << ")" << std::endl;
}

double Point::DistanceTo(const Point& other) const {
    double dx = _x - other._x;
    double dy = _y - other._y;
    return sqrt(dx * dx + dy * dy);
}