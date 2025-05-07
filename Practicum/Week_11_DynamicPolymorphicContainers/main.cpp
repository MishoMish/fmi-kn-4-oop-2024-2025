#include <iostream>

class Parent
{
public:
    virtual void doSomething() const = 0;
};

class Child : public Parent
{
public:
    void doSomething() const override
    {
        std::cout << "pure virtual method is defined\n";
    }
};

int main()
{
    Parent p;
    return 0;
}