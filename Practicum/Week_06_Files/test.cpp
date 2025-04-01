#include <fstream>
#include <cstring>
#include <iostream>

class FN{
    char m_fn[10];
    bool isValid(const char* other) const{
        if(other[4] > '8')
            return false;
        if(other[1] != 'M')
            return false;
        if(other[2] != 'I')
            return false;
        return true;
    }
    public:
    FN(){};
    FN(const char* other){
        if(isValid(other)){
            strcpy(m_fn, other);
        }
    }
    friend std::ostream& operator<<(std::ostream& out,const FN& fn);
    friend std::istream& operator>>(std::istream& in,FN& student);
};

class Student{
    FN m_fn;
    char* name;
    int grade;

    void copy(const Student& other){
        m_fn = other.m_fn;
        grade = other.grade;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        name[strlen(other.name)] = '\0';
    }

    void free(){
        delete[] name;
    }

    public:
    Student():name(new char[1]{'\0'}){};
    Student(const Student& other): m_fn(other.m_fn){
        copy(other);
    }
    Student& operator=(const Student& other){
        if(this != &other){
            free();
            copy(other);
        }
        return *this;
    }
    ~Student(){
       free();
    }

    friend std::istream& operator>>(std::istream& in,Student& student); 
    friend std::ostream& operator<<(std::ostream& out,const Student& student);

};

std::istream& operator>>(std::istream& in,FN& fn){
    char temp[10];
    for(int i=0; i<10;i++)
        temp[i] = in.get();
    in.get();
    FN newFN(temp);
    fn = newFN;
    return in;
}   

std::istream& operator>>(std::istream& in,Student& student){
    in >> student.m_fn;
    in >> student.grade;
    int tempSize;
    in >> tempSize;
    char *newName = new char[tempSize+1];
    for(int i=0; i<tempSize;i++)
        in >> newName[i];

    newName[tempSize] = '\0';
    delete[] student.name;
    student.name = newName;
    return in;
}
std::ostream& operator<<(std::ostream& out,const FN& fn){
    for(int i = 0; i < 10; i++)
        out<<fn.m_fn[i];

    return out;
}


std::ostream& operator<<(std::ostream& out,const Student& student){
    out << student.m_fn <<std::endl;
    out << student.grade <<std::endl;
    out << strlen(student.name) <<std::endl;
    out << student.name <<std::endl;
    return out;
}


int main(){
    std::ofstream file("test.txt");
    Student a;
    std::cin >> a;
    std::cout << a;

}
/*
Student format

FN
grade
nameSize
Name

*/

/*
Напишете сами класовете StudentReader и StudentWriter
Искаме при подадено име(символен низ) в конструктора да работим с конкретния файл, ако съществува,
а без аргументи да се работи в стандартния вход и изход.

За класа StudentReader искаме да имаме метод readStudent(), който чете от съответния поток и връща нов студент.
За класа StudentWriter искаме да имаме метод writeStudent(), който записва в съответния поток студент, който се подава като аргумент.

Помислете как бихте прочели няколко студент и как бихте ги върнали? Какви проблеми могат да възникнат и как бихте ги решили?

*/