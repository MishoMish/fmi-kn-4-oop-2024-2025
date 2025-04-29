#include "Point.h"
#include "Figure.h"
#ifndef Circle_h
#define Circle_h

class  Circle: public Figure {
    public:
        Circle(const Point& a, unsigned int radius);
        double area() override;
        double perimeter() override;
        void print(std::ostream& os = std::cout) const override;

    private:
        Point _c;
        unsigned int _radius;
};

#endif // Circle_h
