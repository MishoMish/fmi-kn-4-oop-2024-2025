#include <iostream>

class Rational
{
private:
    int a;
    unsigned int b;

    int getGCD(int x, int y) const 
    {
        while (y)
        {
            int r = x % y;
            x = y;
            y = r;
        }

        return x;
    }
    void reduction()
    {
        int gcd = this->getGCD(this->a, this->b);
        this->a /= gcd;
        this->b /= gcd;
    }

public:
    Rational(int x)
    {
        this->a = x;
        this->b = 1;
    }
    Rational(int x, int y)
    {
        if (y == 0)
        {
            std::cout << "Wrong denominator!!!\n";
            this->a = 0;
            this->b = 1;
        }
        else {
            this->a = std::abs(x);
            this->b = std::abs(y);
            
            this->reduction();
            
            if (x * y < 0)
                this->negate();
        }
    }

    bool isZero() const
    {
        return this->a == 0;
    }
    void negate() 
    {
        this->a *= -1;
    }

    void add(const Rational& other)
    {
        this->a = this->a * other.b + other.a * this->b;
        this->b = this->b * other.b;

        this->reduction();
    }

    Rational sum(const Rational& other) const
    {
        Rational res = *this;
        res.add(other);

        return res;
    }

    void sub(const Rational& other)
    {
        Rational negOther = other;
        negOther.negate();

        this->add(negOther);
    }
    void mult(const Rational& other)
    {
        this->a *= other.a;
        this->b *= other.b;

        this->reduction();
    }
    void div(const Rational& other)
    {
        if (other.isZero())
        {
            std::cout << "Invalid division\n";
            return;
        }

        this->a *= other.b;
        this->b *= other.a;

        this->reduction();
    }

    void print() const
    {
        std::cout << '(' << this->a << ", " << this->b <<')';
    }
};

int main()
{
    Rational r1(5), r2(3, 0);
    r1.print(); // (5,1)
    std::cout << ' ';
    r2.print(); // (0,1)
    std::cout << '\n';

    Rational r3(1, 3), r4(5);
    r3.add(r4); // (16,3)
    Rational sum = r3.sum(r4); // (31,3)
    r3.print();
    std::cout << ' ';
    sum.print();
    std::cout << '\n';

    sum.sub(r4); // (16,3)
    sum.print();
    std::cout << '\n';

    sum.div(r3); // (1,1)
    sum.print();
    std::cout << '\n';

}