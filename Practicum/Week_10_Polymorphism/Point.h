#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
    public:
    Point();
    Point(double x, double y);
    
    double GetX() const;
    double GetY() const;
    
    void SetX(double x);
    void SetY(double y);
    
    void Print(std::ostream& os = std::cout) const;
    
    double DistanceTo(const Point& other) const;
    
    private:
    double _x; 
    double _y; 
};

#endif