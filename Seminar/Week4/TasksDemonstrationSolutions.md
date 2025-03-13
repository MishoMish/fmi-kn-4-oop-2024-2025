# Решения на примерните задачи

## **Решение 1: Клас "Автомобил"**

```cpp
#include <iostream>
#include <string>

class Car
{
private:
    std::string brand;
    int year;
    int counter = 0;

public:
    Car(std::string b, int y) : brand(b), year(y) {}
    std::string sellCar(int numSold)
    {
        counter += numSold;
        return "Sold a car with the brand " + brand;
    }
    std::string numSoldCars()
    {
        return "Number of sold cars with brand " + brand + " is " + std::to_string(counter);
    }
    std::string getInfo()
    {
        return "Brand: " + brand + ", Year: " + std::to_string(year);
    }
};

int main()
{
    Car c("Toyota", 2020);
    std::cout << c.getInfo() << std::endl;
    std::cout << c.sellCar(1) << std::endl;
    std::cout << c.sellCar(2) << std::endl;
    std::cout << c.sellCar(3) << std::endl;
    std::cout << c.sellCar(4) << std::endl;

    std::cout << c.numSoldCars() << std::endl;

    return 0;
}
```

---

## **Решение 2: Клас "Служител"**

```cpp
#include <iostream>
#include <string>

class Employee
{
private:
    std::string name;
    double salary;
    double startingSalary;

public:
    Employee(std::string n, double s) : name(n), salary(s), startingSalary(s) {}

    void increaseSalary(double percent)
    {
        salary += salary * (percent / 100);
    }

    void decreaseSalary(double percent)
    {
        salary -= salary * (percent / 100);
    }

    double getIncreasement()
    {
        return salary - startingSalary;
    }
    double getStartSalary()
    {
        return startingSalary;
    }

    double getSalary()
    {
        return salary;
    }
};

int main()
{
    Employee e("Petar", 1500);
    e.increaseSalary(10);
    e.decreaseSalary(13);
    e.increaseSalary(20);
    e.decreaseSalary(11);
    e.increaseSalary(35);

    std::cout << e.getSalary() << std::endl;
    std::cout << e.getStartSalary() << std::endl;
    std::cout << e.getIncreasement() << std::endl;

    return 0;
}
```

---

## **Решение 3: Клас "Правоъгълник"**

```cpp
#include <iostream>
#include <string>

class Rectangle
{
private:
    std::string name;
    double width, height;

public:
    Rectangle(std::string n, double w, double h) : name(n), width(w), height(h) {}

    double getWidth()
    {
        return width;
    }

    double getHeight()
    {
        return height;
    }

    double getArea()
    {
        return width * height;
    }

    double getPerimeter()
    {
        return 2 * (width + height);
    }

    std::string printInfo()
    {
        return name + " with width = " + std::to_string(width) +
               ", height = " + std::to_string(height) +
               ", area = " + std::to_string(getArea()) +
               ", perimeter = " + std::to_string(getPerimeter());
    }
};

int compareRectArea(Rectangle r1, Rectangle r2)
{
    double area1 = r1.getArea();
    double area2 = r2.getArea();

    if (area1 > area2)
        return 1;
    if (area1 < area2)
        return -1;
    return 0;
}

int compareRectPerimeter(Rectangle r1, Rectangle r2)
{
    double perim1 = r1.getPerimeter();
    double perim2 = r2.getPerimeter();

    if (perim1 > perim2)
        return 1;
    if (perim1 < perim2)
        return -1;
    return 0;
}

int main()
{
    Rectangle r1("Rectangle1", 2, 10);
    Rectangle r2("Rectangle2", 1, 12);

    std::cout << r1.printInfo() << std::endl;
    std::cout << r2.printInfo() << std::endl;

    int areaComparison = compareRectArea(r1, r2);
    if (areaComparison > 0)
        std::cout << "Rectangle1 has a larger area than Rectangle2." << std::endl;
    else if (areaComparison < 0)
        std::cout << "Rectangle2 has a larger area than Rectangle1." << std::endl;
    else
        std::cout << "Both rectangles have the same area." << std::endl;

    int perimeterComparison = compareRectPerimeter(r1, r2);
    if (perimeterComparison > 0)
        std::cout << "Rectangle1 has a larger perimeter than Rectangle2." << std::endl;
    else if (perimeterComparison < 0)
        std::cout << "Rectangle2 has a larger perimeter than Rectangle1." << std::endl;
    else
        std::cout << "Both rectangles have the same perimeter." << std::endl;

    return 0;
}
```
