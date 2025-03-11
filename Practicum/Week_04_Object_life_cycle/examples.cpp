#include <iostream>
#include <cstring>

using namespace std;

// жизнен цикъл на обекта
// идея - конструктори
// идея - деструктори
// default - имплемнтации от компилатора
// синтаксис
// кое кога се вика (масиви)
// delete, default, explicit 

class A{
    public:
    A(){
        cout<<"A()"<<endl;
    }
    A(const A& other){
        cout<<"A(const A&)"<<endl;
    }
    A& operator=(const A& other){
        cout<<"A& operator=(const A&)"<<endl;
        return *this;
    }
    ~A(){
        cout<<"~A()"<<endl;
    }
};

class B{
    int m_num;
    A m_a;

    //const, reference, no default constructor;
    
    public:
    
    B() = default;

    B(int num):m_num(num), m_a(){
        cout<<"copy constructor of B"<<endl<<m_num<<endl;;
    };
    
    B(const B& other) = delete;
    
    ~B() = default; // никога delete
};   

int main(){
    A a;
    A d(a);
    A b = a;
    A c;
    c = a;
     
    // cout<<"------------------"<<endl;
    // B e = 7;


    cout<<"------------------"<<endl;
    return 0;
}

#include <chrono>
using namespace std::chrono;
class Message{
    char* message;
    char* user;
    int timestamp;

public:

    Message() = delete;
    
    Message(char* message, char* user){
        this->message = new char[strlen(message)+1];
        strcpy(this->message,message);
        
        this->user = new char[strlen(user)+1];
        strcpy(this->user,user);

        timestamp = duration_cast<::milliseconds>( system_clock::now().time_since_epoch() ).count(); 
    }
    Message(char* message, char* user, int timestamp){
        this->message = new char[strlen(message)+1];
        strcpy(this->message,message);
        
        this->user = new char[strlen(user)+1];
        strcpy(this->user,user);
        
        this->timestamp = timestamp;
    }
    Message(const Message& other){
        this->message = new char[strlen(other.message)+1];
        strcpy(this->message,other.message);
        
        this->user = new char[strlen(other.user)+1];
        strcpy(this->user,other.user);
        
        this->timestamp = other.timestamp;
    }

    void print(){
        cout<<user<<": "<<message<<endl;
    }

    ~Message(){
        delete[] message;
        delete[] user;
    }   
};


// int main(){
//     A a;
//     A d(a);
//     A b = a;
//     A c;
//     c = a;
//     return 0;
// }