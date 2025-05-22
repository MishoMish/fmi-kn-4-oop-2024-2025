# Обектно ориентирано програмиране - Седмица 2

## Тема: Шаблони. Функции от по-висок ред (указатели към функции, std::function, lambda)

---

## 1. Въведение в шаблоните (Templates)

### Какво представляват шаблоните?

Шаблоните в C++ са механизъм за обобщено програмиране, който позволява писането на код, който може да работи с различни типове данни, без да се дублира логиката. Използват се предимно за създаване на **шаблонни функции** и **шаблонни класове**.

### Шаблонни функции (Function Templates)

Шаблонните функции ни позволяват да дефинираме функция, без да задаваме конкретен тип за нейните аргументи и резултат.

#### **Пример:**

```cpp
#include <iostream>

// Дефиниция на шаблонна функция
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << maxValue(5, 10) << std::endl;   // Извежда: 10
    std::cout << maxValue(3.14, 2.71) << std::endl; // Извежда: 3.14
    return 0;
}
```

### **Задача 1:**

Напишете шаблонна функция `maxValue`, която приема два аргумента от произволен тип и връща по-големия от тях.

#### **Примерно решение:**

```cpp
#include <iostream>

template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << maxValue(42, 35) << std::endl;
    std::cout << maxValue(4.5, 7.2) << std::endl;
    return 0;
}
```

---

## 2. Функции от по-висок ред и указатели към функции

### Какво са функции от по-висок ред?

Функциите от по-висок ред са такива, които приемат като аргумент друга функция или връщат функция като резултат. Това позволява **по-голяма гъвкавост и преизползваемост на кода**.

### Указатели към функции

Указателят към функция е променлива, която съдържа адреса на функция и може да бъде използвана за извикване на тази функция.

#### **Пример:**

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    int (*funcPtr)(int, int) = add;
    std::cout << funcPtr(3, 4) << std::endl; // Извежда: 7
    return 0;
}
```

### **Задача 2:**

Напишете функция `applyOperation`, която приема два `int` аргумента и указател към функция, извършваща някаква операция върху тях (например събиране).

#### **Примерно решение:**

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int applyOperation(int x, int y, int (*operation)(int, int)) {
    return operation(x, y);
}

int main() {
    std::cout << applyOperation(10, 20, add) << std::endl; // 30
    return 0;
}
```

---

## 3. std::function и неговото приложение

### Какво е `std::function`?

`std::function` е обект от **стандартната библиотека**, който позволява съхраняване и извикване на функции с определен подпис (signature). Той е по-гъвкав от указателите към функции, защото поддържа и **lambda** функции и методи на класове.

#### **Пример:**

```cpp
#include <iostream>
#include <functional>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    std::function<int(int, int)> operation = multiply;
    std::cout << operation(5, 3) << std::endl; // 15
    return 0;
}
```

### **Задача 3:**

Преработете `applyOperation` от предишната задача, така че вместо указател към функция, тя да използва `std::function`.

#### **Примерно решение:**

```cpp
#include <iostream>
#include <functional>

int applyOperation(int x, int y, std::function<int(int, int)> operation) {
    return operation(x, y);
}

int main() {
    std::cout << applyOperation(10, 20, [](int a, int b) { return a + b; }) << std::endl; // 30
    return 0;
}
```

---

## 4. Lambda функции

### Какво представляват `lambda` функциите?

`Lambda` функциите са **анонимни функции**, които могат да бъдат дефинирани на място, предавани като аргументи и използвани без да се дефинират отделно.

#### **Пример:**

```cpp
#include <iostream>

int main() {
    auto sum = [](int a, int b) { return a + b; };
    std::cout << sum(3, 4) << std::endl; // 7
    return 0;
}
```

### **Задача 4:**

Използвайте `lambda` функция, за да подадете операция за умножение към `applyOperation`.

#### **Примерно решение:**

```cpp
#include <iostream>
#include <functional>

int applyOperation(int x, int y, std::function<int(int, int)> operation) {
    return operation(x, y);
}

int main() {
    std::cout << applyOperation(10, 20, [](int a, int b) { return a * b; }) << std::endl; // 200
    return 0;
}
```

---

## Обобщение

В този урок разгледахме:
✔️ Шаблони и тяхното приложение за създаване на гъвкави функции.
✔️ Функции от по-висок ред и указатели към функции.
✔️ Използването на `std::function` за съхранение на функции.
✔️ Lambda функции за писане на компактни и удобни анонимни функции.
