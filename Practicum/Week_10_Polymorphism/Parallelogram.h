#include "Point.h"
#include "Figure.h"
#include "Quadrilateral.h"
#ifndef Parrallelogram_h
#define Parrallelogram_h

class Parrallelogram: public Quadrilateral {
    public:
        Parrallelogram(const Point& a, const Point& b, const Point& c, const Point& d);
        void print(std::ostream& out)const override;
};

#endif // Circle_h
