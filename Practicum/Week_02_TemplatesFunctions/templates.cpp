#include <iostream>

using namespace std;

template <typename T>
void Swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}

void Swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}


void Swap(double& a, double& b){
    double temp = a;
    a = b;
    b = temp;
}



template <typename T>
T add(T a, T b) {
    return a + b;
}

// implicit vs explicit (пвно и неявно използване на шаблони)
// int main(){
//     int a = 3;
//     int b = 5;
//     swap<int>(a,b);
//     // swap(a,b);
//     cout<<"a = "<<a<<endl; 
//     cout<<"b = "<<b<<endl; 
// }


// специализирани шаблони 


template <typename T, typename U>
T add(T a, U b) {
    cout<<"first adder"<<endl;
    return a + b;
}

template <typename T>
T add(T a, int b) {
    cout<<"second adder"<<endl;
    return a + b;
}

template <>
char add(char a, int b) {
    b%=(255 - a);
    cout<<"third adder"<<endl;
    return a + b;
}

// int main(){
//     int a = 3;
//     double b = 15.0;
//     char c = 'a';
//     cout<<add(b,a)<<endl;
//     cout<<add(a,b)<<endl;
//     cout<<add(c,a)<<endl;

// }


//шаблони в структури

template <typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;

    void display() const {
        std::cout << "First: " << first << ",\nSecond: " << second << std::endl;
    }
};

// int main() {
//     char buffer[20] = "Hello world";
//     Pair<int, double> p1{10, 3.14};
//     Pair<char*, char> p2{buffer, 'A'};
//     p1.display(); 
//     p2.display(); 
// }

template<int N>
struct Factoriel{
    static const int value = N * Factoriel<N-1>::value;
};

template<>
struct Factoriel<0>{
    static const int value=1;
};  

// int main(){
//     const int x = 5;
//     cout<<Factoriel<x>::value<<endl;
// }



//-----------------------------------------------------------------------------------

//фунцкии от по-висок ред

//Указател към функция:
//Синтаксис:          

//  [return type] (*[function name])([argument types]);

// int (*func)(int,int) - тип !!!!!
//не пишем []

//---------------------------------------------------------------

//пример: 
//функция приемаща функция

void Times2(int& a){a*=2;}
void Times3(int& a){a*=3;}

// template<typename T>
// void map(T* arr, size_t size, void (*func)(T&) ){
//     for(int i = 0; i< size; i++)
//         func(arr[i]);
// }
    
// int main(){
//     int arr[5]{1,2,3,4,5};
//     map<int>(arr,5, Times3);
//     for(int i = 0;i<5;i++)
//     cout<<arr[i]<<' ';
// }

//std::function
//синтаксис:          

//  std::function<[return type]([argument types])> [function name]

// std::function<void(int&)> func = Times2;
//не пишем []

//------------------------------------------------------

//lambda 
//синтаксис:          

//  [<capture list>](<arguments>){<body>}

//не пишем <>

#include <functional>

template<typename T>
void map(T* arr,size_t size, function<void(int&)> func){
    for(int i = 0; i< size; i++)
        func(arr[i]);
}

// int main(){
//     int arr[5]{1,2,3,4,5};
//     map<int>(arr,5, [](int& a){a*=2;});
    
//     for(int i = 0;i<5;i++)
//         cout<<arr[i]<<' ';
// }


//------------------------------------------------------------------

//връщане на указател към функция

using Operator =int (*)(int,int);
// typedef int (*Operator)(int,int);

int Add(int a, int b){
    return a + b;
}
int Subtract(int a, int b){
    return a - b;
}
int ZeroFunction(int a, int b){
    return 0;
}

Operator getOperator(char op){
    switch(op){
        case '+': return Add;break;
        case '-': return Subtract;break;
        default: cout<<"Unknown operator";return ZeroFunction;break;
    }
}

// Operator getOperator(char op){
    //     switch(op){
        //         case '+': return [](int a, int b){return a+b;};break;
        //         case '-': return [](int a, int b){return a-b;};break;
        //         default: cout<<"Unknown operator";return [](int,int){return 0;};break;//lambda функция
//     }
// }

using multiplier =std::function<int(int)>;
multiplier getMultiplier(int a){
    return [a](int b){return a*b;};
}

int main(){
    int a = 10;
    int b = 14;
    char op = '+';
    multiplier times3 = getMultiplier(3);
    cout<<times3(5)<<endl;
    cout<<getOperator(op)(a,b)<<endl;
}
