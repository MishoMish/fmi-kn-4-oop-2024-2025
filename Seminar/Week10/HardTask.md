# Трудна задача – Контролен стил

## Задача: Център за съобщения

Създайте йерархия от класове, представящи различни типове съобщения:

- `Message` (базов клас)
- `TextMessage` – съдържа текст
- `ImageMessage` – съдържа име на файл
- `ReactionMessage` – съдържа емоджи и ID на съобщението, към което е реакция

Създайте фабричен клас `MessageFactory`, който по текстова команда създава подходящия обект:

```cpp
Message* createMessage(const std::string& type, const std::vector<std::string>& args);
```

Примери за вход:

```
text Hello, world!
image cat.png
reaction 👍 3
```

## Изисквания

- Използвайте `std::vector<Message*>` за съхранение
- Всеки клас трябва да има метод `print()` (виртуален), който извежда съдържанието на съобщението
- `ReactionMessage` използва индекс/ID на съобщение (няма нужда да сочи към него реално)

## Примерен изход

```
[Text] Hello, world!
[Image] cat.png
[Reaction] 👍 to 3
```

## Допълнителна задача (ако остане време)

Добавете възможност да се зареждат съобщения от текстов файл чрез фабриката.

> Бележка: Паметта не се изчиства нарочно. Не се изисква използване на smart pointers, макар че е добра практика.

```cpp

#include <iostream>
#include <vector>
#include <string>

// Абстрактен базов клас Message
class Message
{
public:
    virtual void print() const = 0;
    virtual Message *clone() const = 0;
    virtual ~Message() {}
};

// Текстово съобщение
class TextMessage : public Message
{
private:
    std::string content;

public:
    TextMessage(const std::string &content) : content(content) {}
    void print() const override
    {
        std::cout << "[Text] " << content << std::endl;
    }
    Message *clone() const override
    {
        return new TextMessage(*this);
    }
};

// Снимково съобщение
class ImageMessage : public Message
{
private:
    std::string filename;

public:
    ImageMessage(const std::string &filename) : filename(filename) {}
    void print() const override
    {
        std::cout << "[Image] " << filename << std::endl;
    }
    Message *clone() const override
    {
        return new ImageMessage(*this);
    }
};

// Реакционно съобщение
class ReactionMessage : public Message
{
private:
    std::string emoji;
    int targetId;

public:
    ReactionMessage(const std::string &emoji, int targetId)
        : emoji(emoji), targetId(targetId) {}
    void print() const override
    {
        std::cout << "[Reaction] " << emoji << " to " << targetId << std::endl;
    }
    Message *clone() const override
    {
        return new ReactionMessage(*this);
    }
};

// Фабрика за съобщения
class MessageFactory
{
public:
    static Message *createMessage(const std::string &type, const std::vector<std::string> &args)
    {
        // Добави случаи
        return nullptr;
    }
};

// Стратегия за принтиране
class PrintStrategy
{
public:
    virtual void print(const Message &msg) const = 0;
    virtual ~PrintStrategy() {}
};

// Принтиране по подразбиране
class DefaultPrintStrategy : public PrintStrategy
{
public:
    void print(const Message &msg) const override
    {
        msg.print();
    }
};

// Принтиране в JSON формат
class JsonPrintStrategy : public PrintStrategy
{
public:
    void print(const Message &msg) const override
    {
        // Може да добавите JSON формат тук
        std::cout << "{ " message ": ";
        msg.print();
        std::cout << " }" << std::endl;
    }
};

int main()
{
    std::vector<Message *> messages;

    // Пример за използване на фабрика
    messages.push_back(MessageFactory::createMessage("text", {"Hello, world!"}));
    messages.push_back(MessageFactory::createMessage("image", {"cat.jpg"}));
    messages.push_back(MessageFactory::createMessage("reaction", {"👍", "2"}));

    // Принтиране с различни стратегии
    DefaultPrintStrategy defaultStrategy;
    JsonPrintStrategy jsonStrategy;

    for (const auto &msg : messages)
    {
        defaultStrategy.print(*msg);
    }

    std::cout << "
        JSON Output : ";
                      for (const auto &msg : messages)
    {
        jsonStrategy.print(*msg);
    }

    // Изчистване на паметта
    for (auto &msg : messages)
    {
        delete msg;
    }

    return 0;
}
```
