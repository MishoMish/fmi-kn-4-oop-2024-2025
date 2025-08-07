# C++ Подготвително упражнение – тренинг тест

## Инструкции

Това е тренировъчен тест, целящ да ви подготви за изпита по теория OОП. **ОТГОВОРИТЕ НЕ СА ПРЕДОСТАВЕНИ** – целта е да ги откриете чрез самостоятелна или групова работа.

---

### Въпрос 1

Каква е функционалната разлика между следните два кода?

```cpp
// Код X
std::vector<int> data(1000000, 1);
for (int val : data) {
    // използваме val
}

// Код Y
std::vector<int> data(1000000, 1);
for (const int& val : data) {
    // използваме val
}
```

- a. Няма разлика
- b. Код X е по-ефективен
- c. Код X прави копия на всеки елемент
- d. Код Y няма да се компилира

---

### Въпрос 2

Какви типове ще има `param` в тези два случая?

```cpp
template<typename T>
void process(T&& param) {
    // ?
}

int a = 7;
process(a);      // случай A
process(8);      // случай B
```

- a. A: int&&, B: int&&
- b. A: int&, B: int&&
- c. A: int&, B: int&
- d. A: int, B: int

---

### Въпрос 3

Кой от следните изрази е допустим?

```cpp
struct Block { float values[10]; };
Block x, y;
float table[10];
float matrix[10][10];
```

- a. `x.values = table;`
- b. `x = y;`
- c. `matrix = table;`
- d. `table = matrix;`
- e. `x == y;`

---

### Въпрос 4

Какво ще се случи при следния код?

```cpp
class Holder {
    int* ptr;
public:
    Holder(int* p) : ptr(p) {}
    ~Holder() { delete ptr; }
};

int main() {
    Holder a(new int(10));
    Holder b = a;
}
```

- a. Всичко ще работи нормално
- b. Програмата ще завърши с double delete
- c. Няма да се компилира
- d. Ще има memory leak

---

### Въпрос 5

Попълнете липсващите части, така че да няма memory leak и всичко работи:

```cpp
char* makeBuffer(int size) {
    <A>
    return buf;
}

int main() {
    char* data = makeBuffer(5);
    std::cout << data[0];
    <B>
}
```

- a. `<A>`: `char* buf = new char[size];` `<B>`: `delete data;`
- b. `<A>`: `char* buf = new char[size];` `<B>`: `delete[] data;`
- c. `<A>`: `char buf[size];` `<B>`: `delete[] data;`
- d. `<A>`: `char* buf = malloc(size);` `<B>`: `free(data);`

---

### Въпрос 6

Какво трябва да притежава класът `Collection`, за да може да се използва в range-based for?

```cpp
Collection c;
for (auto e : c) { ... }
```

- a. Оператор `[]`
- b. Методи `begin()` и `end()`
- c. `begin()` и `end()` трябва да връщат обекти с `++`, `!=` и `*`
- d. Класът трябва да наследява `std::iterator`
- e. Колекцията трябва да е STL контейнер

---

### Въпрос 7

Какъв е изходът?

```cpp
struct Box { int x, y; };
void doubleSize(Box b) { b.x *= 2; b.y *= 2; }

int main() {
    Box b = {4, 5};
    doubleSize(b);
    std::cout << b.x << "," << b.y;
}
```

- a. 8,10
- b. 4,5
- c. Компилационна грешка
- d. 0,0

---

### Въпрос 8

Попълнете липсващия параметър:

```cpp
template <typename T>
T minElement(T arr[], <P> cmp, int size) {
    int idx = 0;
    for (int i = 1; i < size; ++i) {
        if (cmp(arr[i], arr[idx])) idx = i;
    }
    return arr[idx];
}
```

- a. `bool(*)(T,T)`
- b. `T(*)(T,T)`
- c. `std::function<T(T,T)>`
- d. `std::function<bool(T,T)>`

---

### Въпрос 9

Клас може ли да дефинира няколко форми на оператор `*=`?

- a. Да
- b. Не

---

### Въпрос 10

Кои от тези класове изискват custom copy конструктор?

- a. `class File { std::ifstream* f; };`
- b. `class Buffer { std::vector<int> values; };`
- c. `class A { int data[10]; };`
- d. `class Data { char* str; };`
- e. `class X { std::string* name; };`

---

### Въпрос 11

Какъв ще е изходът?

```cpp
void changeA(char* p) { p[0] = 'X'; }
void changeB(char a[]) { a[0] = 'Y'; }
void changeC(char c) { c = 'Z'; }

int main() {
    char x = 'a', y = 'b', z = 'c';
    changeA(&x);
    changeB(&y);
    changeC(z);
    std::cout << x << y << z;
}
```

- a. XYZ
- b. XYC
- c. aYZ
- d. XYc

---

### Въпрос 12

Валидна ли е тази декларация?

```cpp
class User {
    User(User u);
};
```

- a. Да
- b. Не

---

### Въпрос 13

Ако функция A вика B, а B вика C, и C хвърли изключение, какво се случва?

- a. Ако никъде няма try-catch, програмата се прекратява
- b. Ако A има try-catch, всички стекови обекти от A, B и C ще се деструктурират
- c. Изключението се хваща в B
- d. Всички обекти от C ще се загубят

---

### Въпрос 14

Какъв е проблемът тук, ако има такъв?

```cpp
class Multiplier {
    double operator()(int x, int y) {
        return x * y;
    }
};
```

- a. Няма
- b. `operator()` трябва да е public
- c. `operator()` трябва да връща int
- d. Не може да се предефинира

---

### Въпрос 15

Какво се отпечатва?

```cpp
class Shape {
public:
    virtual void draw() { std::cout << "Shape"; }
};

class Circle : public Shape {
public:
    void draw() override { std::cout << "Circle"; }
};

int main() {
    Shape* s = new Circle();
    s->draw();
    delete s;
}
```

