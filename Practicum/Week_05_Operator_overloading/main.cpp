#include <cstring> 
#include <iostream>

class A {
public:
    char name[50];
};
int main() {
    A a;
    strcpy(a.name, "abc");
    A b(a);
    std::cout << a.name << ' ' << b.name << '\n';
    
    b.name[1] = 'B';
    std::cout << a.name << ' ' << b.name << '\n';

    A c;
    c = a;
    std::cout << a.name << ' ' << c.name << '\n';
    
    c.name[1] = '#';
    std::cout << a.name << ' ' << c.name << '\n';
    return 0;
}