# Изключения (Exceptions) в C++

## 1. Необходимост от изключения

### 1.1. Проблеми при обработката на грешки

Традиционните методи за обработка на грешки в програмирането имат редица недостатъци:

#### Връщане на код за грешка

```cpp
int findRecordIndex(const std::string& name)
{
    // Търсене на запис...
    if (recordFound)
        return recordIndex;
    else
        return -1; // Код за грешка
}
```

**Недостатъци:**

- Кодовете за грешки трябва да се документират
- Кодовете за грешки лесно се игнорират от програмистите
- Функциите могат да връщат само един тип стойност
- Неудобно за използване с конструктори (които не могат да връщат стойност)

#### Използване на глобални променливи за грешки

```cpp
bool processFile(const std::string& filename)
{
    // Опит за обработка на файл...
    if (errorOccurred)
    {
        g_errorCode = ERROR_FILE_NOT_FOUND;
        return false;
    }
    return true;
}
```

**Недостатъци:**

- Глобалните променливи нарушават енкапсулацията
- Трудно се проследява произходът на грешката
- Възможни са състезателни условия при многонишково програмиране

### 1.2. Предимства на изключенията

- **Разделение на нормален код и код за обработка на грешки**
- **Невъзможно е да се игнорират** - програмата ще прекъсне, ако изключението не се хване
- **Детайлна информация** за грешката посредством обекти с изключения
- **Прекратяване на изпълнението** и връщане назад по стека на извикванията до подходящ обработчик
- **Автоматично освобождаване на ресурси** чрез RAII принципа

## 2. Основи на изключенията в C++

### 2.1. Синтаксис и използване

#### Хвърляне на изключение (throw)

```cpp
void validateAge(int age)
{
    if (age < 0)
        throw std::invalid_argument("Възрастта не може да бъде отрицателна");

    if (age > 150)
        throw std::out_of_range("Възрастта е прекалено голяма");
}
```

#### Улавяне на изключение (try-catch)

```cpp
try
{
    validateAge(-5);
}
catch (const std::invalid_argument& e)
{
    std::cerr << "Грешка: " << e.what() << std::endl;
}
catch (const std::out_of_range& e)
{
    std::cerr << "Грешка при обхват: " << e.what() << std::endl;
}
catch (...)  // Улавя всички останали изключения
{
    std::cerr << "Неизвестна грешка!" << std::endl;
}
```

### 2.2. Стандартна йерархия на изключенията в C++

В C++ стандартната библиотека предоставя йерархия от класове за изключения:

```
std::exception
  ├── std::bad_alloc
  ├── std::bad_cast
  ├── std::bad_typeid
  ├── std::bad_exception
  ├── std::logic_error
  │     ├── std::domain_error
  │     ├── std::invalid_argument
  │     ├── std::length_error
  │     ├── std::out_of_range
  │     └── std::future_error
  └── std::runtime_error
        ├── std::overflow_error
        ├── std::underflow_error
        ├── std::range_error
        └── std::system_error
```

Основните категории са:

- **logic_error**: Грешки, които могат да бъдат открити преди изпълнение на програмата
- **runtime_error**: Грешки, които могат да бъдат открити само по време на изпълнение

## 3. Създаване на собствени класове за изключения

### 3.1. Наследяване от std::exception

Добра практика е да се наследява от базовия клас `std::exception` или някой от неговите наследници:

```cpp
class FileOpenError : public std::runtime_error
{
private:
    std::string m_filename;

public:
    FileOpenError(const std::string& filename)
        : std::runtime_error("Не може да се отвори файл: " + filename),
          m_filename(filename)
    {
    }

    const std::string& getFilename() const
    {
        return m_filename;
    }
};
```

### 3.2. Използване на собствен клас за изключения

```cpp
void openFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw FileOpenError(filename);

    // Работа с файла...
}

try
{
    openFile("nonexistent.txt");
}
catch (const FileOpenError& e)
{
    std::cerr << e.what() << std::endl;
    std::cerr << "Име на файл: " << e.getFilename() << std::endl;
}
```

## 4. Добри практики при работа с изключения

### 4.1. Кога да използваме изключения

- За **необичайни ситуации**, които не са част от нормалния поток на програмата
- За **грешки, които не могат да бъдат обработени локално**
- Когато **функцията не може да изпълни своя договор** (не може да се справи със задачата си)

### 4.2. Кога НЕ трябва да използваме изключения

- За **нормален поток на програмата** (например, край на файл)
- За **предвидими грешки**, които могат да се обработят с връщане на стойност
- В **деструктори** (деструкторите не трябва да хвърлят изключения)
- В **критични по производителност секции** на кода

### 4.3. RAII (Resource Acquisition Is Initialization)

RAII е принцип, според който ресурсите се обвързват със живота на обекта:

