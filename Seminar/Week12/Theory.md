# SOLID принципите в обектно-ориентираното програмиране

## Въведение

SOLID е акроним, представляващ пет основни принципа на обектно-ориентираното програмиране и дизайн, които целят да направят софтуера по-разширяем, поддръжкаем и лесен за разбиране. Този документ обяснява всеки принцип с примери, предимства, недостатъци и връзки с други ООП концепции.

## Принципи

### 1. **S – Single Responsibility Principle (SRP)**

> "Класът трябва да има само една причина да се променя."

#### Обяснение:

Всеки клас трябва да отговаря за една функционалност, което улеснява тестването, рефакторирането и поддръжката.

#### Пример:

**Грешно:**

```cpp
class Report {
public:
    void generate();
    void print();
    void saveToFile();
};
```

**Правилно:**

```cpp
class ReportGenerator {
public:
    void generate();
};

class ReportPrinter {
public:
    void print(const ReportGenerator&);
};

class ReportFileSaver {
public:
    void saveToFile(const ReportGenerator&);
};
```

**Предимства:**

- Лесно тестване и поддръжка.
- Намалява сложността на класовете.

**Недостатъци:**

- Може да доведе до повече класове, което увеличава сложността на проекта.

**Връзка с ООП концепции:**

- Подобрява модулността, улеснява unit тестването.
- Съвместим с шаблони като Command или Facade.

---

### 2. **O – Open/Closed Principle (OCP)**

> "Софтуерните елементи трябва да бъдат отворени за разширение, но затворени за промяна."

#### Обяснение:

Новата функционалност се добавя чрез нови класове, без да се променя съществуващият код.

#### Пример:

```cpp
class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return M_PI * radius * radius; }
};
```

**Предимства:**

- Лесно разширяване на системата.
- Намалява риска от регресии.

**Недостатъци:**

- Изисква внимателно планиране на абстракции.
- Може да усложни първоначалния дизайн.

**Връзка с ООП концепции:**

- Често се използва с шаблони като Strategy или Factory.
- Подходящ за системи с динамично разширяване (напр. плагини).

**UML диаграма (описание):**

- Абстрактен клас `Shape` с метод `area`.
- `Rectangle` и `Circle` наследяват `Shape`.

---

### 3. **L – Liskov Substitution Principle (LSP)**

> "Обектите от подтипове трябва да могат да заместят обекти от базовия тип без да променят правилното поведение."

#### Обяснение:

Наследниците на клас трябва да се държат коректно, когато се използват вместо базовия клас.

#### Пример (проблемен):

```cpp
class Rectangle {
protected:
    int width, height;
public:
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    int getArea() { return width * height; }
};

class Square : public Rectangle {
public:
    void setWidth(int w) override {
        width = height = w;
    }
    void setHeight(int h) override {
        width = height = h;
    }
};
```

**Проблем:** `Square` нарушава очакванията за `Rectangle`, защото променя ширината и височината едновременно.

**Рефакториран код:**

```cpp
class Shape {
public:
    virtual int getArea() const = 0;
};

class Rectangle : public Shape {
protected:
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    int getArea() const override { return width * height; }
};

class Square : public Shape {
    int side;
public:
    Square(int s) : side(s) {}
    int getArea() const override { return side * side; }
};
```

**Предимства:**

- Гарантира коректно поведение на наследниците.
- Улеснява полиморфизма.

**Недостатъци:**

- Може да усложни йерархията на класовете.
- Изисква внимателен дизайн на базовия клас.

**Връзка с ООП концепции:**

- Свързан с полиморфизъм и правилен дизайн на наследяване.
- Използва се в шаблони като Template Method.

---

### 4. **I – Interface Segregation Principle (ISP)**

> "Клиентите не трябва да бъдат принуждавани да зависят от интерфейси, които не използват."

#### Обяснение:

Интерфейсите трябва да бъдат малки и специфични, за да избегнат излишни методи.

#### Пример:

```cpp
class IPrintable {
public:
    virtual void print() const = 0;
};

class IScannable {
public:
    virtual void scan() = 0;
};

class Printer : public IPrintable {
public:
    void print() const override { /* Печат */ }
};

class Scanner : public IScannable {
public:
    void scan() override { /* Сканира */ }
};
```

**Предимства:**

- Намалява ненужните зависимости.
- Улеснява поддръжката на класовете.

**Недостатъци:**

- Може да доведе до повече интерфейси.
- Изисква внимателно проектиране.

**Връзка с ООП концепции:**

- Свързан с модулност и шаблони като Adapter.
- Подпомага разделянето на функционалност в microservices.

---

### 5. **D – Dependency Inversion Principle (DIP)**

> "Модули на високо ниво не трябва да зависят от модули на ниско ниво. И двете трябва да зависят от абстракции."

#### Обяснение:

Класовете трябва да зависят от абстракции, а не от конкретни имплементации.

#### Пример:

```cpp
class IMessageSender {
public:
    virtual void send(const std::string& msg) = 0;
};

class EmailSender : public IMessageSender {
public:
    void send(const std::string& msg) override { /* Изпраща имейл */ }
};

class NotificationManager {
    IMessageSender& sender;
public:
    NotificationManager(IMessageSender& s) : sender(s) {}
    void notify() { sender.send("Hello!"); }
};
```

**Предимства:**

- Гъвкавост при смяна на имплементации.
- Улеснява тестването чрез mock обекти.

**Недостатъци:**

- Изисква допълнителна конфигурация (напр. dependency injection).
- Може да добави сложност в малки проекти.

**Връзка с ООП концепции:**

- Свързан с шаблона Dependency Injection.
- Подходящ за архитектури като Clean Architecture.

---

## Чести грешки при прилагане на SOLID

1. **SRP:** Прекомерно разделяне на класове, което води до ненужна сложност.
2. **OCP:** Неправилно проектиране на абстракции, което ограничава разширяемостта.
3. **LSP:** Неправилно наследяване, което нарушава поведението на базовия клас.
4. **ISP:** Създаване на твърде много интерфейси, което затруднява поддръжката.
5. **DIP:** Неправилно инжектиране на зависимости, което води до твърди връзки.

## Ресурси за допълнително изучаване

- **Книги:**
  - "Clean Code" от Robert C. Martin
  - "Design Patterns" от Erich Gamma и др.
- **Онлайн курсове:**
  - Pluralsight: "SOLID Principles in C++"
  - Udemy: "Object-Oriented Design"
- **Инструменти:**
  - Boost.DI за dependency injection в C++.
  - Google Test за unit тестване.

## Заключение

SOLID принципите са основа за създаването на качествен, поддръжкаем и разширяем софтуер. Те са особено полезни в големи проекти, където промените са чести. Правилното им прилагане изисква баланс, за да се избегне прекомерна сложност.
