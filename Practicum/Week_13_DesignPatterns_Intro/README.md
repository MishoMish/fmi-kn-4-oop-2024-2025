# Шаблони за дизайн

## Шаблони за създаване

### Factory
Вече сме разглеждали няколко пъти. Чрез него създаваме обекти от някаква йерархия и ни помага да работим с хетерогенни контейнери.

### Singleton
***Цел:*** Гарантиране на наличие на точно една инстанция по време на изпълнение на програмата. По този начин е налице централизиран достъп до ресурси.

```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton()
    {
        std::cout << "Successful creation\n";
    }

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

    static Singleton* getInstance()
    {
        if (instance == nullptr)
            instance = new Singletion();
        
        return instance;
    }

    void func() const
    {
        // do something
    }
};

Singleton* Singleton::instance = nullptr;
```

*Задача.* Да се реализира клас, който представлява система за log-вания на съобщения. Погрижете се да има единствена инстанция на класа в програмата. Да се реализира метод, който по подаден поток и съобщение, принтира съобщението в потока.

## Шаблони за поведение

### Visitor
***Цел:*** Разграничаване на обектите от операциите, които могат да им се прилагат.

```cpp
class Visitor
{
public:
    virtual void visit(A* a) = 0;
    virtual void visit(B* b) = 0;
};

class Visitable
{
public:
    virtual void accept(Visitor* vis) = 0;
    /*
    често реализацията на този метод е просто:
    void accept(Visitor* vis)
    {
        vis->visit(this);
    }
    */
}
```

*Задача.* Да се напише програма, която моделира файлова система, съставена от файлове и папки. Всеки файл има име и размер, а папките - име и списък със съдържанието им. Да се реализират и два посетителя:
- GetSizeVisitor - изчислява общия размер на подадено място във файловата система(размер на папка е сумарният размер на съдържанието й);
- PrintVisitor - йерархично принтира цялата структура на файловата система.

## Шаблони за структуриране

### Proxy

### Adapter