# Наследяване и Полиморфизъм в C++

## Наследяване - уводни бележки

### Идеята за наследяване

Наследяването е концепция, при която нови класове могат да бъдат създавани въз основа на вече съществуващи. Новият клас (наследник) автоматично получава членовете (променливи и методи) на родителския клас, като може да добавя нови или да променя съществуващите.

### 'is-a' vs. 'has-a' отношения

- **is-a** – показва, че един клас е специализация на друг (наследяване): `Куче is-a Животно`.
- **has-a** – показва, че един клас съдържа друг като част (композиция): `Кола has-a Двигател`.

## Плюсове на наследяването

- Повторна употреба на код (reuse).
- По-ясна и логична йерархия.
- По-лесна поддръжка и разширяемост.
- Улеснява полиморфизма и абстракцията.

## Синтаксис на наследяване

```cpp
class Base {
protected:
    int x;
public:
    void sayHello() { std::cout << "Hello from Base!\n"; }
};

class Derived : public Base {
    // x е достъпен, sayHello() също
};
```

### Видове наследяване:

- **public** – запазва достъпа на членовете.
- **protected** – public и protected членове стават protected.
- **private** – всичко става private.

## Жизнен цикъл на обект при наследяване

При създаване на обект от производен клас:

1. Първо се извиква конструкторът на базовия клас.
2. След това – конструкторът на производния.
   При унищожаване – редът е обратен: първо производният, после базовият деструктор.

## Предефиниране vs. Полиморфизъм

### Предефиниране (Override)

Позволява наследник да замести функция от базовия клас.

### Полиморфизъм

Позволява на обект да се държи по различен начин в зависимост от конкретния тип на инстанцията.

#### Виртуални функции

```cpp
class Animal {
public:
    virtual void makeSound() { std::cout << "Some sound\n"; }
};

class Dog : public Animal {
public:
    void makeSound() override { std::cout << "Bark\n"; }
};
```

#### Абстрактни класове

```cpp
class Shape {
public:
    virtual double area() const = 0; // Чисто виртуална функция
};
```

## The Diamond problem

```cpp
class A { public: void f(); };
class B : public A {};
class C : public A {};
class D : public B, public C {}; // Конфликт: 2x A

// Решение:
class B : virtual public A {};
class C : virtual public A {};
```

## Пример: Йерархия от фигури

```cpp
class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
};
```

# Задача за упражнение

Създайте клас `Person` с метод `introduce()`, който извежда име. Направете клас `Student`, който наследява `Person` и добавя `facultyNumber`. Предефинирайте `introduce()` така, че да извежда и двата атрибута.

## Подсказка:

```cpp
class Person {
    std::string name;
public:
    Person(std::string n) : name(n) {}
    virtual void introduce();
};

class Student : public Person {
    int facultyNumber;
public:
    Student(std::string n, int fn);
    void introduce() override;
};
```

## Заключение

Наследяването и полиморфизмът позволяват изграждане на по-гъвкав и разширяем код чрез абстракции, повторна употреба и специализация на поведение.
