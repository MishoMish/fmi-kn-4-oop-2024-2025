# C++ Constructors & Operators Cheat Sheet

## **1. Конструктори**

### **Стандартен конструктор**

```cpp
class Example {
public:
    Example() {
        std::cout << "Default constructor\n";
    }
};
```

### **Конструктор с параметри**

```cpp
class Example {
private:
    int value;
public:
    Example(int v) : value(v) {} // Инициализиращ списък
};
```

### **Копиконструктор (Copy Constructor)**

```cpp
class Example {
private:
    int value;
public:
    Example(const Example& other) : value(other.value) {
        std::cout << "Copy constructor called\n";
    }
};
```

### **Move Constructor (Конструктор за преместване)**

```cpp
class Example {
private:
    int* data;
public:
    Example(int v) {
        data = new int(v);
    }
    Example(Example&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Move constructor called\n";
    }
};
```

---

## **2. Оператори**

### **Оператор `=` (Присвояване)**

```cpp
class Example {
private:
    int* data;
public:
    Example& operator=(const Example& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }
};
```

### **Оператор `+` (Събиране)**

```cpp
class Example {
private:
    int value;
public:
    Example(int v) : value(v) {}
    Example operator+(const Example& other) const {
        return Example(value + other.value);
    }
};
```

### **Оператор `==` (Сравнение)**

```cpp
class Example {
private:
    int value;
public:
    bool operator==(const Example& other) const {
        return value == other.value;
    }
};
```

### **Оператор `<<` (Извеждане)**

```cpp
#include <iostream>
class Example {
private:
    int value;
public:
    Example(int v) : value(v) {}
    friend std::ostream& operator<<(std::ostream& os, const Example& obj) {
        os << "Value: " << obj.value;
        return os;
    }
};
```

### **Оператор `>>` (Въвеждане)**

```cpp
#include <iostream>
class Example {
private:
    int value;
public:
    friend std::istream& operator>>(std::istream& is, Example& obj) {
        is >> obj.value;
        return is;
    }
};
```

---

## **3. Destructor (Деструктор)**

```cpp
class Example {
public:
    ~Example() {
        std::cout << "Destructor called!\n";
    }
};
```
