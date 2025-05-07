#include <iostream>
#include <vector>
#include <algorithm>
 
class SimpleExpression
{
public:
    virtual double getValue() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual SimpleExpression* clone() const = 0;
    virtual ~SimpleExpression() = default;
};
 
class Constant : public SimpleExpression
{
public:
    // Какво ще ни е необходимо за реализиране?
    Constant(double _value)
        : value(_value) {}
 
    double getValue() const override
    {
        return value;
    }
    void print(std::ostream& out = std::cout) const override
    {
        out << value;
    }
    Constant* clone() const
    {
        return new Constant(*this);
    }
 
 
private:
    // Какво да съдържа?
    double value;
};
 
class Max : public SimpleExpression
{
public:
    // Какви методи са необходими?
    Max(const SimpleExpression* const _left, const SimpleExpression* const _right)
    {
        copy(_left, _right);
    }
    Max(const Max& other)
    {
        copy(other.left, other.right);
    }
    Max& operator = (const Max& other)
    {
        if (this != &other)
        {
            deallocate();
            copy(other.left, other.right);
        }
 
        return *this;
    }
 
    // to do:
    Max(Max&& other);
    Max& operator = (Max&& other);
 
 
    double getValue() const override
    {
        return std::max(left->getValue(), right->getValue());
    }
    void print(std::ostream& out = std::cout) const override
    {
        out << "max(";
        left->print(out);
        out << ", ";
        right->print(out);
        out << ")";
    }
    Max* clone() const
    {
        return new Max(*this);
    }
    ~Max()
    {
        deallocate();
    }
 
private:
    void copy(const SimpleExpression* const _left, const SimpleExpression* const _right)
    {
        left = _left->clone();
        right = _right->clone();
    }
    void deallocate()
    {
        delete left;
        delete right;
    }
 
private:
    // Какво да съдържа?
    SimpleExpression *left, *right;
};
 
class Product : public SimpleExpression
{
public:
    // Какво е необходимо?
    double getValue() const override
    {
        double product = 1;
 
        for (const SimpleExpression* const expr : mults)
            product *= expr->getValue();
 
        return product;
    }
    void print(std::ostream& out = std::cout) const override
    {
        out << "prod(";
 
        bool flag = false;
        for (const SimpleExpression* const expr : mults)
        {
            if (flag)
                out << ", ";
            else
                flag = true;
 
            expr->print(out);
        }
 
        out << ")";
    }
 
    void addMultiplier(const SimpleExpression* const newMult)
    {
        mults.push_back(newMult->clone());
    }
 
    Product()
        : mults(std::vector<SimpleExpression*>()) {}
    Product(const std::vector<SimpleExpression*>& _mults)
    {
        for (const SimpleExpression* const expr : _mults)
            addMultiplier(expr);
    }
    Product(const Product& other)
    {
        for (const SimpleExpression* const expr : other)
            addMultiplier(expr);
    }
    Product& operator = (const Product& other)
    {
        if (this != &other)
        {
            for (SimpleExpression* expr : mults)
                delete expr;
 
            // !!!
            mults.clear();
 
            for (const SimpleExpression* const expr : other)
                addMultiplier(expr);
        }
 
        return *this;
    }
 
    // to do:
    Product(Product&& other);
    Product& operator = (Product&& other);
 
    Product* clone() const
    {
        return new Product(*this);
    }
 
    ~Product()
    {
        for (SimpleExpression* expr : mults)
            delete expr;
    }
 
    std::vector<SimpleExpression*>::iterator begin()
    {
        return mults.begin();
    }
    std::vector<SimpleExpression*>::iterator end()
    {
        return mults.end();
    }
    std::vector<SimpleExpression*>::const_iterator begin() const
    {
        return mults.begin();
    }
    std::vector<SimpleExpression*>::const_iterator end() const
    {
        return mults.end();
    }
 
private:
    // Какво е съдържанието?
    std::vector<SimpleExpression*> mults;
};
 
int main()
{
    SimpleExpression* expr =
        new Max(new Product({new Max(new Constant(1.0),
                                     new Constant(2.0)),
                             new Constant(3.0)}),
                new Constant(4.0));
 
    expr->print(std::cout);
    std::cout << '\n' << expr->getValue() << std::endl;
    return 0;
}