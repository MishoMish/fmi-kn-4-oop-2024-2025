# Работа с файлове

## 1. Видове файлове според типа данни

### Текстови файлове

Файлове, в които съдържанието е предназначено за четене от хора. Данните във файла са представени като последователност от символи.

### Двоични файлове

Файлове, чието съдържание представлява точно копие на данните в паметта, записани в бинарен формат.

## 2. Видове операции с файлове

- Четене
- Писане
- Четене и писане

## 3. Поток

Потокът е абстракция, която описва връзката между програмата и даден файл или устройство.

### Видове потоци

- `std::ifstream` – входен поток за четене от файл
- `std::ofstream` – изходен поток за запис във файл
- `std::fstream` – двупосочен поток за четене и запис

### Основни методи

- `open("име_на_файл")` – отваря файл
- `close()` – затваря файл

### Флагове на потока

- `good()` – последната операция е успешна
- `fail()` – грешен формат на данните
- `eof()` – достигнат е краят на файла
- `clear()` – изчистване на грешките

## 4. Четене и писане в текстови файлове

### Пример за четене

```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }
    int a, b;
    file >> a >> b;
    std::cout << a << " " << b << std::endl;
    file.close();
}
```

### Пример за писане

```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("output.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }
    int a = 3, b = 10;
    file << a << " " << b << " " << a + b << std::endl;
    file.close();
}
```

## 5. Четене и писане в двоични файлове

### Записване на структура

```cpp
#include <iostream>
#include <fstream>

struct Test {
    bool b;
    int x;
};

int main() {
    Test t = { true, 45 };
    std::ofstream file("test.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }
    file.write(reinterpret_cast<const char*>(&t), sizeof(t));
    file.close();
}
```

### Четене на структура

```cpp
#include <iostream>
#include <fstream>

struct Test {
    bool b;
    int x;
};

int main() {
    Test t;
    std::ifstream file("test.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }
    file.read(reinterpret_cast<char*>(&t), sizeof(t));
    std::cout << std::boolalpha << t.b << " " << t.x << std::endl;
    file.close();
}
```

## 6. Записване и четене на масив от структури

### Структура

```cpp
struct Student {
    char name[24];
    int age;
    int fn;
};
```

### Записване на масив от структури

```cpp
void SaveToFile(const Student* students, size_t count, std::ofstream &file) {
    file.write(reinterpret_cast<const char*>(&count), sizeof(size_t));
    file.write(reinterpret_cast<const char*>(students), count * sizeof(Student));
}
```

### Четене на масив от структури

```cpp
std::unique_ptr<Student[]> ReadFromFile(size_t &count, std::ifstream &file) {
    file.read(reinterpret_cast<char*>(&count), sizeof(size_t));
    auto students = std::make_unique<Student[]>(count);
    file.read(reinterpret_cast<char*>(students.get()), count * sizeof(Student));
    return students;
}
```
