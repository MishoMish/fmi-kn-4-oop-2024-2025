#include <iostream>
#include <vector>

class SimpleExpression
{
public:
    virtual double getValue() const = 0;
    virtual void print(std::ostream& out) = 0;
    // досещане 1
    // досещане 2
};

class Constant : public SimpleExpression
{
public:
    // Какво ще ни е необходимо за реализиране?

private:
    // Какво да съдържа?
};

class Max : public SimpleExpression
{
public:
    // Какви методи са необходими?
private:
    // Какво да съдържа?
};

class Product : public SimpleExpression
{
public:
    // Какво е необходимо?
private:
    // Какво е съдържанието?
};