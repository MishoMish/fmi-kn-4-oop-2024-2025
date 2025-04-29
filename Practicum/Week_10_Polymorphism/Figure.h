#ifndef Figure_h
#define Figure_h
#include <iostream>
class Figure{
    public:
    Figure(){};
    virtual double area();
    virtual double perimeter();
    
    virtual void print(std::ostream& os = std::cout) const;
};

#endif // Figure_h