**# Решения на задачите от теорията: Итератори в C++**

## **Решение на Пример 1: Итератор за масив**

```cpp
#include <iostream>

class ArrayIterator {
private:
    int* ptr;
public:
    ArrayIterator(int* p) : ptr(p) {}
    int& operator*() { return *ptr; }
    ArrayIterator& operator++() { ++ptr; return *this; }
    ArrayIterator& operator--() { --ptr; return *this; }
    bool operator!=(const ArrayIterator& other) { return ptr != other.ptr; }
};

class IntArray {
private:
    int* data;
    size_t size;
public:
    IntArray(int arr[], size_t s) : data(arr), size(s) {}
    ArrayIterator begin() { return ArrayIterator(data); }
    ArrayIterator end() { return ArrayIterator(data + size); }
};

int main() {
    int values[] = {10, 20, 30, 40};
    IntArray arr(values, 4);

    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

**Изход:**

```
10 20 30 40
```

## **Решение на Пример 2: Двупосочен итератор**

```cpp
#include <iostream>

class ArrayIterator {
private:
    int* ptr;
public:
    ArrayIterator(int* p) : ptr(p) {}
    int& operator*() { return *ptr; }
    ArrayIterator& operator++() { ++ptr; return *this; }
    ArrayIterator& operator--() { --ptr; return *this; }
    bool operator!=(const ArrayIterator& other) { return ptr != other.ptr; }
};

int main() {
    int values[] = {1, 2, 3, 4};
    ArrayIterator it(values);
    ArrayIterator end(values + 4);

    while (it != end) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    while (it != ArrayIterator(values)) {
        --it;
        std::cout << *it << " ";
    }
    return 0;
}
```

**Изход:**

```
1 2 3 4
4 3 2 1
```
