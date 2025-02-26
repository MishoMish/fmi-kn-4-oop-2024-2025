#include <iostream>

// 1. Шаблонна функция за намиране на минимална стойност
template <typename T>
T minValue(T a, T b) {
    return (a < b) ? a : b;
}

// 2. Използване на указател към функция
int applyOperation(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int add(int a, int b) {
    return a + b;
}

// 3. Lambda функция върху масив
void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] += i;
    }
}

int main() {
    std::cout << minValue(3, 7) << std::endl; // 3
    std::cout << minValue(5.2, 2.8) << std::endl; // 2.8

    std::cout << applyOperation(10, 20, add) << std::endl; // 30

    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    auto lambda = [](int arr[], int size) {
        for (int i = 0; i < size; ++i) {
            arr[i] += i;
        }
    };
    lambda(array, size);

    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
