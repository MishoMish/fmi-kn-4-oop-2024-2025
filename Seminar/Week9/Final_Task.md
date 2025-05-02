# Сложна задача: Йерархия от служители във фирма

## Условие

Създайте програма за управление на йерархия от служители в една фирма.

Имаме следните роли:
- `Employee` (базов абстрактен клас) – всеки служител има име, ID и метод `getSalary()`.
- `Developer` – има основна заплата и брои проекти, които увеличават заплатата му с фиксирана надбавка.
- `Manager` – има основна заплата и екип от служители, чиято обща ефективност увеличава заплатата.
- `Intern` – има фиксирана стипендия и няма други параметри.

Програмата трябва да:
1. Използва **виртуални функции**.
2. Използва **поне една чисто виртуална функция**.
3. Поддържа **списък от служители** чрез указатели към `Employee`.
4. Извежда информация за заплатата на всеки служител чрез полиморфизъм.

## Примерен интерфейс
```cpp
class Employee {
protected:
    std::string name;
    int id;
public:
    Employee(std::string name, int id);
    virtual double getSalary() const = 0;
    virtual void printInfo() const;
    virtual ~Employee();
};

class Developer : public Employee {
    double baseSalary;
    int projects;
public:
    Developer(std::string name, int id, double salary, int projects);
    double getSalary() const override;
    void printInfo() const override;
};

class Manager : public Employee {
    double baseSalary;
    std::vector<Employee*> team;
public:
    Manager(std::string name, int id, double salary);
    void addToTeam(Employee* e);
    double getSalary() const override;
    void printInfo() const override;
};

class Intern : public Employee {
    double stipend;
public:
    Intern(std::string name, int id, double stipend);
    double getSalary() const override;
    void printInfo() const override;
};
```

## Изисквания

- Имплементирайте всички класове и нужните методи.
- Използвайте `std::vector<Employee*>` за съхранение на служители.
- Напишете демонстрационна функция `main`, в която:
  - Създавате различни служители.
  - Мениджър добавя други служители към своя екип.
  - Извеждате информация за всички служители с `printInfo()`.

## Подсказка

Използвайте полиморфизъм, за да извикате `getSalary()` и `printInfo()` върху указатели от тип `Employee*`.

## Допълнително

Ако искате да усложните задачата, добавете виртуален метод `evaluatePerformance()`, който връща число от 0 до 1.0 и влияе на заплатата.