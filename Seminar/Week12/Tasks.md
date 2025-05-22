# Задачи: SOLID принципи в ООП

## Въведение

Този документ съдържа практически задачи за прилагане на SOLID принципите в обектно-ориентираното програмиране. Всяка задача включва описание на проблема, неправилен код (където е приложимо), и пример за рефакториран код, спазващ съответния принцип. Добавени са и насоки за самопроверка.

## Задача 1: Единствена отговорност (SRP)

**Описание:**  
Даден е клас `Invoice`, който включва методи за:

- добавяне на продукти;
- изчисляване на сума;
- принтиране на фактурата;
- запис във файл.

**Изискване:**  
Реорганизирайте кода, така че всеки клас да има само една отговорност.

**Неправилен код (нарушава SRP):**

```cpp
class Invoice {
public:
    void addProduct(Product p) { /* Добавя продукт */ }
    double calculateTotal() { /* Изчислява обща сума */ }
    void print() { /* Принтира на конзолата */ }
    void saveToFile() { /* Записва във файл */ }
};
```

**Рефакториран код:**

```cpp
class Invoice {
public:
    void addProduct(Product p) { /* Добавя продукт */ }
    double calculateTotal() { /* Изчислява обща сума */ }
};

class InvoicePrinter {
public:
    void print(const Invoice& invoice) { /* Принтира на конзолата */ }
};

class InvoiceFileSaver {
public:
    void saveToFile(const Invoice& invoice) { /* Записва във файл */ }
};
```

**Обяснение:**  
Класът `Invoice` сега отговаря само за управлението на продукти и изчислението на сумата. Печатането и записът във файл са отделени в собствени класове, което улеснява тестването и поддръжката.

**Насоки за проверка:**

- Проверете дали всеки клас има само една причина за промяна.
- Уверете се, че добавянето на нов формат за печатане (напр. PDF) не изисква промяна в `Invoice`.

**UML диаграма (описание):**

- `Invoice` съдържа методи `addProduct` и `calculateTotal`.
- `InvoicePrinter` и `InvoiceFileSaver` имат връзка на зависимост към `Invoice`.

---

## Задача 2: Open/Closed Principle (OCP)

**Описание:**  
Имаме клас `DiscountCalculator`, който изчислява намаления за стандартни клиенти.

**Изискване:**  
Добавете нов тип клиент (напр. VIP клиент), без да променяте съществуващия код в `DiscountCalculator`.

**Неправилен код (нарушава OCP):**

```cpp
class DiscountCalculator {
public:
    double calculateDiscount(double amount, std::string clientType) {
        if (clientType == "Standard") return amount * 0.1;
        return 0.0; // Няма поддръжка за други типове
    }
};
```

**Рефакториран код:**

```cpp
class IDiscount {
public:
    virtual double calculateDiscount(double amount) const = 0;
};

class StandardClientDiscount : public IDiscount {
public:
    double calculateDiscount(double amount) const override {
        return amount * 0.1; // 10% отстъпка
    }
};

class VIPClientDiscount : public IDiscount {
public:
    double calculateDiscount(double amount) const override {
        return amount * 0.2; // 20% отстъпка
    }
};

class DiscountCalculator {
    IDiscount& discount;
public:
    DiscountCalculator(IDiscount& d) : discount(d) {}
    double calculate(double amount) { return discount.calculateDiscount(amount); }
};
```

**Обяснение:**  
Използването на интерфейс `IDiscount` позволява добавянето на нови типове клиенти (напр. `PremiumClientDiscount`) без промяна в `DiscountCalculator`.

**Насоки за проверка:**

- Добавете нов тип клиент (напр. `PremiumClientDiscount`) и проверете дали `DiscountCalculator` работи без промяна.
- Уверете се, че новите типове клиенти не засягат съществуващите.

**UML диаграма (описание):**

- Интерфейс `IDiscount` с метод `calculateDiscount`.
- Класове `StandardClientDiscount` и `VIPClientDiscount` наследяват `IDiscount`.
- `DiscountCalculator` зависи от `IDiscount`.

---

## Задача 3: Liskov Substitution Principle (LSP)

**Описание:**  
Имаме класове `Bird`, `Penguin` и `Sparrow`. Всички имат метод `fly()`, но пингвините не могат да летят.

**Изискване:**  
Преработете йерархията, така че да не нарушава LSP. Предложете по-добра абстракция.

**Неправилен код (нарушава LSP):**

```cpp
class Bird {
public:
    virtual void fly() = 0;
};

class Sparrow : public Bird {
    void fly() override { /* Лети */ }
};

class Penguin : public Bird {
    void fly() override { throw std::logic_error("Penguins can't fly!"); }
};
```

**Рефакториран код:**

```cpp
class Bird {
public:
    virtual void move() = 0;
};

class FlyingBird : public Bird {
public:
    void move() override { /* Лети */ }
};

class WalkingBird : public Bird {
public:
    void move() override { /* Ходи */ }
};

class Sparrow : public FlyingBird {};
class Penguin : public WalkingBird {};
```

**Обяснение:**  
Абстракцията `Bird` сега използва по-общ метод `move()`, а конкретните поведения (летене, ходене) са разделени в подкласове `FlyingBird` и `WalkingBird`. Това позволява `Penguin` и `Sparrow` да се използват взаимозаменяемо като `Bird` без грешки.

**Насоки за проверка:**

