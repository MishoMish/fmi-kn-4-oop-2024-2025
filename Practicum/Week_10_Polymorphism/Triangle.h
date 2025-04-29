#ifndef Triangle_h
#define Triangle_h

#include "Figure.h"
#include "Point.h"

class Triangle : public Figure {
    public:
        Triangle(const Point& a, const Point& b, const Point& c);
        double area() override;
        double perimeter() override;
        void print(std::ostream& os = std::cout) const override;

    private:
        Point _a;
        Point _b;
        Point _c;
};

#endif // Triangle_h