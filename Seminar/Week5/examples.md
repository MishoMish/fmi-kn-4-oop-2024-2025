# Въведение - Примери

## Пример 1: Клас `Point`

**Описание:**
Създайте клас `Point`, който представя точка в двумерното пространство.

- Използвайте инициализиращ списък в конструктора.
- Реализирайте копиконструктор.
- Реализирайте деструктор, който отпечатва съобщение.
- Добавете метод за извеждане на координатите.

**Код:**

```cpp
#include <iostream>
class Point {
private:
    int x, y;
public:
    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
    Point(const Point& other) : x(other.x), y(other.y) {
        std::cout << "Copy constructor called!\n";
    }
    ~Point() {
        std::cout << "Destructor called for Point(" << x << ", " << y << ")\n";
    }
    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

int main() {
    Point p1(3, 4);
    Point p2 = p1;
    p1.print();
    p2.print();
    return 0;
}
```

---

## Пример 2: Клас `Student`

**Описание:**
Създайте клас `Student`, който съдържа:

- Име на студента (динамично заделена памет)
- Конструктор с параметър
- Копиконструктор
- Деструктор
- Оператор=
- Метод за извеждане на информацията

**Код:**

```cpp
#include <iostream>
#include <cstring>

class Student {
private:
    char* name;
public:
    Student(const char* studentName) {
        name = new char[strlen(studentName) + 1];
        strcpy(name, studentName);
    }
    Student(const Student& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    Student& operator=(const Student& other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }
    ~Student() {
        delete[] name;
    }
    void print() const {
        std::cout << "Student: " << name << "\n";
    }
};

int main() {
    Student s1("Alice");
    Student s2 = s1;
    s1.print();
    s2.print();
    Student s3("Bob");
    s3 = s1;
    s3.print();
    return 0;
}
```

---

## Пример 3: Клас `Rectangle`

**Описание:**
Създайте клас `Rectangle`, който има:

- Полета `width` и `height`
- Конструктор с параметри
- Копиконструктор
- Деструктор
- Оператор=
- Метод `area()`, който връща площта

**Код:**

```cpp
#include <iostream>

class Rectangle {
private:
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}
    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
        }
        return *this;
    }
    ~Rectangle() {}
    int area() const {
        return width * height;
    }
};

int main() {
    Rectangle r1(4, 5);
    Rectangle r2 = r1;
    std::cout << "Area: " << r2.area() << "\n";
    Rectangle r3(2, 3);
    r3 = r1;
    std::cout << "Area after assignment: " << r3.area() << "\n";
    return 0;
}
```