- Проверете дали можете да използвате `Penguin` или `Sparrow` навсякъде, където се очаква `Bird`.
- Уверете се, че няма изключения или неочаквано поведение при извикване на `move()`.

**UML диаграма (описание):**

- Абстрактен клас `Bird` с метод `move`.
- `FlyingBird` и `WalkingBird` наследяват `Bird`.
- `Sparrow` наследява `FlyingBird`, `Penguin` наследява `WalkingBird`.

---

## Задача 4: Interface Segregation Principle (ISP)

**Описание:**  
Имаме интерфейс `IM exceptoIMachine`, който има методи `print()`, `scan()` и `fax()`. Някои устройства могат само да печатат.

**Изискване:**  
Разделете интерфейса, така че устройства с ограничена функционалност да не имплементират излишни методи.

**Неправилен код (нарушава ISP):**

```cpp
class IMachine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class Printer : public IMachine {
    void print() override { /* Печат */ }
    void scan() override { throw std::logic_error("Not supported"); }
    void fax() override { throw std::logic_error("Not supported"); }
};
```

**Рефакториран код:**

```cpp
class IPrintable {
public:
    virtual void print() = 0;
};

class IScannable {
public:
    virtual void scan() = 0;
};

class IFaxable {
public:
    virtual void fax() = 0;
};

class Printer : public IPrintable {
    void print() override { /* Печат */ }
};

class MultiFunctionDevice : public IPrintable, IScannable, IFaxable {
    void print() override { /* Печат */ }
    void scan() override { /* Сканира */ }
    void fax() override { /* Изпраща факс */ }
};
```

**Обяснение:**  
Интерфейсът `IMachine` е разделен на три по-малки интерфейса (`IPrintable`, `IScannable`, `IFaxable`). Устройства като `Printer` имплементират само необходимите интерфейси, без да изпълняват ненужни методи.

**Насоки за проверка:**

- Проверете дали устройствата имплементират само нужните интерфейси.
- Уверете се, че добавянето на ново устройство (напр. само сканиращо) не изисква излишни методи.

**UML диаграма (описание):**

- Интерфейси `IPrintable`, `IScannable`, `IFaxable`.
- `Printer` имплементира само `IPrintable`.
- `MultiFunctionDevice` имплементира всичките три интерфейса.

---

## Задача 5: Dependency Inversion Principle (DIP)

**Описание:**  
Имаме клас `OrderProcessor`, който директно създава обект от тип `EmailSender` вътре в себе си и изпраща потвърждение.

**Изискване:**  
Променете дизайна, така че `OrderProcessor` да зависи от абстракция (`IMessageSender`), а не от конкретна имплементация. Инжектирайте зависимостта отвън.

**Неправилен код (нарушава DIP):**

```cpp
class OrderProcessor {
    EmailSender sender;
public:
    void process() {
        sender.send("Order processed!");
    }
};
```

**Рефакториран код:**

```cpp
class IMessageSender {
public:
    virtual void send(const std::string& msg) = 0;
};

class EmailSender : public IMessageSender {
public:
    void send(const std::string& msg) override { /* Изпраща имейл */ }
};

class SmsSender : public IMessageSender {
public:
    void send(const std::string& msg) override { /* Изпраща SMS */ }
};

class OrderProcessor {
    IMessageSender& sender;
public:
    OrderProcessor(IMessageSender& s) : sender(s) {}
    void process() {
        sender.send("Order processed!");
    }
};
```

**Обяснение:**  
`OrderProcessor` сега зависи от абстракцията `IMessageSender`, а не от конкретния `EmailSender`. Зависимостта се инжектира отвън, което позволява лесна замяна с `SmsSender` или други имплементации.

**Насоки за проверка:**

- Проверете дали можете да смените `EmailSender` с `SmsSender` без промяна в `OrderProcessor`.
- Уверете се, че няма твърда връзка с конкретна имплементация.

**UML диаграма (описание):**

- Интерфейс `IMessageSender` с метод `send`.
- `EmailSender` и `SmsSender` имплементират `IMessageSender`.
- `OrderProcessor` зависи от `IMessageSender`.

---

## Допълнителна задача – анализ на реален код

**Описание:**  
Изберете клас от ваш проект или от open-source C++ библиотека.

**Изискване:**  
Анализирайте кои от SOLID принципите се спазват и кои се нарушават. Предложете подобрения.

**Пример за анализ (Boost.Asio – io_context):**

- **SRP:** Класът `io_context` в Boost.Asio управлява асинхронни операции и събития. Той обаче понякога се използва за различни цели (напр. таймери, мрежови операции), което може да се разглежда като нарушение на SRP.  
  **Подобрение:** Разделяне на функционалността в специализирани класове (напр. `TimerContext`, `NetworkContext`).
- **OCP:** Boost.Asio позволява добавяне на нови асинхронни операции чрез шаблони и callbacks, което спазва OCP.
- **LSP:** Не е приложимо директно, тъй като `io_context` не участва в сложна йерархия.
- **ISP:** Интерфейсът на `io_context` е общ и може да принуди потребителите да използват методи, които не са им нужни.  
  **Подобрение:** Въвеждане на по-малки интерфейси за специфични операции.
- **DIP:** `io_context` често се използва директно, което създава твърди зависимости.  
  **Подобрение:** Въвеждане на абстракция като `IAsyncContext` за инжектиране на зависимости.

**Насоки за проверка:**

- Изберете клас от вашия проект и го анализирайте по същия начин.
- Направете UML диаграма на текущото състояние и предложените промени.
