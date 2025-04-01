#include <iostream>
#include "Vector.h"

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9,10};

    Vector v(sizeof(a)/sizeof(a[0]), a);

    // for (Vector::Iterator it = v.begin(); it != v.end(); ++it)
    // {
    //     //(*it)++;

    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;


    // for (Vector::ConstIterator it = v.const_begin(); it != v.const_end(); ++it)
    // {
    //     (*it)++;
        
    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;

    for (int& a : v)
    {
        a++;
        
        std::cout << a << ' ';
    }
    std::cout << std::endl;

    for (int& a : v)
    {   
        std::cout << a << ' ';
    }
    std::cout << std::endl;

    return 0;
}