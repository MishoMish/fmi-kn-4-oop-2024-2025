#include "Quadrilateral.h"
#include "Parallelogram.h"
#include <cmath>

Parrallelogram::Parrallelogram(const Point& a, const Point& b, const Point& c, const Point& d) : Quadrilateral(a,b,c,d) {}

void Parrallelogram::print(std::ostream& os) const {
    os << "Parrallelogram: " << std::endl;
    Quadrilateral::print(os);
}
