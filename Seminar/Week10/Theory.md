# Теория: Полиморфизъм и Фабрики

## Полиморфизъм (припомняне)

Полиморфизмът позволява работа с обекти от различни типове чрез общ интерфейс. Това става чрез **виртуални методи** и използване на указатели към базовия клас.

```cpp
class Animal {
public:
    virtual void speak() const {
        std::cout << "Some animal sound\n";
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!\n";
    }
};

void makeItSpeak(const Animal* a) {
    a->speak();
}

// makeItSpeak(new Dog()); -> Woof!
```

---

## Какво е Design Pattern

Design pattern е доказано и многократно използвано решение на често срещан проблем при проектиране на софтуер. Това не е конкретен код, а по-скоро **шаблон за архитектурно решение**, което може да се прилага в различни ситуации.

Целта на шаблоните е да:

- Повишат повторната употреба на решения
- Подобрят четимостта и разширяемостта на кода
- Насърчат добри практики и структурираност

Шаблоните най-често се делят на три основни категории:

- **Creational (Създаващи)** – за управление на създаването на обекти (напр. Factory, Singleton, Builder)
- **Structural (Структурни)** – за композиция на обекти и класове (напр. Adapter, Decorator, Composite)
- **Behavioral (Поведенчески)** – за взаимодействие между обекти и разпределение на отговорности (напр. Strategy, Observer, Command)

🔗 [Design Patterns – Refactoring.Guru](https://refactoring.guru/design-patterns)

---

## Вектор от Base\*

Обикновено полиморфизмът се използва със структури от данни, съдържащи указатели към базовия тип:

```cpp
std::vector<Animal*> zoo;
zoo.push_back(new Dog());

for (const auto* a : zoo) {
    a->speak();
}
```

👉 Упражнение: Създайте йерархия от `Shape` (Circle, Rectangle) и направете вектор от `Shape*`, който визуализира всички форми.

---

## Фабрики (Factory Design Pattern)

Фабриката е проектен модел, който централизира създаването на обекти. Идеята е да се използва метод или клас, който скрива логиката по инстанциране.

🔗 [Factory Method – Refactoring.Guru](https://refactoring.guru/design-patterns/factory-method)

### Пример: Фабричен метод

```cpp
class AnimalFactory {
public:
    static Animal* create(const std::string& type) {
        if (type == "dog") return new Dog();
        // добавете други типове
        return nullptr;
    }
};

Animal* a = AnimalFactory::create("dog");
a->speak();
```

👉 Упражнение: Напишете фабрика `ShapeFactory`, която създава различни обекти от тип `Shape` според подаден низ – "circle", "rectangle" и т.н.

### Предимства на фабриките

- Централизирана логика на създаване
- Лесно добавяне на нови типове
- Скриване на конкретните класове от потребителя

👉 Упражнение (по избор): Разширете `ShapeFactory` с възможност за регистрация на типове чрез map и функции.

---

## Идеи за разширение на фабриките

- Регистрация на типове чрез map (plugin система)
- Абстрактна фабрика (фабрика, която създава група от свързани обекти)
- Сериализация / десериализация с типова информация (напр. "type": "dog")

👉 Упражнение: Реализирайте прост JSON-like сериализатор и десериализатор на обекти `Shape`, който използва фабриката, за да създава правилния тип.

## Factory в контекста на полиморфизъм

Фабриката и полиморфизмът често вървят ръка за ръка. Основната идея е, че фабриката връща указател към базовия клас (Base\*), а реалният обект, който се създава, е от производен клас. Така може да работим с обекти от различни типове чрез общ интерфейс.

```cpp
Animal\* a = AnimalFactory::create("dog");
makeItSpeak(a); // -> Woof!
```

Това позволява:

- гъвкавост при добавяне на нови типове животни без промяна на клиентския код
- централизирано управление на инстанции
- използване на съществуващ полиморфен интерфейс (напр. speak())

> Важно: За да използваме фабрика ефективно с полиморфизъм, е задължително базовият клас да има виртуални методи и виртуален деструктор.

---

## Други свързани шаблони

### Strategy

Позволява подмяна на поведение в runtime. Например различни алгоритми за филтриране, компресия и т.н.

🔗 [Strategy – Refactoring.Guru](https://refactoring.guru/design-patterns/strategy)

```cpp
class CompressionStrategy {
public:
    virtual void compress(const std::string& filename) = 0;
    virtual ~CompressionStrategy() {}
};

class ZipCompression : public CompressionStrategy {
    void compress(const std::string& filename) override {
        std::cout << "Compressing " << filename << " as ZIP\n";
    }
};
```

👉 Упражнение: Напишете стратегия за рисуване на `Shape` – например ASCII представяне, SVG представяне и др.

### Singleton

Клас, от който има точно един обект (например Logger, Config). Може да се използва във фабрики при централизирано управление.

🔗 [Singleton – Refactoring.Guru](https://refactoring.guru/design-patterns/singleton)

👉 Упражнение: Направете клас `ShapeRegistry`, който е Singleton и съхранява всички създадени фигури.

### Prototype

Използва се за клониране на обекти. Вместо `new`, извикваме `.clone()` върху съществуващ обект. Полезно при дълбоки йерархии или когато създаването е скъпо.

🔗 [Prototype – Refactoring.Guru](https://refactoring.guru/design-patterns/prototype)

👉 Упражнение: Добавете виртуален метод `clone()` в `Shape` и имплементирайте го за няколко подтипа.

### Builder

Използва се за създаване на сложни обекти стъпка по стъпка. Може да се комбинира с фабриката, когато обектите имат множество опционални параметри.

🔗 [Builder – Refactoring.Guru](https://refactoring.guru/design-patterns/builder)

👉 Упражнение: Създайте `ShapeBuilder`, който позволява поетапно конструиране на фигура (напр. задаване на цвят, координати и др.)

---

> В този модул фокусът е основно върху **Factory**, но е добре студентите да разпознават и другите модели и да могат да ги разграничават по предназначение и структура.
