# Решение на Примерни Задачи

## Устройства

```cpp
#include <iostream>
using namespace std;

class Device {
public:
    virtual void info() { cout << "Generic Device\n"; }
};

class Phone : public Device {
public:
    void info() override { cout << "Phone\n"; }
};

class Laptop : public Device {
public:
    void info() override { cout << "Laptop\n"; }
};

void printInfo(Device* d) {
    d->info();
}

int main() {
    Phone p;
    Laptop l;
    printInfo(&p); // Phone
    printInfo(&l); // Laptop
    return 0;
}
```

## Храни

```cpp
#include <iostream>
using namespace std;

class Food {
public:
    virtual int calories() const = 0;
};

class Apple : public Food {
public:
    int calories() const override { return 52; }
};

class Burger : public Food {
public:
    int calories() const override { return 300; }
};

int main() {
    Apple a;
    Burger b;
    cout << a.calories() << endl; // 52
    cout << b.calories() << endl; // 300
    return 0;
}
```