```cpp
class FileHandler
{
private:
    std::fstream m_file;

public:
    FileHandler(const std::string& filename)
    {
        m_file.open(filename);
        if (!m_file.is_open())
            throw FileOpenError(filename);
    }

    ~FileHandler()
    {
        if (m_file.is_open())
            m_file.close();
    }

    // Методи за работа с файла...
};

void processFile(const std::string& filename)
{
    try
    {
        FileHandler file(filename);
        // Работа с файла...
    }
    catch (const FileOpenError& e)
    {
        // Обработка на грешката...
    }
    // Файлът автоматично ще се затвори, когато file излезе от обхвата
}
```

### 4.4. Преобработване на изключения (Exception re-throwing)

Понякога е полезно да хванем изключение, да извършим някакви действия и след това да го хвърлим отново:

```cpp
void function()
{
    try
    {
        // Код, който може да хвърли изключение
    }
    catch (const std::exception& e)
    {
        // Извършваме някакви действия
        std::cerr << "Хванато изключение: " << e.what() << std::endl;

        // Хвърляме изключението отново
        throw;
    }
}
```

### 4.5. Спецификация на изключенията (noexcept)

Можем да обявим функция, която гарантирано няма да хвърля изключения:

```cpp
void safeFunction() noexcept
{
    // Този код не трябва да хвърля изключения
}
```

Или функция, която хвърля изключения при определено условие:

```cpp
void conditionallyThrowingFunction() noexcept(sizeof(int) > 4)
{
    // Хвърля изключения само ако условието е false
}
```

## 5. Улавяне на съществуващи изключения

### 5.1. Стандартни изключения в C++

#### Улавяне на std::bad_alloc (проблем с памет)

```cpp
try
{
    int* array = new int[1000000000000]; // Опит за заделяне на твърде много памет
}
catch (const std::bad_alloc& e)
{
    std::cerr << "Грешка при заделяне на памет: " << e.what() << std::endl;
}
```

#### Улавяне на std::out_of_range (извън обхват)

```cpp
try
{
    std::vector<int> vec = {1, 2, 3};
    std::cout << vec.at(5); // Индекс извън обхвата
}
catch (const std::out_of_range& e)
{
    std::cerr << "Индекс извън обхвата: " << e.what() << std::endl;
}
```

### 5.2. Изключения от стандартната библиотека

#### Изключения при работа с файлове

```cpp
try
{
    std::ifstream file("nonexistent.txt");
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open("nonexistent.txt");
}
catch (const std::ios_base::failure& e)
{
    std::cerr << "Грешка при I/O операция: " << e.what() << std::endl;
}
```

#### Изключения при преобразуване на низове

```cpp
try
{
    std::string str = "not a number";
    int value = std::stoi(str);
}
catch (const std::invalid_argument& e)
{
    std::cerr << "Невалиден аргумент: " << e.what() << std::endl;
}
catch (const std::out_of_range& e)
{
    std::cerr << "Стойност извън обхвата: " << e.what() << std::endl;
}
```

## 6. Разширени техники

### 6.1. Създаване на йерархия от изключения

```cpp
class DatabaseError : public std::runtime_error
{
public:
    DatabaseError(const std::string& message)
        : std::runtime_error("Грешка в базата данни: " + message)
    {
    }
};

class ConnectionError : public DatabaseError
{
public:
    ConnectionError(const std::string& server)
        : DatabaseError("Неуспешно свързване със сървър: " + server)
    {
    }
};

class QueryError : public DatabaseError
{
private:
    std::string m_query;

public:
    QueryError(const std::string& query, const std::string& reason)
        : DatabaseError("Грешка в заявката: " + reason),
          m_query(query)
    {
    }

    const std::string& getQuery() const
    {
        return m_query;
    }
};
```

### 6.2. Употреба на множество блокове catch

```cpp
try
{
    // Код, който може да хвърли различни видове изключения
}
catch (const ConnectionError& e)
{
    std::cerr << "Грешка при свързване: " << e.what() << std::endl;
    // Опит за повторно свързване
}
catch (const QueryError& e)
{
    std::cerr << "Грешка в заявката: " << e.what() << std::endl;
    std::cerr << "Проблемна заявка: " << e.getQuery() << std::endl;
    // Корекция на заявката
}
catch (const DatabaseError& e)
{
    std::cerr << "Обща грешка в базата данни: " << e.what() << std::endl;
    // Обща обработка
}
catch (const std::exception& e)
{
    std::cerr << "Стандартно изключение: " << e.what() << std::endl;
}
catch (...)
{
    std::cerr << "Неизвестно изключение!" << std::endl;
}
```

Важно е да се подредят блоковете catch от най-специфичния към най-общия тип изключение.

## 7. Заключение

Изключенията са мощен механизъм за обработка на грешки в C++, който позволява:

1. Разделяне на нормалния код от кода за обработка на грешки
2. Предаване на богата информация за грешката чрез обекти
3. Гарантиране, че грешките не се игнорират
4. Автоматично почистване на ресурси чрез RAII принципа

Въпреки това, изключенията трябва да се използват внимателно и само за наистина необичайни ситуации, които не са част от нормалния поток на програмата.
