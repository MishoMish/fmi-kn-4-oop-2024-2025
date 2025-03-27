# Задачи за демонстрация

## Задача 1: Запис и четене на числа в текстов файл

**Описание:**
Напишете програма, която записва 10 цели числа в текстов файл и след това ги прочита обратно.

**Решение:**

```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ofstream outFile("numbers.txt");
    if (!outFile) {
        std::cerr << "Грешка при отваряне на файла за запис!" << std::endl;
        return 1;
    }
    for (int i = 1; i <= 10; i++) {
        outFile << i << " ";
    }
    outFile.close();

    std::ifstream inFile("numbers.txt");
    if (!inFile) {
        std::cerr << "Грешка при отваряне на файла за четене!" << std::endl;
        return 1;
    }
    int num;
    while (inFile >> num) {
        std::cout << num << " ";
    }
    inFile.close();
}
```

---

## Задача 2: Запис и четене на структура в двоичен файл

**Описание:**
Създайте програма, която записва структура `Student` в двоичен файл и след това я прочита обратно.

**Решение:**

```cpp
#include <iostream>
#include <fstream>

struct Student {
    char name[20];
    int age;
    int fn;
};

int main() {
    Student s = {"Иван", 20, 12345};
    std::ofstream outFile("student.dat", std::ios::binary);
    if (!outFile) {
        std::cerr << "Грешка при запис!" << std::endl;
        return 1;
    }
    outFile.write(reinterpret_cast<const char*>(&s), sizeof(s));
    outFile.close();

    Student readS;
    std::ifstream inFile("student.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Грешка при четене!" << std::endl;
        return 1;
    }
    inFile.read(reinterpret_cast<char*>(&readS), sizeof(readS));
    inFile.close();

    std::cout << "Име: " << readS.name << ", Възраст: " << readS.age << ", ФН: " << readS.fn << std::endl;
}
```