- a. Shape
- b. Circle
- c. Компилационна грешка

---

### Въпрос 16

Какво ще се случи?

```cpp
std::string* make() {
    std::string arr[3] = {"A", "B", "C"};
    return arr;
}
```

- a. Компилационна грешка
- b. arr е валиден след връщане
- c. Поведението е недефинирано
- d. arr ще бъде изтрито автоматично

---

### Въпрос 17

Кой от тези начини е най-ефективен?

```cpp
// A
std::vector<int> get() {
    std::vector<int> v = {1,2,3};
    return v;
}

// B
std::vector<int> get() {
    return {1,2,3};
}

// C
const std::vector<int>& get() {
    static std::vector<int> v = {1,2,3};
    return v;
}
```

- a. A
- b. B
- c. C

---

### Въпрос 18

Кои извиквания са валидни?

```cpp
class Num { public: Num(int); };
void process(Num n);
void calc(int x);
```

- a. process(1);
- b. process(1.5);
- c. calc(Num(3));

---

### Въпрос 19

Как да реализираме `Matrix result = 2 * mat;`?

- a. Външен `Matrix operator*(const Matrix&, int)`
- b. Метод `Matrix operator*(int)`
- c. Външен `Matrix operator*(int, const Matrix&)`
- d. Вътрешен `Matrix operator*(int)`

---

### Въпрос 20

Коя декларация е коректна?

```cpp
double modify(double* arr, int i); // искаме modify(arr, 3) = 1.0;
```

- a. double modify(...)
- b. double& modify(...)
- c. void modify(...)
- d. double\* modify(...)

---

### Въпрос 21

Кое от изброените НЕ е валидно име на променлива в C++?

- a. my_var
- b. \_temp
- c. var123
- d. 123var

---

### Въпрос 22

Какъв ще бъде изходът от следната програма?

```cpp
int x = 5;
int y = x++;
std::cout << y;
```

- a. 4
- b. 5
- c. 6
- d. Грешка при компилация

---

### Въпрос 23

Каква е разликата между `==` и `=` в C++?

_(отворен въпрос)_

---

### Въпрос 24

Какво ще се отпечата при изпълнението на следния код?

```cpp
int a = 10;
int b = 3;
std::cout << a % b;
```

- a. 0
- b. -1
- c. 1
- d. 3

---

### Въпрос 25

Кой от изброените типове е подходящ за съхранение на число с плаваща запетая?

- a. char
- b. double
- c. int
- d. bool

---

### Въпрос 26

Какъв е резултатът от следния израз?

```cpp
true && false || true
```

- a. false
- b. true
- c. Грешка при компилация
- d. Зависи от компилатора

---

### Въпрос 27

Какво ще се случи при изпълнението на следния код?

```cpp
int a = 5;
int b = 0;
std::cout << a / b;
```

- a. Ще се отпечата 0
- b. Ще се отпечата нещо произволно
- c. Ще доведе до недефинирано поведение, което обикновено завършва със срив на програмата.
- d. Ще се отпечата "Грешка"

---

### Въпрос 28

Какво е итератор в C++? Каква е неговата роля в контекста на STL? Дайте нетривиален пример за използване на итератор (различен от `std::vector`, `std::list`).

_(отворен въпрос)_

---

### Въпрос 29

Кой от следните оператори има най-висок приоритет в C++?

- a. +
- b. ==
- c. \*
- d. &&

---

### Въпрос 30

Каква е стойността на променливата `result`?

```cpp
int x = 4;
int y = 2;
int result = x > y ? x : y;
```

- a. 4
- b. 2
- c. true
- d. false

---

### Въпрос 31

Кое от следните е вярно за указатели (pointers) в C++?

- a. Те съдържат адрес на променлива
- b. Те могат да съдържат само цели числа
- c. Указателите са само за четене
- d. Те не могат да сочат към масив

---

### Въпрос 32

Какъв ще бъде резултатът?

```cpp
int a = 5;
int b = 3;
std::cout << (a > b) << " " << (a < b);
```

- a. 1 0
- b. 0 1
- c. true false
- d. Грешка при компилация

---

### Въпрос 33

Какво се случва, ако опитаме да достъпим елемент извън границите на масив? Опишете адресната ариметика при използване на [] - как работи и какво се случва при опит за достъп до невалиден индекс.

_(отворен въпрос)_

---

### Въпрос 34

Какво означава `const` при деклариране на променлива?

- a. Че не може да бъде променяна
- b. Че е глобална
- c. Че се инициализира по-късно
- d. Че се намира в стековата памет

---

### Въпрос 35

Кой от операторите се използва за достъп до член на структура чрез указател?

- a. .
- b. ->
- c. \*
- d. &

---

### Въпрос 36

За какво служи `break` в цикъл? Опишете как работи и дайте пример за използване на `break` в цикъл.

_(отворен въпрос)_

---

### Въпрос 37

Какво ще отпечата този код?

```cpp
for (int i = 0; i < 3; i++) {
    std::cout << i << " ";
}
```

- a. 0 1 2
- b. 1 2 3
- c. 0 1 2 3
- d. Грешка

---

### Въпрос 38

Какво е полиморфизъм в C++? Дайте пример за полиморфизъм и обяснете как работи. Защо избрахте този пример?

_(отворен въпрос)_

---

### Въпрос 39

Какво ще бъде отпечатано?

```cpp
int arr[3] = {1, 2, 3};
std::cout << *(arr + 1);
```

- a. 1
- b. 2
- c. Грешка
- d. Адрес на елемент

---

### Въпрос 40

Каква е разликата между `while` и `do-while` цикъл?

_(отворен въпрос)_
